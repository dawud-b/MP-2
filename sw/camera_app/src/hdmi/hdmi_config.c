/*
 * hdmi_config.c
 *
 * Author: Nikil Thapa
 *
 */
#include "hdmi_config.h"

#define PAGE_SIZE	16
#define IIC_ADV7511_ADDRESS 0x39
#define NUMBER_OF_HDMI_REGS  40
#define EEPROM_TEST_START_ADDRESS	0x80

#define EEPROM_ADDRESS		0x50

typedef struct {
	u8 addr;
	u8 data;
	u8 init;
} HDMI_REG;

HDMI_REG hdmi_iic[NUMBER_OF_HDMI_REGS] = {

		{ 0x15, 0x00, 0x01 },
		{ 0x16, 0x00, 0x38 },
		{ 0x41, 0x00, 0x10 },
		{ 0x48, 0x00, 0x08 },
		{ 0x55, 0x00, 0x00 },
		{ 0x56, 0x00, 0x28 },
		{ 0x98, 0x00, 0x03 },
		{ 0x9A, 0x00, 0xE0 },
		{ 0x9C, 0x00, 0x30 },
		{ 0x9D, 0x00, 0x61 },
		{ 0xA2, 0x00, 0xA4 },
		{ 0xA3, 0x00, 0xA4 },
		{ 0xAF, 0x00, 0x06 },
		{ 0xBA, 0x00, 0x60 },
		{ 0xE0, 0x00, 0xD0 },
		{ 0xF9, 0x00, 0x00 },

		// HDTV YCbCr (16to235) to RGB (16to235)
		//color space conversion
		/**/{ 0x18, 0x00, 0xAC },
		/**/{ 0x19, 0x00, 0x53 },
		/**/{ 0x1A, 0x00, 0x08 },
		/**/{ 0x1B, 0x00, 0x00 },
		/**/{ 0x1C, 0x00, 0x00 },
		/**/{ 0x1D, 0x00, 0x00 },
		/**/{ 0x1E, 0x00, 0x19 },
		/**/{ 0x1F, 0x00, 0xD6 },
		/**/{ 0x20, 0x00, 0x1C },
		/**/{ 0x21, 0x00, 0x56 },
		/**/{ 0x22, 0x00, 0x08 },
		/**/{ 0x23, 0x00, 0x00 },
		/**/{ 0x24, 0x00, 0x1E },
		/**/{ 0x25, 0x00, 0x88 },
		/**/{ 0x26, 0x00, 0x02 },
		/**/{ 0x27, 0x00, 0x91 },
		/**/{ 0x28, 0x00, 0x1F },
		/**/{ 0x29, 0x00, 0xFF },
		/**/{ 0x2A, 0x00, 0x08 },
		/**/{ 0x2B, 0x00, 0x00 },
		/**/{ 0x2C, 0x00, 0x0E },
		/**/{ 0x2D, 0x00, 0x85 },
		/**/{ 0x2E, 0x00, 0x18 },
		/**/{ 0x2F, 0x00, 0xBE }

};

u8 IIC_DEVICE_ADDR;

u8 WriteBuffer[PAGE_SIZE];

u8 ReadBuffer[PAGE_SIZE];

u8 DataBuf[PAGE_SIZE];

typedef u8 AddressType;

int hdmi_config(u32 IIC_BASEADDR) {
	u8 BytesRead;
	u32 StatusReg;
	u8 Index;
	int Status, i;
	int count = 0;
	IIC_DEVICE_ADDR = 0x74;
	u8 buffer;
	u8 Addr;
	u8 DataInit;

	Status = XIic_DynInit(IIC_BASEADDR);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	while (((StatusReg = XIic_ReadReg(IIC_BASEADDR, XIIC_SR_REG_OFFSET))
			& (XIIC_SR_RX_FIFO_EMPTY_MASK | XIIC_SR_TX_FIFO_EMPTY_MASK
					| XIIC_SR_BUS_BUSY_MASK))
			!= (XIIC_SR_RX_FIFO_EMPTY_MASK | XIIC_SR_TX_FIFO_EMPTY_MASK)) {

	}

	for (Index = 0; Index < PAGE_SIZE; Index++) {
		WriteBuffer[Index] = Index;
		ReadBuffer[Index] = 0;
		DataBuf[Index] = 0;
	}
	print("Register Programming...");
	IIC_DEVICE_ADDR = IIC_ADV7511_ADDRESS;
	for (Index = 0; Index < NUMBER_OF_HDMI_REGS; Index++) {
		IIC_WRITE(IIC_BASEADDR, hdmi_iic[Index].addr, &hdmi_iic[Index].init, 1);

	}
	print("DONE!\n\r");

	print("\n\rRegister Programming Verification\n\r");
	for (Index = 0; Index < NUMBER_OF_HDMI_REGS; Index++) {

		Addr = hdmi_iic[Index].addr;
		DataInit = hdmi_iic[Index].init;
		xil_printf("Reg Addr: 0x%x------Write Data: 0x%x------", Addr,
				DataInit);
		BytesRead = IIC_READ(IIC_BASEADDR, Addr, &buffer, 1);
		for (i = 0; i < 1000; i++)
			;	// IIC delay
		xil_printf("Read Data: 0x%x------", buffer);

		if (DataInit == buffer) {
			xil_printf("Matched\n\r");
			count++;
		} else {
			xil_printf("Not-Matched\n\r");
		}

		if (BytesRead != 1) {
			return XST_FAILURE;
		}
	}
	if (count == NUMBER_OF_HDMI_REGS) {
		xil_printf("Register Programming Successful!\n\r");
	} else {
		xil_printf("Register Programming FAILED!\n\r");
	}

	return XST_SUCCESS;
}
u8 IIC_WRITE(u32 IIC_BASEADDR, AddressType Address, u8 *BufferPtr, u8 ByteCount) {
	u8 SentByteCount;
	u8 WriteBuffer[sizeof(Address) + PAGE_SIZE];
	u8 Index;

	if (sizeof(AddressType) == 2) {
		WriteBuffer[0] = (u8) (Address >> 8);
		WriteBuffer[1] = (u8) (Address);
	} else if (sizeof(AddressType) == 1) {
		WriteBuffer[0] = (u8) (Address);
		IIC_DEVICE_ADDR |= (EEPROM_TEST_START_ADDRESS >> 8) & 0x7;
	}


	for (Index = 0; Index < ByteCount; Index++) {
		WriteBuffer[sizeof(Address) + Index] = BufferPtr[Index];
	}


	SentByteCount = XIic_DynSend(IIC_BASEADDR, IIC_DEVICE_ADDR, WriteBuffer,
			sizeof(Address) + ByteCount,
			XIIC_STOP);

	return SentByteCount - sizeof(Address);
}
u8 IIC_READ(u32 IIC_BASEADDR, AddressType Address, u8 *BufferPtr, u8 ByteCount) {
	u8 ReceivedByteCount;
	u8 SentByteCount;
	u16 StatusReg;


	do {
		StatusReg = XIic_ReadReg(IIC_BASEADDR, XIIC_SR_REG_OFFSET);
		if (!(StatusReg & XIIC_SR_BUS_BUSY_MASK)) {
			SentByteCount = XIic_DynSend(IIC_BASEADDR, IIC_DEVICE_ADDR,
					(u8 *) &Address, sizeof(Address),
					XIIC_REPEATED_START);
		}

	} while (SentByteCount != sizeof(Address));

	ReceivedByteCount = XIic_DynRecv(IIC_BASEADDR, IIC_DEVICE_ADDR, BufferPtr,
			ByteCount);

	return ReceivedByteCount;
}
