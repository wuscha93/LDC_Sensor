/*
 * LDC_I2C.c
 *
 *  Created on: Nov 16, 2018
 *      Author: ADRIAN
 */

#include "GI2C1.h"
#include "LDC_I2C.h"
#include "ADDR.h"
#include "WAIT1.h"
#include "PE_Error.h"

uint8_t LDC_writeWordAddress8(uint8_t i2cDeviceAddress, uint8_t deviceRegister, uint16_t value){
	uint8_t v8[2];
	uint16_t v16;

	v8[1] = value>>8;
	v8[0] = value&0xff;
	v16 = (uint16_t) (v8[0]<<8) | v8[1];
	return GI2C1_WriteWordAddress8(i2cDeviceAddress, deviceRegister, v16);
}

uint8_t LDC_readWordAddress8(uint8_t i2cDeviceAddress, uint8_t deviceRegister, uint16_t *value){
	return GI2C1_ReadWordAddress8(i2cDeviceAddress, deviceRegister, value);
}


uint8_t LDC_Init(void){

	uint8_t retVal = ERR_OK;
	ADDR_PutVal(0);				// LDC I2C Address = 0x2A

	// Evt Reset Device?
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) RESET_DEV, (uint16_t) VAL_RESET_DEV);			// Reset Device
	WAIT1_Waitms(50);			// No specific wait

	// Settings for Channel 0 and Channel 1
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) RCOUNT0, (uint16_t) VAL_RCOUNT0); 			// CH0: longest conversion time (26.21ms)
	WAIT1_Waitms(1);
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) RCOUNT1, (uint16_t) VAL_RCOUNT1); 			// CH1: longest conversion time (26.21ms)
	WAIT1_Waitms(1);
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) OFFSET0, (uint16_t) VAL_OFFSET0); 			// CH0: no offset
	WAIT1_Waitms(1);
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) OFFSET1, (uint16_t) VAL_OFFSET1); 			// CH1: no offset
	WAIT1_Waitms(1);
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) SETTLECOUNT0, (uint16_t) VAL_SETTLECOUNT0);		// CH0: settlecount = 0.4ms
	WAIT1_Waitms(1);
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) SETTLECOUNT1, (uint16_t) VAL_SETTLECOUNT1);		// CH1: settlecount = 0.4ms
	WAIT1_Waitms(1);
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) CLOCK_DIVIDERS0, (uint16_t) VAL_CLOCK_DIVIDERS0);	// CH0: CH0 Inputdivider = 1, CH0 Reference Divider = 1
	WAIT1_Waitms(1);
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) CLOCK_DIVIDERS1, (uint16_t) VAL_CLOCK_DIVIDERS1);	// CH1: CH0 Inputdivider = 1, CH0 Reference Divider = 1
	WAIT1_Waitms(1);
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) ERROR_CONFIG, (uint16_t) VAL_ERROR_CONFIG);		// no error report
	WAIT1_Waitms(1);

	// write to CONFIG
	// Sleepmode = active, Sensor Rp override = enabled, low power activation mode = enabled, auto sensor amplitude = enabled
	// External Clock (MHz), High Current Sensor Drive = disabled
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) MUX_CONFIG, (uint16_t) 0x820c);			// CH0: CH0-CH1 Sequence
	WAIT1_Waitms(1);
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) CONFIG, (uint16_t) VAL_DEFAULT_CONFIG_WITH_CONVERSION);

	return retVal;
}

uint8_t LDC_startConversion(unsigned char channel){
	uint8_t retVal = ERR_OK;
	if(channel == 0){

	}
	return retVal;
}

uint8_t LDC_readConversion(unsigned char channel){
	uint8_t retVal = ERR_OK;
	if(channel == 0){
	}
	return retVal;
}




