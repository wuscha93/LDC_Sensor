/*
 * Handle_Command.c
 *
 *  Created on: Nov 23, 2018
 *      Author: ADRIAN
 */


#include "UTIL1.h"
#include "LDC_I2C.h"
#include "CDC1.h"

void handleCommand(uint8_t *cmd){
	uint32_t data32;					// 32bit data received from LDC1614
	uint16_t data16;					// 16bit data received from LDC1614
	uint32_t channel;					// channel
	uint32_t val;						// config value
	uint16_t registerValue;
	unsigned char data_string[32];		// string to send information
	const unsigned char *p;
	uint8_t retVal = ERR_OK;

	if(UTIL1_strncmp(cmd, "getDigitalOutputCode ", sizeof("getDigitalOutputCode ")-1)==0){		// get DigitalOutput Code of Channel 0
		p = cmd+sizeof("getDigitalOutputCode ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK) {
			if(LDC_getDigitalOutputCode((unsigned char) channel, &data32)){	// if I2C communication corrupted -> data = -1
				data32 = 0;	// data corrupted
			}
		}
		UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), data32);
		(void)CDC1_SendString((unsigned char*)data_string);
	}

	if((UTIL1_strcmp(cmd, "getSTATUS")==0) || (UTIL1_strcmp(cmd, "getSTATUS\n")==0)){		// get DigitalOutput Code of Channel 0
		LDC_readWordAddress8(STATUS, &data16);
		UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), data16);
		(void)CDC1_SendString((unsigned char*)data_string);
	}

	if(UTIL1_strncmp(cmd, "setRCOUNT ", sizeof("setRCOUNT ")-1)==0){		//
		p = cmd+sizeof("setRCOUNT ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK && UTIL1_xatoi(&p, &val)==ERR_OK) {
			if(channel == 0) {LDC_writeConfig((uint8_t) RCOUNT0, (uint16_t) val);};
			if(channel == 1) {LDC_writeConfig((uint8_t) RCOUNT1, (uint16_t) val);};
			if(channel == 2) {LDC_writeConfig((uint8_t) RCOUNT2, (uint16_t) val);};
			if(channel == 3) {LDC_writeConfig((uint8_t) RCOUNT3, (uint16_t) val);};
		}
	}

	if(UTIL1_strncmp(cmd, "getRCOUNT ", sizeof("getRCOUNT ")-1)==0){		//
		p = cmd+sizeof("getRCOUNT ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK) {
			if(channel == 0) {LDC_readConfig((uint8_t) RCOUNT0, &data16);};
			if(channel == 1) {LDC_readConfig((uint8_t) RCOUNT1, &data16);};
			if(channel == 2) {LDC_readConfig((uint8_t) RCOUNT2, &data16);};
			if(channel == 3) {LDC_readConfig((uint8_t) RCOUNT3, &data16);};
		}
		UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
		(void)CDC1_SendString((unsigned char*)data_string);
	}

	if(UTIL1_strncmp(cmd, "setOFFSET ", sizeof("setOFFSET ")-1)==0){		//
		p = cmd+sizeof("setOFFSET ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK && UTIL1_xatoi(&p, &val)==ERR_OK) {
			if(channel == 0) {LDC_writeConfig((uint8_t) OFFSET0, (uint16_t) val);};
			if(channel == 1) {LDC_writeConfig((uint8_t) OFFSET1, (uint16_t) val);};
			if(channel == 2) {LDC_writeConfig((uint8_t) OFFSET2, (uint16_t) val);};
			if(channel == 3) {LDC_writeConfig((uint8_t) OFFSET3, (uint16_t) val);};
		}
	}

	if(UTIL1_strncmp(cmd, "getOFFSET ", sizeof("getOFFSET ")-1)==0){		//
		p = cmd+sizeof("getOFFSET ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK) {
			if(channel == 0) {LDC_readConfig((uint8_t) OFFSET0, &data16);};
			if(channel == 1) {LDC_readConfig((uint8_t) OFFSET1, &data16);};
			if(channel == 2) {LDC_readConfig((uint8_t) OFFSET2, &data16);};
			if(channel == 3) {LDC_readConfig((uint8_t) OFFSET3, &data16);};
		}
		UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
		(void)CDC1_SendString((unsigned char*)data_string);
	}

	if(UTIL1_strncmp(cmd, "setSETTLECOUNT ", sizeof("setSETTLECOUNT ")-1)==0){		//
		p = cmd+sizeof("setSETTLECOUNT ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK && UTIL1_xatoi(&p, &val)==ERR_OK) {
			if(channel == 0) {LDC_writeConfig((uint8_t) SETTLECOUNT0, (uint16_t) val);};
			if(channel == 1) {LDC_writeConfig((uint8_t) SETTLECOUNT1, (uint16_t) val);};
			if(channel == 2) {LDC_writeConfig((uint8_t) SETTLECOUNT2, (uint16_t) val);};
			if(channel == 3) {LDC_writeConfig((uint8_t) SETTLECOUNT3, (uint16_t) val);};
		}
	}

	if(UTIL1_strncmp(cmd, "getSETTLECOUNT ", sizeof("getSETTLECOUNT ")-1)==0){		//
		p = cmd+sizeof("getSETTLECOUNT ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK) {
			if(channel == 0) {LDC_readConfig((uint8_t) SETTLECOUNT0, &data16);};
			if(channel == 1) {LDC_readConfig((uint8_t) SETTLECOUNT1, &data16);};
			if(channel == 2) {LDC_readConfig((uint8_t) SETTLECOUNT2, &data16);};
			if(channel == 3) {LDC_readConfig((uint8_t) SETTLECOUNT3, &data16);};
		}
		UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
		(void)CDC1_SendString((unsigned char*)data_string);
	}

	if(UTIL1_strncmp(cmd, "setCLOCK_DIVIDERS ", sizeof("setCLOCK_DIVIDERS ")-1)==0){		//
		p = cmd+sizeof("setCLOCK_DIVIDERS ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK && UTIL1_xatoi(&p, &val)==ERR_OK) {
			if(channel == 0) {LDC_writeConfig((uint8_t) CLOCK_DIVIDERS0, (uint16_t) val);};
			if(channel == 1) {LDC_writeConfig((uint8_t) CLOCK_DIVIDERS1, (uint16_t) val);};
			if(channel == 2) {LDC_writeConfig((uint8_t) CLOCK_DIVIDERS2, (uint16_t) val);};
			if(channel == 3) {LDC_writeConfig((uint8_t) CLOCK_DIVIDERS3, (uint16_t) val);};
		}
	}

	if(UTIL1_strncmp(cmd, "getCLOCK_DIVIDERS ", sizeof("getCLOCK_DIVIDERS ")-1)==0){		//
		p = cmd+sizeof("getCLOCK_DIVIDERS ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK) {
			if(channel == 0) {LDC_readConfig((uint8_t) CLOCK_DIVIDERS0, &data16);};
			if(channel == 1) {LDC_readConfig((uint8_t) CLOCK_DIVIDERS1, &data16);};
			if(channel == 2) {LDC_readConfig((uint8_t) CLOCK_DIVIDERS2, &data16);};
			if(channel == 3) {LDC_readConfig((uint8_t) CLOCK_DIVIDERS3, &data16);};
		}
		UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
		(void)CDC1_SendString((unsigned char*)data_string);
	}

	if(UTIL1_strncmp(cmd, "setDRIVE_CURRENT ", sizeof("setDRIVE_CURRENT ")-1)==0){		//
		p = cmd+sizeof("setDRIVE_CURRENT ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK && UTIL1_xatoi(&p, &val)==ERR_OK) {
			if(channel == 0) {LDC_writeConfig((uint8_t) DRIVE_CURRENT0, (uint16_t) val);};
			if(channel == 1) {LDC_writeConfig((uint8_t) DRIVE_CURRENT1, (uint16_t) val);};
			if(channel == 2) {LDC_writeConfig((uint8_t) DRIVE_CURRENT2, (uint16_t) val);};
			if(channel == 3) {LDC_writeConfig((uint8_t) DRIVE_CURRENT3, (uint16_t) val);};
		}
	}

	if(UTIL1_strncmp(cmd, "getDRIVE_CURRENT ", sizeof("getDRIVE_CURRENT ")-1)==0){		//
		p = cmd+sizeof("getDRIVE_CURRENT ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK) {
			if(channel == 0) {LDC_readConfig((uint8_t) DRIVE_CURRENT0, &data16);};
			if(channel == 1) {LDC_readConfig((uint8_t) DRIVE_CURRENT1, &data16);};
			if(channel == 2) {LDC_readConfig((uint8_t) DRIVE_CURRENT2, &data16);};
			if(channel == 3) {LDC_readConfig((uint8_t) DRIVE_CURRENT3, &data16);};
		}

		data16 &= 0x7c0;		// only current Idrive setting
		data16 = (data16>>6);
		UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
		(void)CDC1_SendString((unsigned char*)data_string);
	}

	if(UTIL1_strncmp(cmd, "setNUMBEROFCHANNELS ", sizeof("setNUMBEROFCHANNELS ")-1)==0){		//
		p = cmd+sizeof("setNUMBEROFCHANNELS ")-1;
		if (UTIL1_xatoi(&p, &val)==ERR_OK) {
			registerValue = VAL_MUX_CONFIG & 0x9FFF; 				// temporary clear Auto-Scan Sequence Configuration
			registerValue |= ((val-2)<<13);			     			// temporary set new Auto-Scan Sequence Configuration
			LDC_writeConfig((uint8_t) MUX_CONFIG, registerValue);
			setNumberofActivatedChannels(val);						// set global variable number of active channels
		}
	}

	if((UTIL1_strcmp(cmd, "getNUMBEROFCHANNELS")==0) || (UTIL1_strcmp(cmd, "getNUMBEROFCHANNELS\n")==0)){		//
		UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) getNumberofActivatedChannels());
		(void)CDC1_SendString((unsigned char*)data_string);
	}

	if(UTIL1_strncmp(cmd, "setERROR_CONFIG ", sizeof("setERROR_CONFIG ")-1)==0){		//
		p = cmd+sizeof("setERROR_CONFIG ")-1;
		if (UTIL1_xatoi(&p, &val)==ERR_OK) {
			LDC_writeConfig((uint8_t) ERROR_CONFIG, (uint16_t) val);
		}
	}

	if((UTIL1_strcmp(cmd, "getERROR_CONFIG")==0) || (UTIL1_strcmp(cmd, "getERROR_CONFIG\n")==0)){		//
			LDC_readConfig((uint8_t) ERROR_CONFIG, &data16);
			UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
			(void)CDC1_SendString((unsigned char*)data_string);
	}

	if(UTIL1_strncmp(cmd, "setCONFIG ", sizeof("setCONFIG ")-1)==0){		//
		p = cmd+sizeof("setCONFIG ")-1;
		if (UTIL1_xatoi(&p, &val)==ERR_OK) {
			LDC_writeConfig((uint8_t) CONFIG, (uint16_t) val);
		}
	}

	if((UTIL1_strcmp(cmd, "getCONFIG")==0) || (UTIL1_strcmp(cmd, "getCONFIG\n")==0)){		//
			LDC_readConfig((uint8_t) CONFIG, &data16);
			UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
			(void)CDC1_SendString((unsigned char*)data_string);
	}

	if(UTIL1_strncmp(cmd, "setMUX_CONFIG ", sizeof("setMUX_CONFIG ")-1)==0){		//
		p = cmd+sizeof("setMUX_CONFIG ")-1;
		if (UTIL1_xatoi(&p, &val)==ERR_OK) {
			LDC_writeConfig((uint8_t) MUX_CONFIG, (uint16_t) val);
		}
	}

	if((UTIL1_strcmp(cmd, "getMUX_CONFIG")==0) || (UTIL1_strcmp(cmd, "getMUX_CONFIG\n")==0)){		//
			LDC_readConfig((uint8_t) MUX_CONFIG, &data16);
			UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
			(void)CDC1_SendString((unsigned char*)data_string);
	}
}
