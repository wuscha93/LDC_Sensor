/*
 * LDC_I2C.h
 *
 *  Created on: Nov 16, 2018
 *      Author: ADRIAN
 */

#ifndef __LDC_I2C_H_
#define __LDC_I2C_H_

// LDC i2C Address

#define LDC_MIN_I2CADDR     0x2A
#define LDC_MAX_I2CADDR     0x2B
#define LDC_DEFAULT_I2CADDR LDC_MIN_I2CADDR
//#define EVM_DEFAULTS_SIZE 24 // 13 registers, 0x08 - 0x14


// LDC I2C Registers

#define DATA0_MSB			0x00
#define	DATA0_LSB			0x01
#define	DATA1_MSB			0x02
#define	DATA1_LSB			0x03
#define	DATA2_MSB			0x04
#define	DATA2_LSB			0x05
#define	DATA3_MSB			0x06
#define	DATA3_LSB			0x07
#define	RCOUNT0				0x08
#define	RCOUNT1				0x09
#define	RCOUNT2				0x0a
#define	RCOUNT3				0x0b
#define	OFFSET0				0x0c
#define	OFFSET1				0x0d
#define	OFFSET2				0x0e
#define	OFFSET3				0x0f
#define	SETTLECOUNT0		0x10
#define	SETTLECOUNT1		0x11
#define	SETTLECOUNT2		0x12
#define	SETTLECOUNT3		0x13
#define	CLOCK_DIVIDERS0		0x14
#define	CLOCK_DIVIDERS1		0x15
#define	CLOCK_DIVIDERS2		0x16
#define	CLOCK_DIVIDERS3		0x17
#define	STATUS				0x18
#define	ERROR_CONFIG		0x19
#define	CONFIG				0x1a
#define	MUX_CONFIG			0x1b
#define	RESET_DEV			0x1c
#define	DRIVE_CURRENT0		0x1e
#define	DRIVE_CURRENT1		0x1f
#define	DRIVE_CURRENT2		0x20
#define	DRIVE_CURRENT3		0x21
#define	MANUFACTURER_ID		0x7e
#define	DEVICE_ID			0x7f


// LDC I2C Register Bits

//#define SLEEP_MODE_EN							0x2000
#define VAL_DEFAULT_CONFIG_NO_CONVERSION		0x3a01
#define VAL_DEFAULT_CONFIG_START_CONVERSION		0x1a01
#define VAL_SETTLECOUNT0						0x0400
#define VAL_SETTLECOUNT1						0x0400
#define VAL_RCOUNT0								0xffff
#define VAL_RCOUNT1								0xffff
#define VAL_RESET_DEV							0x8000
#define VAL_OFFSET0								0x0000
#define VAL_OFFSET1								0x0000
#define VAL_CLOCK_DIVIDERS0						0x1001
#define VAL_CLOCK_DIVIDERS1						0x1001
#define VAL_ERROR_CONFIG						0x0000
#define VAL_MUX_CONFIG							0x820c




uint8_t LDC_Init(void);

uint8_t LDC_startConversion(unsigned char channel);

uint8_t LDC_writeWordAddress8(uint8_t i2cDeviceAddress, uint8_t deviceRegister, uint16_t value);

uint8_t LDC_readWordAddress8(uint8_t i2cDeviceAddress, uint8_t deviceRegister, uint16_t *value);

uint8_t LDC_ReadWordAddress8(uint8_t deviceregister, uint16_t *buffer);

uint8_t LDC_getDigitalOutputCode(unsigned char channel, uint32_t *digitaloutputcode);


#endif /* SOURCES_LDC_I2C_H_ */
