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

unsigned char numberOfActivatedChannels = 0;

/*
** ===================================================================
**     Method      :  LDC_Init (void)
**     Description :
**         Initializes the LDC 1614
**     Parameters  :
**     Returns     :
**         ---             - Error code, returns ERR_OK if I2C
**         				     communication was successful
** ===================================================================
*/

uint8_t LDC_Init(void){

	uint8_t retVal = ERR_OK;
	ADDR_PutVal(0);	// LDC I2C Address = 0x2A

	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) RESET_DEV, (uint16_t) VAL_RESET_DEV);				// Reset Device
	WAIT1_Waitms(50);

	// Settings for Channel 0 - Channel 3
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) RCOUNT0, (uint16_t) VAL_RCOUNT); 					// CH0: conversion time (26.21ms)
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) RCOUNT1, (uint16_t) VAL_RCOUNT); 					// CH1: conversion time (26.21ms)
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) RCOUNT2, (uint16_t) VAL_RCOUNT); 					// CH0: conversion time (26.21ms)
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) RCOUNT3, (uint16_t) VAL_RCOUNT); 					// CH1: conversion time (26.21ms)

	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) OFFSET0, (uint16_t) VAL_OFFSET); 					// CH0: no offset
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) OFFSET1, (uint16_t) VAL_OFFSET); 					// CH1: no offset
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) OFFSET2, (uint16_t) VAL_OFFSET); 					// CH0: no offset
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) OFFSET3, (uint16_t) VAL_OFFSET); 					// CH1: no offset

	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) SETTLECOUNT0, (uint16_t) VAL_SETTLECOUNT);		// CH0: settle-count = 0.4ms
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) SETTLECOUNT1, (uint16_t) VAL_SETTLECOUNT);		// CH1: settle-count = 0.4ms
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) SETTLECOUNT2, (uint16_t) VAL_SETTLECOUNT);		// CH0: settle-count = 0.4ms
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) SETTLECOUNT3, (uint16_t) VAL_SETTLECOUNT);		// CH1: settle-count = 0.4ms

	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) CLOCK_DIVIDERS0, (uint16_t) VAL_CLOCK_DIVIDERS);	// CH0: CH0 Input-divider = 1, CH0 Reference Divider = 1
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) CLOCK_DIVIDERS1, (uint16_t) VAL_CLOCK_DIVIDERS);	// CH1: CH0 Input-divider = 1, CH0 Reference Divider = 1
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) CLOCK_DIVIDERS2, (uint16_t) VAL_CLOCK_DIVIDERS);	// CH0: CH0 Input-divider = 1, CH0 Reference Divider = 1
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) CLOCK_DIVIDERS3, (uint16_t) VAL_CLOCK_DIVIDERS);	// CH1: CH0 Input-divider = 1, CH0 Reference Divider = 1



	// CONFIG
	// Sleepmode = active, Sensor Rp override = enabled, low power activation mode = enabled, auto sensor amplitude = enabled
	// External Clock (MHz), High Current Sensor Drive = disabled, CH0-CH1 Measuring Sequence
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) ERROR_CONFIG, (uint16_t) VAL_ERROR_CONFIG);		// no error report
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) MUX_CONFIG, (uint16_t) VAL_MUX_CONFIG);
	retVal &= LDC_writeWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, (uint8_t) CONFIG, (uint16_t) VAL_DEFAULT_CONFIG_START_CONVERSION);

	// set numberOfActiveChannels variable
	if(((MUX_CONFIG & 0x6000)>>13) == 0 || ((MUX_CONFIG & 0x6000)>>13) == 3) 	{numberOfActivatedChannels = 2;}
	if(((MUX_CONFIG & 0x6000)>>13) == 1) 										{numberOfActivatedChannels = 3;}
	if(((MUX_CONFIG & 0x6000)>>13) == 2) 										{numberOfActivatedChannels = 4;}
	return retVal;
}

/*
** ===================================================================
**     Method      :  LDC_writeWordAddress8 (uint8_t i2cDeviceAddress, uint8_t deviceRegister, uint16_t value)
**     Description :
**         Writes a 16bit value to an 8bit I2c register of the LDC1614
**         The MSB and LSB are changed in order to send the MSB first according to LDC1614 specification
**     Parameters  :
**         i2cDeviceAddress            - I2c address of LDC1614
**         deviceRegister			   - register address of LDC1614
**         value					   - data (settings)
**     Returns     :
**         ---             - Error code, returns ERR_OK if I2C
**         				     communication was successful
** ===================================================================
*/
uint8_t LDC_writeWordAddress8(uint8_t i2cDeviceAddress, uint8_t deviceRegister, uint16_t value){
	uint8_t retVal = ERR_OK;
	uint8_t v8[2];
	uint16_t v16;

	v8[1] = value>>8;
	v8[0] = value&0xff;
	v16 = (uint16_t) (v8[0]<<8) | v8[1];
	retVal = GI2C1_WriteWordAddress8(i2cDeviceAddress, deviceRegister, v16);
	WAIT1_Waitms(1);
	return retVal;
}



/*
** ===================================================================
**     Method      :  LDC_readWordAddress8 (uint8_t i2cDeviceAddress, uint16_t *buffer)
**     Description :
**         Reads a 16bit value of an 8bit I2c register of the LDC1614
**         The MSB and LSB are changed in order to read the MSB first according to LDC1614 specification
**     Parameters  :
**         deviceRegister			   - register address of LDC1614
**        *data					   	   - data buffer for the value to be stored in
**     Returns     :
**         ---             - Error code, returns ERR_OK if I2C
**         				     communication was successful
** ===================================================================
*/
uint8_t LDC_readWordAddress8(uint8_t deviceregister, uint16_t *data){
	uint8_t retVal = ERR_OK;
	uint8_t v[2];

	retVal &= GI2C1_ReadWordAddress8((uint8_t) LDC_DEFAULT_I2CADDR, deviceregister, data);
	v[1] = *data>>8;
	v[0] = *data&0xff;
	*data = (uint16_t) (v[0]<<8) | v[1];

	return retVal;
}

/*
** ===================================================================
**     Method      :  LDC_getDigitalOutputCode (unsigned char channel, uint32_t *digitaloutputcode)
**     Description :
**         Reads the digital output code of a specific channel of the LDC 1614
**     Parameters  :
**         channel			   		   - channel to be read from
**        *digitaloutputcode		   - digitaloutputcode buffer for the value to be stored in
**     Returns     :
**         ---             - Error code, returns ERR_OK if I2C
**         				     communication was successful
** ===================================================================
*/
uint8_t LDC_getDigitalOutputCode(unsigned char channel, uint32_t *digitaloutputcode){
	uint8_t retVal = ERR_OK;
	uint16_t v[2] = {0,0};
	if (channel == 0){
		retVal &= LDC_readWordAddress8((uint8_t) DATA0_MSB, &v[1]);			// get value in Register DATA0_MSB
		WAIT1_Waitms(1);
		retVal &= LDC_readWordAddress8((uint8_t) DATA0_LSB, &v[0]);			// get value in Register DATA0_LSB
		WAIT1_Waitms(1);
		*digitaloutputcode = ((uint32_t) (v[1]<<16) | v[0]) & 0xFFFFFFF;	// remove bit 31-28 (error information)
	}
	else if (channel == 1){
		retVal &= LDC_readWordAddress8((uint8_t) DATA1_MSB, &v[1]);			// get value in Register DATA0_MSB
		WAIT1_Waitms(1);
		retVal &= LDC_readWordAddress8((uint8_t) DATA1_LSB, &v[0]);			// get value in Register DATA0_LSB
		WAIT1_Waitms(1);
		*digitaloutputcode = ((uint32_t) (v[1]<<16) | v[0]) & 0xFFFFFFF;	// remove bit 31-28 (error information)
	}

	else if (channel == 2 && numberOfActivatedChannels >= 3){
		retVal &= LDC_readWordAddress8((uint8_t) DATA2_MSB, &v[1]);			// get value in Register DATA0_MSB
		WAIT1_Waitms(1);
		retVal &= LDC_readWordAddress8((uint8_t) DATA2_LSB, &v[0]);			// get value in Register DATA0_LSB
		WAIT1_Waitms(1);
		*digitaloutputcode = ((uint32_t) (v[1]<<16) | v[0]) & 0xFFFFFFF;	// remove bit 31-28 (error information)
	}

	else if (channel == 3 && numberOfActivatedChannels == 4){
		retVal &= LDC_readWordAddress8((uint8_t) DATA3_MSB, &v[1]);			// get value in Register DATA0_MSB
		WAIT1_Waitms(1);
		retVal &= LDC_readWordAddress8((uint8_t) DATA3_LSB, &v[0]);			// get value in Register DATA0_LSB
		WAIT1_Waitms(1);
		*digitaloutputcode = ((uint32_t) (v[1]<<16) | v[0]) & 0xFFFFFFF;	// remove bit 31-28 (error information)
	}
	else{
		retVal = ERR_RANGE;	// Channel not activated
		*digitaloutputcode = 0;
	}
	return retVal;
}

/*
** ===================================================================
**     Method      :  LDC_writeConfig(uint8_t deviceregister, uint16_t value)
**     Description :
**         writes the specific configuration into the i2C register of the LDC1614
**     Parameters  :
**         deviceregister	   		   - specific configuration register
**         value		   			   - configuration value
**     Returns     :
**         ---             - Error code, returns ERR_OK if I2C
**         				     communication was successful
** ===================================================================
*/
uint8_t LDC_writeConfig(uint8_t deviceregister, uint16_t value){
	uint8_t retVal = ERR_OK;
	retVal &= LDC_writeWordAddress8(LDC_DEFAULT_I2CADDR, CONFIG, VAL_DEFAULT_CONFIG_NO_CONVERSION);	// set LDC Conversion inactive (Configuration mode)
	retVal &= LDC_writeWordAddress8(LDC_DEFAULT_I2CADDR, deviceregister, value);
	retVal &= LDC_writeWordAddress8(LDC_DEFAULT_I2CADDR, CONFIG, VAL_DEFAULT_CONFIG_START_CONVERSION); // start LDC Conversion
}

/*
** ===================================================================
**     Method      :  LDC_readConfig(uint8_t deviceregister, uint16_t *value)
**     Description :
**         reads the configuration data of a specific LDC1614 register
**     Parameters  :
**         deviceregister	   		   - specific configuration register
**         *value		   			   - pointer to configuration data
**     Returns     :
**         ---             - Error code, returns ERR_OK if I2C
**         				     communication was successful
** ===================================================================
**/
uint8_t LDC_readConfig(uint8_t deviceregister, uint16_t *value){
	uint8_t retVal = ERR_OK;
	retVal &= LDC_readWordAddress8(deviceregister, value);
	return retVal;
}

void setNumberofActivatedChannels(unsigned char value){
	numberOfActivatedChannels = value;
}

unsigned char getNumberofActivatedChannels(){
	return numberOfActivatedChannels;
}




