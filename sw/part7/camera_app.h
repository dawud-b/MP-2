#ifndef CAMERA_APP_H   /* prevent circular inclusions */
#define CAMERA_APP_H   /* by using protection macros */


#include <exception>
#include <memory>

#include "xparameters.h"
#include <xbasic_types.h>
#include <xil_printf.h>
#include "platform/platform.h"
#include "verbose/verbose.h"
#include "intc/ScuGicInterruptController.h"
#include "cam/PS_GPIO.h"
#include "cam/Nop_GPIO.h"
#include "cam/PS_IIC.h"
#include "cam/TCA9546.h"
#include "cam/OV5640.h"
#include "video/VideoOutput.h"
#include "video/AXI_VDMA.h"
// #include "xcsi.h" // Uncomment when using CSI camera for video input

#include "hdmi/hdmi_config.h"

/* Hardware profile */
#define IRPT_CTL_DEVID 			XPAR_PS7_SCUGIC_0_DEVICE_ID
#define VDMA_A_DEVID			XPAR_AXI_VDMA_A_DEVICE_ID
#define VDMA_A_MM2S_IRPT_ID		XPAR_FABRIC_AXI_VDMA_A_MM2S_INTROUT_INTR
#define VDMA_A_S2MM_IRPT_ID		XPAR_FABRIC_AXI_VDMA_A_S2MM_INTROUT_INTR
#define GPIO_DEVID				XPAR_PS7_GPIO_0_DEVICE_ID
#define GPIO_IRPT_ID			XPAR_PS7_GPIO_0_INTR
#define CAM_I2C_DEVID			XPAR_PS7_I2C_0_DEVICE_ID
#define CAM_I2C_IRPT_ID			XPAR_PS7_I2C_0_INTR

#define VTC_DEVID				XPAR_VTC_0_DEVICE_ID
#define DYN_PIXCLK_DEVID		XPAR_VIDEO_DYNCLK_DEVICE_ID

#define VDMA_B_DEVID			XPAR_AXI_VDMA_B_DEVICE_ID
#define VDMA_B_S2MM_IRPT_ID		XPAR_FABRIC_AXI_VDMA_B_S2MM_INTROUT_INTR

#define VDMA_C_DEVID			XPAR_AXI_VDMA_C_DEVICE_ID
#define VDMA_C_S2MM_IRPT_ID		XPAR_FABRIC_AXI_VDMA_C_S2MM_INTROUT_INTR

#define VDMA_D_DEVID			XPAR_AXI_VDMA_D_DEVICE_ID
#define VDMA_D_S2MM_IRPT_ID		XPAR_FABRIC_AXI_VDMA_D_S2MM_INTROUT_INTR

/* *************** */
uintptr_t constexpr frame_baseaddr 	= 0x0A000000U; //Must make sure linker reserves the region above this
/* *************** */

using namespace digilent;

// Function Prototypes
void configure_platform(void);
static void start_output_video_pipeline(AXI_VDMA<ScuGicInterruptController>& vdma_driver, VideoOutput& vid, Resolution VideoOutputRes,u8 master_select);
static void start_input_video_pipeline(AXI_VDMA<ScuGicInterruptController>& vdma_driver, OV5640& cam, Resolution VideoOutputRes, OV5640_cfg::mode_t mode, uintptr_t csi_baseaddr);
void camera_loop(void); // SW Color Processing of video frames
int enable_color_pipeline(void); // HW Color Processing of video frames


// Assign CSI Base address to 0 when CSI IP block not present
#ifdef  XPAR_CSISS_0_BASEADDR
  uintptr_t csi_baseaddr_tmp = XPAR_CSISS_0_BASEADDR;
#else
  uintptr_t csi_baseaddr_tmp = 0;
#endif


// PHJ START MOVE to MP2.h
u8 read_master_select;

ScuGicInterruptController irpt_ctl(IRPT_CTL_DEVID);

//Construct camera control IPs
PS_GPIO<ScuGicInterruptController> gpio_driver(GPIO_DEVID, irpt_ctl, GPIO_IRPT_ID);
Nop_GPIO nopgpio;
PS_IIC<ScuGicInterruptController> iic_driver(CAM_I2C_DEVID, irpt_ctl, CAM_I2C_IRPT_ID, 100000);
//Dual-channel VDMA for the HDMI display, and Video input stream
AXI_VDMA<ScuGicInterruptController> vdma_a_driver(VDMA_A_DEVID, frame_baseaddr, irpt_ctl,
							                        VDMA_A_MM2S_IRPT_ID,
							                        VDMA_A_S2MM_IRPT_ID);
//Output pipeline drivers
VideoOutput vid(VTC_DEVID, DYN_PIXCLK_DEVID);

//Input pipeline drivers
std::unique_ptr<TCA9546> muxch_a_ptr;
std::unique_ptr<OV5640> cam_a_ptr;

// PHJ END MOVE to MP2.h

#endif  /* end of protection macro */
