#include "xiic_l.h"
typedef u8 AddressType;

int hdmi_config(u32 IIC_BASEADDR);
u8 IIC_WRITE(u32 IIC_BASEADDR, AddressType Address, u8 *BufferPtr, u8 ByteCount);
u8 IIC_READ(u32 IIC_BASEADDR, AddressType Address, u8 *BufferPtr, u8 ByteCount);
