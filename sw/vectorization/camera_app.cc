/*
 * main2.cc
 *
 *  Created on: Apr 12, 2019
 *      Author: ROGyorgE
 */

#include "./camera_app.h"
#include "xparameters.h"
#include "xtime_l.h"
#include "time.h"
#include <arm_neon.h>

int main()
{
  // Start bringing up board
  configure_platform();

  // Start Video HDMI Output Stream
  start_output_video_pipeline(vdma_a_driver, vid, Resolution::R1920_1080_60_PP,read_master_select);

  // Start Video Input Stream
  start_input_video_pipeline(vdma_a_driver, *cam_a_ptr, Resolution::R1920_1080_60_PP, OV5640_cfg::mode_t::MODE_1080P_1920_1080_30fps_336M_MIPI, csi_baseaddr_tmp);

  // Start SW Processing of Video Frames
  camera_loop();

  // Shutdown Platform
  cleanup_platform();
}


/////////////////////////////////
// Start bringing up the board //
/////////////////////////////////
void configure_platform(void)
{
  //Init CPU, UART, caches etc.
  init_platform();

  // Configure HDMI interface
  hdmi_config(XPAR_AXI_IIC_HDMI_BASEADDR);

  xil_printf("Initializing...\r\n");

  //Init of system board finished
  xil_printf("Starting system...\r\n");
  gpio_driver.clearBit(gpio_driver.Bits::CAM_GPIO0);
  ::usleep(1000000);
  gpio_driver.setBit(gpio_driver.Bits::CAM_GPIO0);
  ::usleep(1000000);
  xil_printf("CAM GPIO complete\r\n");

  muxch_a_ptr = std::make_unique<TCA9546>(iic_driver, 0, 1 << 0);
  cam_a_ptr = std::make_unique<OV5640>(*muxch_a_ptr, nopgpio);
  read_master_select  = 0x00;
}


////////////////////////////////////////////
// Bring up output pipeline back-to-front //
////////////////////////////////////////////
void start_output_video_pipeline(AXI_VDMA<ScuGicInterruptController>& vdma_driver, VideoOutput& vid, Resolution VideoOutputRes, u8 master_select)
{

  // Reset Video Timing Controller
  xil_printf("\r\nVTC resetting...\r\n");
  vid.reset();

  // Reset VDMA Read channel
  xil_printf("VDMA Read Channel resetting...\r\n");
  vdma_driver.resetRead();

  // Configure Video Timing Controller and Clocking IP cores
  xil_printf("Waiting for clocks to lock...\r\n");
  vid.configure(VideoOutputRes);
  xil_printf("Clocks locked\r\n");

  // Configure VDMA Read channel
  vdma_driver.configureRead(timing[static_cast<int>(VideoOutputRes)].h_active, timing[static_cast<int>(VideoOutputRes)].v_active,master_select);

  // Clear/Initialize VDMA frame buffers
  Xuint32 i;
  Xuint32 storage_size = XPAR_AXIVDMA_0_NUM_FSTORES * ((1920*1080)<<1);
  volatile Xuint32 *pStorageMem = (Xuint32 *)frame_baseaddr;

  // Frame #1 - Red pixels
  for (i = 0; i < storage_size / XPAR_AXIVDMA_0_NUM_FSTORES; i += 4) {
	  *pStorageMem++ = 0xF0525A52;  // Red
  }
  // Frame #2 - Green pixels
  for (i = 0; i < storage_size / XPAR_AXIVDMA_0_NUM_FSTORES; i += 4) {
	  *pStorageMem++ = 0x36912291; // Green
  }
  // Frame #3 - Blue pixels
  for (i = 0; i < storage_size / XPAR_AXIVDMA_0_NUM_FSTORES; i += 4) {
	  *pStorageMem++ = 0x6E29F029;  // Blue
  }

  Xil_DCacheFlush(); // Flush Cache

  // Enable Video Timing Controller
  vid.enable();

  // Enable VDMA Read channel
  vdma_driver.enableRead();

  xil_printf("\r\nStarting HDMI Output:\r\n");
  xil_printf("If Static Image does not display within 10s restart program\r\n");
  sleep(10);

  xil_printf("Output Static Image for 5 more seconds\r\n");
  xil_printf("If Static Image currently not displaying, then restart program\r\n");
  sleep(5);
}



///////////////////////////////////////////
// Bring up input pipeline back-to-front //
///////////////////////////////////////////
void start_input_video_pipeline(AXI_VDMA<ScuGicInterruptController>& vdma_driver, OV5640& cam, Resolution VideoOutputRes, OV5640_cfg::mode_t mode, uintptr_t csi_baseaddr)
{

  xil_printf("\r\nStart selected Video stream: 1. TPG, or 2. Camera...\r\n");

  // Reset VDMA write channel
  vdma_driver.resetWrite();

  // Disable CSI Camera IP block
  // Option 2: Uncomment if camera used for video input
  *(int *)csi_baseaddr = 0;

  // Configure VDMA write channel
  vdma_driver.configureWrite(timing[static_cast<int>(VideoOutputRes)].h_active, timing[static_cast<int>(VideoOutputRes)].v_active, timing[static_cast<int>(VideoOutputRes)].h_active, timing[static_cast<int>(VideoOutputRes)].v_active);

  //Initialize Camera
  // Option 2: Uncomment if camera is used for video input
  cam.init();

  // Enable VDMA Write Channel
  vdma_driver.enableWrite();

  // Configure and enable Color HW pipeline
    // Uncomment when using Color HW pipeline
//  enable_color_pipeline();


  // Chose Video Input source: 1) TPG, or 2) Camera
    // Option 1: Uncomment for TPG option
  // Define convenient volatile pointers for accessing TPG registers
/*
  volatile unsigned int *TPG_CR       = (unsigned int *)(XPAR_V_TPG_0_S_AXI_CTRL_BASEADDR + 0);    // TPG Control
  volatile unsigned int *TPG_Act_H    = (unsigned int *)(XPAR_V_TPG_0_S_AXI_CTRL_BASEADDR + 0x10); // Active Height
  volatile unsigned int *TPG_Act_W    = (unsigned int *)(XPAR_V_TPG_0_S_AXI_CTRL_BASEADDR + 0x18); // Active Width
  volatile unsigned int *TPG_BGP      = (unsigned int *)(XPAR_V_TPG_0_S_AXI_CTRL_BASEADDR + 0x20); // Background Pattern
  volatile unsigned int *TPG_FGP      = (unsigned int *)(XPAR_V_TPG_0_S_AXI_CTRL_BASEADDR + 0x28); // Foreground Pattern
  volatile unsigned int *TPG_MS       = (unsigned int *)(XPAR_V_TPG_0_S_AXI_CTRL_BASEADDR + 0x38); // Motion Speed
  volatile unsigned int *TPG_CF       = (unsigned int *)(XPAR_V_TPG_0_S_AXI_CTRL_BASEADDR + 0x40); // TPG Color Format

  xil_printf("Start Test Pattern Generator...\n\r");
  // Direct Memory Mapped access of TPG configuration registers
  // See TPG data sheet for configuring the TPG for other features
  TPG_Act_H[0]  = 0x438; // Active Height
  TPG_Act_W[0]  = 0x780; // Active Width
  //TPG_BGP[0]    = 0x0A;  // Background Pattern
  TPG_BGP[0]    = 0x10;  // Background Pattern // psuedorandom pattern
  //TPG_FGP[0]    = 0x00;  // Foreground Pattern
  TPG_FGP[0]    = 0x0;  // Foreground Pattern
  // TPG_MS[0]     = 0x04;  // Motion Speed
  TPG_MS[0]     = 0x0f;  // Motion Speed Increase speed
  TPG_CF[0]     = 0x02;  // TPG Color Format
  TPG_CR[0]     = 0x81;  // TPG Control*/

    // Option 2: Uncomment for Camera option
	*(int *)csi_baseaddr = 1; // CSI Enable
	cam.set_mode(mode);
	cam.set_awb(OV5640_cfg::awb_t::AWB_ADVANCED);

  xil_printf("VDMA pass-through for 5 Seconds\r\n");
  sleep(5);

/*  *TPG_MS = 2; // slow down before going to software
  *TPG_FGP = 0;
  *TPG_BGP = 0xa; // go back to sin pattern*/
}


///////////////////////////////////
// SW processing of video frames //
///////////////////////////////////
void camera_loop(void)
{
  Xuint32 parkptr; // Store Park location for VDMA Write or Read channel
  Xuint32 vdma_S2MM_DMACR;  // Store value of VDMA Write channel Control Register
  Xuint32 vdma_MM2S_DMACR;  // Store value of VDMA Read channel Control Register
  int i, j; // Loop indexes

  xil_printf("\r\nEntering SW processing loop...\r\n");

  // Grab the DMA parkptr, and update it to ensure that when parked, the S2MM side is on frame 0, and the MM2S side on frame 1
  parkptr = XAxiVdma_ReadReg(XPAR_AXIVDMA_0_BASEADDR, XAXIVDMA_PARKPTR_OFFSET);
  parkptr &= ~XAXIVDMA_PARKPTR_READREF_MASK;
  parkptr &= ~XAXIVDMA_PARKPTR_WRTREF_MASK;
  parkptr |= 0x1;
  XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, XAXIVDMA_PARKPTR_OFFSET, parkptr);

  // Grab the VDMA Control Registers, and place VDMA channels in Park
  // (i.e., Lock each VDMA channel to its own frame buffer)
  vdma_MM2S_DMACR = XAxiVdma_ReadReg(XPAR_AXIVDMA_0_BASEADDR, XAXIVDMA_TX_OFFSET+XAXIVDMA_CR_OFFSET);
  XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, XAXIVDMA_TX_OFFSET+XAXIVDMA_CR_OFFSET, vdma_MM2S_DMACR & ~XAXIVDMA_CR_TAIL_EN_MASK);
  vdma_S2MM_DMACR = XAxiVdma_ReadReg(XPAR_AXIVDMA_0_BASEADDR, XAXIVDMA_RX_OFFSET+XAXIVDMA_CR_OFFSET);
  XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, XAXIVDMA_RX_OFFSET+XAXIVDMA_CR_OFFSET, vdma_S2MM_DMACR & ~XAXIVDMA_CR_TAIL_EN_MASK);

  // Pointers to the S2MM memory frame and M2SS memory frame
  volatile Xuint16 *pS2MM_Mem = (Xuint16 *)XAxiVdma_ReadReg(XPAR_AXIVDMA_0_BASEADDR, XAXIVDMA_S2MM_ADDR_OFFSET+XAXIVDMA_START_ADDR_OFFSET);
  volatile Xuint16 *pMM2S_Mem = (Xuint16 *)XAxiVdma_ReadReg(XPAR_AXIVDMA_0_BASEADDR, XAXIVDMA_MM2S_ADDR_OFFSET+XAXIVDMA_START_ADDR_OFFSET+4);

  xil_printf("SW processing 1000 frames...\r\n");
  xil_printf("pS2MM_Mem = %X\n\r", pS2MM_Mem);
  xil_printf("pMM2S_Mem = %X\n\r", pMM2S_Mem);


  // SW Pass-through: SW Copying Write VDMA Frame Buffer to HDMI read VDMA Frame Buffer (Note: This will display Upside down)
  // Copy 1000 frames using SW before going back to VDMA pass-through mode
  // YOUR Color Conversion SW algorithm will replace this SW pass-through code


  /*for (j = 0; j < 1000; j++) {
    for (i = 0; i < 1920*1080; i++) {
      pMM2S_Mem[i] = pS2MM_Mem[1920*1080-i-1];
    }
  }*/


  volatile Xuint16 (*s2mm_frame)[1920] = (volatile Xuint16 (*)[1920]) pS2MM_Mem;
  volatile Xuint16 (*mm2s_frame)[1920] = (volatile Xuint16 (*)[1920]) pMM2S_Mem;

  uint32_t kernel3by3[9] = {0};

  uint64_t tests[3] = {0};

  uint64_t start_time;
  uint64_t end_time;
  uint64_t test1;
  uint64_t test2;
  XTime_GetTime(&start_time);
  while (1) {
	  int count = 0;
	  XTime_GetTime(&start_time);
	  for (int row = 0; row < 1080; row++) {


		  uint16x8x2_t top_row_RG = vld2q_u16((volatile const uint16_t*) &s2mm_frame[row][0]);
		  uint16x8x2_t middle_row_GB = vld2q_u16((volatile const uint16_t*) &s2mm_frame[row+1][0]);
		  uint16x8x2_t bottom_row_RG = vld2q_u16((volatile const uint16_t*) &s2mm_frame[row+2][0]);

		  uint16x8_t merged_reds = vrhaddq_u16(top_row_RG.val[0], bottom_row_RG.val[0]);
		  uint16x8_t merged_greens = vrhaddq_u16(top_row_RG.val[1], bottom_row_RG.val[1]);
		  uint16x8_t bottom_greens = middle_row_GB.val[0];
		  uint16x8_t blues = middle_row_GB.val[1];

		  uint16x8_t bottom_greens_left_align = vextq_u16(bottom_greens, bottom_greens, 1); // 2nd element should then be first element
		  uint16x8_t reds_left_align = vextq_u16(merged_reds, merged_reds, 1);
		  uint16x8_t blues_left_align = vextq_u16(blues, blues, 1);

		  uint16x8_t green_condensed1 = vrhaddq_u16(merged_greens, vrhaddq_u16(bottom_greens, bottom_greens_left_aligned));
		  // TODO: interleave green_condensed1 with bottom_greens_left_align

		  uint16x8_t red_condensed1 = vrhaddq_u16(merged_reds, reds_left_aligned);
		  // TODO: interleave red_condensed1 with merged_reds

		  uint16x8_t blue_condensed1 = vrhaddq_u16(blues, blues_left_align);
		  // TODO: interleave blues with blues_left_align



		  for (int col = 0; col < 1920; col++) {

			  XTime_GetTime(&test1);

			  if (row == 0 || col == 0)
				  kernel3by3[0] = 0;
			  else
				  kernel3by3[0] = s2mm_frame[row-1][col-1];

			  if (row == 0)
				  kernel3by3[1] = 0;
			  else
				  kernel3by3[1] = s2mm_frame[row-1][col];

			  if (row == 0 || col == 1919)
				  kernel3by3[2] = 0;
			  else
				  kernel3by3[2] = s2mm_frame[row-1][col+1];

			  if (col == 0)
				  kernel3by3[3] = 0;
			  else
				  kernel3by3[3] = s2mm_frame[row][col-1];

			  kernel3by3[4] = s2mm_frame[row][col];

			  if (col == 1919)
				  kernel3by3[5] = 0;
			  else
				  kernel3by3[5] = s2mm_frame[row][col+1];

			  if (row == 1079 || col == 0)
				  kernel3by3[6] = 0;
			  else
				  kernel3by3[6] = s2mm_frame[row+1][col-1];

			  if (row == 1079)
				  kernel3by3[7] = 0;
			  else
				  kernel3by3[7] = s2mm_frame[row+1][col];

			  if (row == 1079 || col == 1919)
				  kernel3by3[8] = 0;
			  else
				  kernel3by3[8] = s2mm_frame[row+1][col+1];

			  XTime_GetTime(&test2);
			  tests[0] = test2 - test1;

			  uint16_t red = 0;
			  uint16_t green = 0;
			  uint16_t blue = 0;

			  XTime_GetTime(&test1);

			  if (row % 2 == 0 && col % 2 == 0) {
				  red = kernel3by3[4];
				  green = (kernel3by3[1] + kernel3by3[3] + kernel3by3[5] + kernel3by3[7]) / 4;
				  blue = (kernel3by3[0] + kernel3by3[2] + kernel3by3[6] + kernel3by3[8]) / 4;
			  } else if (row % 2 == 0) {
				  red = (kernel3by3[3] + kernel3by3[5]) / 2;
				  green = (kernel3by3[0] + kernel3by3[2] + kernel3by3[4] + kernel3by3[6] + kernel3by3[8]) / 5;
				  blue = (kernel3by3[1] + kernel3by3[7]) / 2;
			  } else if (col % 2 == 0) {
				  red = (kernel3by3[1] + kernel3by3[7]) / 2;
				  green = (kernel3by3[0] + kernel3by3[2] + kernel3by3[4] + kernel3by3[6] + kernel3by3[8]) / 5;
				  blue = (kernel3by3[3] + kernel3by3[5]) / 2;
			  } else {
				  red = (kernel3by3[0] + kernel3by3[2] + kernel3by3[6] + kernel3by3[8]) / 4;
				  green = (kernel3by3[1] + kernel3by3[3] + kernel3by3[5] + kernel3by3[7]) / 4;
				  blue = kernel3by3[4];
			  }

			  XTime_GetTime(&test2);
			  tests[1] = test2 - test1;

			  XTime_GetTime(&test1);

			  uint8_t Y = ((uint8_t) (16.0 + (float) red * 0.183 + (float) green * 0.614 + (float) blue * 0.062));
			  uint8_t Cb = ((uint8_t) (128.0 + (float) red * -0.101 + (float) green * -0.338 + (float) blue * 0.439));
			  uint8_t Cr = ((uint8_t) (128.0 + (float) red * 0.439 + (float) green * -0.399 + (float) blue * -0.040));


			  uint16_t YCbCr = count % 2 ? (Cb << 8) | Y : (Cr << 8) | Y;

			  XTime_GetTime(&test2);
			  tests[2] = test2 - test1;

			  mm2s_frame[row][col] = YCbCr;
			  count++;
		  }
	  }
	  XTime_GetTime(&end_time);
	  uint64_t cycles = end_time - start_time;
	  float seconds_per_frame = (float) cycles / (float) COUNTS_PER_SECOND;
	  float frames_per_second = 1.0 / seconds_per_frame;
	  //printf("Time for a single frame: %llu\r\n", cycles); // xil_printf was printing wrong for %llu
	  printf("Seconds per frame: %f. Frames per second: %f\r\n", seconds_per_frame, frames_per_second);
	  printf("Cycles for the window memory reads: %llu. Cycles for averaging: %llu. Cycles for float matrix multiplication: %llu.\r\n", tests[0], tests[1], tests[2]);
  }


  // Grab the VDMA Control Registers, and take VDMA channels out of Park
  // (i.e., Allow each VDMA channel to sequence through all frame buffers)
  vdma_MM2S_DMACR = XAxiVdma_ReadReg(XPAR_AXIVDMA_0_BASEADDR, XAXIVDMA_TX_OFFSET+XAXIVDMA_CR_OFFSET);
  XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, XAXIVDMA_TX_OFFSET+XAXIVDMA_CR_OFFSET, vdma_MM2S_DMACR | XAXIVDMA_CR_TAIL_EN_MASK);
  vdma_S2MM_DMACR = XAxiVdma_ReadReg(XPAR_AXIVDMA_0_BASEADDR, XAXIVDMA_RX_OFFSET+XAXIVDMA_CR_OFFSET);
  XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, XAXIVDMA_RX_OFFSET+XAXIVDMA_CR_OFFSET, vdma_S2MM_DMACR | XAXIVDMA_CR_TAIL_EN_MASK);

  xil_printf("SW processing loop complete!\r\n");
  xil_printf("\r\nReturning to VDMA pass-through operation for 10 seconds\r\n");
  sleep(10);

  // Uncomment when using TPG for Video input
  // Define convenient volatile pointers for accessing TPG registers
  //volatile unsigned int *TPG_CR  = (unsigned int *)(XPAR_V_TPG_0_S_AXI_CTRL_BASEADDR + 0);    // TPG Control
  //xil_printf("\r\nShutting down: Disabling Test Pattern Generator...\n\r");
  //TPG_CR[0]     = 0x00;  // TPG Control Register (Disable TPG)

  sleep(1);

  return;
}



// Uncomment for Hardware Image color Pipeline
// XVprocSs proc_ss_RGB_YCrCb_444;  // To hold info for the Video Processing Subsystem: Color Conversion Only IP core: See xv_procss.h, and xv_csc_l2.h
// XVprocSs_Config *Config_ptr;

/////////////////////////////////////////
// Enable HW Color processing pipeline //
/////////////////////////////////////////
int enable_color_pipeline(void) {

   xil_printf("Hardware Color Image Processing Pipeline Initialization ...\n\r" );

   // Video Processing Subsystem (Only re-sampling) 4:4:4 to 4:2:2  (See IP documentation for register details)
   // TODO Add additional register assignments here to fully configure this core. See Video Processing Subsystem IP documentation for register details.
   // Hint 1: You will need to configure 4 additional registers,
   // Hint 2: You will need to dig through some header files for some of the values,
   // Hint 3: Set up the Demosaic IP block first. It is a good warm up.

   // Add assignments here

   // Uncomment as part of Re-sampler IP setup
//   Xil_Out32((XPAR_V_PROC_SS_2_BASEADDR) + (XV_HCRESAMPLER_CTRL_ADDR_AP_CTRL), (u32)(0x81));  // Control
   xil_printf("4:4:4 to 4:2:2 Re-sampling IP Configuration and Enable done\r\n");

   // Video Processing Subsystem Hardware IP (configured for Only Color Conversion) from 24-bit RGB to YCrCb 4:4:4
   // For this IP core there was a High level API for setting it up.  Trace through these calls to see how much work they do.
   // This could have been set up with direct register writes, but there are about 20 registers that need to be set for this IP block

   // Uncomment to setup Color Conversion IP
//   Config_ptr = XVprocSs_LookupConfig(XPAR_XVPROCSS_0_DEVICE_ID);
//   XVprocSs_CfgInitialize(&proc_ss_RGB_YCrCb_444, Config_ptr, XPAR_XVPROCSS_0_BASEADDR);
//   XVprocSs_SetSubsystemConfig(&proc_ss_RGB_YCrCb_444);
//   XV_CscSetColorspace(proc_ss_RGB_YCrCb_444.CscPtr, XVIDC_CSF_RGB, XVIDC_CSF_YCRCB_444, XVIDC_BT_709, XVIDC_BT_709, XVIDC_CR_0_255);
//   XVprocSs_Start(&proc_ss_RGB_YCrCb_444);
   xil_printf("RGB to 4:4:4 IP Configuration and Enable done\r\n");


   // Demosaic to convert sensor Bayer pattern into 24-bit RGB
   // TODO Add additional register assignments here to fully configure this core. See Demosaic IP documentation for register details.
   // Hint 1: You will need to configure 3 addition registers

   // Add assignment here

   // Uncomment as part of Demosaic IP setup
//   Xil_Out32((XPAR_XV_DEMOSAIC_0_S_AXI_CTRL_BASEADDR) + (XV_DEMOSAIC_CTRL_ADDR_AP_CTRL), (u32)(0x81));// 0b10000001 means start and freerun mode (page 16 in PG286)
   xil_printf("Demosaic IP Configuring and Enable done\r\n"); // RGRG sensor pattern

   return 0;
}
