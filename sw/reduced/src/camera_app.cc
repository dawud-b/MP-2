/*
 * main2.cc
 *
 *  Created on: Apr 12, 2019
 *      Author: ROGyorgE
 */

#include "./camera_app.h"



int main()
{
  // Start bringing up board
  configure_platform();


  // Start Video HDMI Output Stream
  start_output_video_pipeline(vdma_a_driver, vid, Resolution::R1920_1080_60_PP,read_master_select);

  // Start Video Input Stream
  start_input_video_pipeline(vdma_a_driver, *cam_a_ptr, Resolution::R1920_1080_60_PP, OV5640_cfg::mode_t::MODE_1080P_1920_1080_30fps_336M_MIPI, csi_baseaddr_tmp);
  while(1);
  // Start SW Processing of Video Frames
  //camera_loop();

  //u32 current_vdmacr = Xil_In32(XPAR_AXIVDMA_0_BASEADDR + 0x30);
  //Xil_Out32(XPAR_AXIVDMA_0_BASEADDR + 0x30, current_vdmacr | (1 << 12));

//  u64 around_frame_start;
//  XTime_GetTime(&around_frame_start);
//
//  while (1) {
//	  //int counts = Xil_In32(XPAR_AXIVDMA_0_BASEADDR + 0x34) >> 24;
//	  //printf("%d\r\n", counts);
//
//	  if (Xil_In32(XPAR_AXIVDMA_0_BASEADDR + 0x34) & (1 << 12)) {
//		  u64 previous_time = around_frame_start;
//		  XTime_GetTime(&around_frame_start);
//		  Xil_Out32(XPAR_AXIVDMA_0_BASEADDR + 0x34, 0); // this needs to beet the time it takes to make a frame (should be clear on write for our relevant bit).
//
//		  printf("Frame time: %llu\r\n", COUNTS_PER_SECOND / (around_frame_start - previous_time));
//	  }
//
//  }


  //camera_interface();

  // Shutdown Platform
  //cleanup_platform();
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


  //Init of system board finished
  gpio_driver.clearBit(gpio_driver.Bits::CAM_GPIO0);
  ::usleep(1000000);
  gpio_driver.setBit(gpio_driver.Bits::CAM_GPIO0);
  ::usleep(1000000);

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
  vid.reset();

  // Reset VDMA Read channel
  vdma_driver.resetRead();

  // Configure Video Timing Controller and Clocking IP cores
  vid.configure(VideoOutputRes);

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
}



///////////////////////////////////////////
// Bring up input pipeline back-to-front //
///////////////////////////////////////////
void start_input_video_pipeline(AXI_VDMA<ScuGicInterruptController>& vdma_driver, OV5640& cam, Resolution VideoOutputRes, OV5640_cfg::mode_t mode, uintptr_t csi_baseaddr)
{


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

  sleep(5);

/*  *TPG_MS = 2; // slow down before going to software
  *TPG_FGP = 0;
  *TPG_BGP = 0xa; // go back to sin pattern*/
}



