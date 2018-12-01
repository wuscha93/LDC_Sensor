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
	uint32_t data32;					// 32 bit data buffer
	uint16_t data16;					// 16 bit data buffer
	uint32_t channel;					// LDC1614 channel
	uint32_t val;						// configuration value
	uint16_t registerValue;				// LDC1614 I2C register
	unsigned char data_string[32];		// string-buffer to send information back to PC
	const unsigned char *p;
	uint8_t retVal = ERR_OK;

	if((UTIL1_strcmp(cmd, "LDCInit")==0) || (UTIL1_strcmp(cmd, "LDCInit\n")==0)){				// Initialize LDC1614 with check if LDC1614 is active
		if(LDC_Init() != ERR_OK){																// Notify via USB CDC if LC1614 could not be initialized
			(void)CDC1_SendString((unsigned char*)"Error tinyk20: LDCinit()");
		} else{
			(void)CDC1_SendString((unsigned char*)"LDC1614 initialized");
		  }
	}
	else if(UTIL1_strncmp(cmd, "getDigitalOutputCode ", sizeof("getDigitalOutputCode ")-1)==0){	// get DigitalOutput Code
		p = cmd+sizeof("getDigitalOutputCode ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK) {
			if(LDC_getDigitalOutputCode((unsigned char) channel, &data32) != ERR_OK){			// Notify via USB CDC if I2C communication is corrupted
				(void)CDC1_SendString((unsigned char*)"Error tinyk20: getDOC");
			}
			else if (data32 > 100000000) { 														// if Digital output-code is too high -> Sensor not plugged in
					data32 = 0;																	// set digital output code to zero
				 }
				 UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), data32);
				 (void)CDC1_SendString((unsigned char*)data_string);
		}
	}

	else if((UTIL1_strcmp(cmd, "getSTATUS")==0) || (UTIL1_strcmp(cmd, "getSTATUS\n")==0)){		// get data of LDC1614 STATUS register
		if (LDC_readWordAddress8(STATUS, &data16) != ERR_OK) {									// Notify via USB CDC if I2C communication is corrupted
			(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");
		}
		else {
			UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), data16);
			(void)CDC1_SendString((unsigned char*)data_string);
		}

	}

	else if(UTIL1_strncmp(cmd, "setRCOUNT ", sizeof("setRCOUNT ")-1)==0){						// set data of LDC1614 RCOUNT register

		p = cmd+sizeof("setRCOUNT ")-1;
		retVal |= UTIL1_xatoi(&p, &channel);
		retVal |= UTIL1_xatoi(&p, &val);
		if (retVal == ERR_OK) {
			if(channel == 0) {retVal |= LDC_writeConfig((uint8_t) RCOUNT0, (uint16_t) val);}
			if(channel == 1) {retVal |= LDC_writeConfig((uint8_t) RCOUNT1, (uint16_t) val);}
			if(channel == 2) {retVal |= LDC_writeConfig((uint8_t) RCOUNT2, (uint16_t) val);}
			if(channel == 3) {retVal |= LDC_writeConfig((uint8_t) RCOUNT3, (uint16_t) val);}
		}

		if (retVal != ERR_OK){
			(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");				// Notify via USB CDC if I2C communication is corrupted
		}
		else{
			(void)CDC1_SendString((unsigned char*)"configuration successful");
		}
	}

	else if(UTIL1_strncmp(cmd, "getRCOUNT ", sizeof("getRCOUNT ")-1)==0){						// get data of LDC1614 RCOUNT register
		p = cmd+sizeof("getRCOUNT ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK) {
			if(channel == 0) {retVal |= LDC_readConfig((uint8_t) RCOUNT0, &data16);}
			if(channel == 1) {retVal |= LDC_readConfig((uint8_t) RCOUNT1, &data16);}
			if(channel == 2) {retVal |= LDC_readConfig((uint8_t) RCOUNT2, &data16);}
			if(channel == 3) {retVal |= LDC_readConfig((uint8_t) RCOUNT3, &data16);}

			if (retVal != ERR_OK){
				(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");			// Notify via USB CDC if I2C communication is corrupted
			}
			else{
				UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
				(void)CDC1_SendString((unsigned char*)data_string);
			}
		}
	}

	else if(UTIL1_strncmp(cmd, "setOFFSET ", sizeof("setOFFSET ")-1)==0){						// set data of LDC1614 OFFSET register
		p = cmd+sizeof("setOFFSET ")-1;

		retVal |= UTIL1_xatoi(&p, &channel);
		retVal |= UTIL1_xatoi(&p, &val);
		if (retVal == ERR_OK) {
			if(channel == 0) {retVal |= LDC_writeConfig((uint8_t) OFFSET0, (uint16_t) val);}
			if(channel == 1) {retVal |= LDC_writeConfig((uint8_t) OFFSET1, (uint16_t) val);}
			if(channel == 2) {retVal |= LDC_writeConfig((uint8_t) OFFSET2, (uint16_t) val);}
			if(channel == 3) {retVal |= LDC_writeConfig((uint8_t) OFFSET3, (uint16_t) val);}
		}

		if (retVal != ERR_OK){
			(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");				// Notify via USB CDC if I2C communication is corrupted
		}
		else{
			(void)CDC1_SendString((unsigned char*)"configuration successful");
		}
	}

	else if(UTIL1_strncmp(cmd, "getOFFSET ", sizeof("getOFFSET ")-1)==0){						// get data of LDC1614 OFFSET register
		p = cmd+sizeof("getOFFSET ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK) {
			if(channel == 0) {retVal |= LDC_readConfig((uint8_t) OFFSET0, &data16);}
			if(channel == 1) {retVal |= LDC_readConfig((uint8_t) OFFSET1, &data16);}
			if(channel == 2) {retVal |= LDC_readConfig((uint8_t) OFFSET2, &data16);}
			if(channel == 3) {retVal |= LDC_readConfig((uint8_t) OFFSET3, &data16);}

			if (retVal != ERR_OK){
				(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");			// Notify via USB CDC if I2C communication is corrupted
			}
			else{
				UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
				(void)CDC1_SendString((unsigned char*)data_string);
			}
		}
	}

	else if(UTIL1_strncmp(cmd, "setSETTLECOUNT ", sizeof("setSETTLECOUNT ")-1)==0){				// set data of LDC1614 SETTLECOUNT register
		p = cmd+sizeof("setSETTLECOUNT ")-1;

		retVal |= UTIL1_xatoi(&p, &channel);
		retVal |= UTIL1_xatoi(&p, &val);
		if (retVal == ERR_OK) {
			if(channel == 0) {retVal |= LDC_writeConfig((uint8_t) SETTLECOUNT0, (uint16_t) val);}
			if(channel == 1) {retVal |= LDC_writeConfig((uint8_t) SETTLECOUNT1, (uint16_t) val);}
			if(channel == 2) {retVal |= LDC_writeConfig((uint8_t) SETTLECOUNT2, (uint16_t) val);}
			if(channel == 3) {retVal |= LDC_writeConfig((uint8_t) SETTLECOUNT3, (uint16_t) val);}
		}

		if (retVal != ERR_OK){
			(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");				// Notify via USB CDC if I2C communication is corrupted
		}
		else{
			(void)CDC1_SendString((unsigned char*)"configuration successful");
		}
	}

	else if(UTIL1_strncmp(cmd, "getSETTLECOUNT ", sizeof("getSETTLECOUNT ")-1)==0){				// get data of LDC1614 SETTLECOUNT register
		p = cmd+sizeof("getSETTLECOUNT ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK) {
			if(channel == 0) {retVal |= LDC_readConfig((uint8_t) SETTLECOUNT0, &data16);}
			if(channel == 1) {retVal |= LDC_readConfig((uint8_t) SETTLECOUNT1, &data16);}
			if(channel == 2) {retVal |= LDC_readConfig((uint8_t) SETTLECOUNT2, &data16);}
			if(channel == 3) {retVal |= LDC_readConfig((uint8_t) SETTLECOUNT3, &data16);}

			if (retVal != ERR_OK){
				(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");		    // Notify via USB CDC if I2C communication is corrupted
			}
			else{
				UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
				(void)CDC1_SendString((unsigned char*)data_string);
			}
		}
	}

	else if(UTIL1_strncmp(cmd, "setCLOCK_DIVIDERS ", sizeof("setCLOCK_DIVIDERS ")-1)==0){		// set data of LDC1614 CLOCK_DIVIDERS register
		p = cmd+sizeof("setCLOCK_DIVIDERS ")-1;

		retVal |= UTIL1_xatoi(&p, &channel);
		retVal |= UTIL1_xatoi(&p, &val);
		if (retVal == ERR_OK) {
			if(channel == 0) {retVal |= LDC_writeConfig((uint8_t) CLOCK_DIVIDERS0, (uint16_t) val);}
			if(channel == 1) {retVal |= LDC_writeConfig((uint8_t) CLOCK_DIVIDERS1, (uint16_t) val);}
			if(channel == 2) {retVal |= LDC_writeConfig((uint8_t) CLOCK_DIVIDERS2, (uint16_t) val);}
			if(channel == 3) {retVal |= LDC_writeConfig((uint8_t) CLOCK_DIVIDERS3, (uint16_t) val);}
		}

		if (retVal != ERR_OK){
			(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");				// Notify via USB CDC if I2C communication is corrupted
		}
		else{
			(void)CDC1_SendString((unsigned char*)"configuration successful");
		}
	}

	else if(UTIL1_strncmp(cmd, "getCLOCK_DIVIDERS ", sizeof("getCLOCK_DIVIDERS ")-1)==0){		// get data of LDC1614 CLOCK_DIVIDERS register
		p = cmd+sizeof("getCLOCK_DIVIDERS ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK) {
			if(channel == 0) {retVal |= LDC_readConfig((uint8_t) CLOCK_DIVIDERS0, &data16);}
			if(channel == 1) {retVal |= LDC_readConfig((uint8_t) CLOCK_DIVIDERS1, &data16);}
			if(channel == 2) {retVal |= LDC_readConfig((uint8_t) CLOCK_DIVIDERS2, &data16);}
			if(channel == 3) {retVal |= LDC_readConfig((uint8_t) CLOCK_DIVIDERS3, &data16);}

			if (retVal != ERR_OK){
				(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");			// Notify via USB CDC if I2C communication is corrupted
			}
			else{
				UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
				(void)CDC1_SendString((unsigned char*)data_string);
			}
		}
	}

	else if(UTIL1_strncmp(cmd, "setIdrive ", sizeof("setIdrive ")-1)==0){						// set data of LDC1614 DRIVE_CURRENT register
		p = cmd+sizeof("setIdrive ")-1;
		retVal |= UTIL1_xatoi(&p, &channel);
		retVal |= UTIL1_xatoi(&p, &val);

		if (retVal == ERR_OK) {
			if(channel == 0) {retVal |= LDC_readConfig((uint8_t) DRIVE_CURRENT0, &data16);}		// read current IDRIVE value
			if(channel == 1) {retVal |= LDC_readConfig((uint8_t) DRIVE_CURRENT1, &data16);}
			if(channel == 2) {retVal |= LDC_readConfig((uint8_t) DRIVE_CURRENT2, &data16);}
			if(channel == 3) {retVal |= LDC_readConfig((uint8_t) DRIVE_CURRENT3, &data16);}

			data16 &= 0x7FF;		    // delete current Idrive setting (bit 15:11 of IDRIVE register)
			data16 |= (val<<11);		// set new Idrive setting in temp register 	(bit 15:11 of IDRIVE register)

			if(channel == 0) {retVal |= LDC_writeConfig((uint8_t) DRIVE_CURRENT0, (uint16_t) data16);}
			if(channel == 1) {retVal |= LDC_writeConfig((uint8_t) DRIVE_CURRENT1, (uint16_t) data16);}
			if(channel == 2) {retVal |= LDC_writeConfig((uint8_t) DRIVE_CURRENT2, (uint16_t) data16);}
			if(channel == 3) {retVal |= LDC_writeConfig((uint8_t) DRIVE_CURRENT3, (uint16_t) data16);}
		}

		if (retVal != ERR_OK){
			(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");				// Notify via USB CDC if I2C communication is corrupted
		}
		else{
			(void)CDC1_SendString((unsigned char*)"configuration successful");
		}
	}

	else if(UTIL1_strncmp(cmd, "getIdrive ", sizeof("getIdrive ")-1)==0){						// get data of LDC1614 DRIVE_CURRENT register
		p = cmd+sizeof("getIdrive ")-1;
		if (UTIL1_xatoi(&p, &channel)==ERR_OK) {
			if(channel == 0) {retVal |= LDC_readConfig((uint8_t) DRIVE_CURRENT0, &data16);}
			if(channel == 1) {retVal |= LDC_readConfig((uint8_t) DRIVE_CURRENT1, &data16);}
			if(channel == 2) {retVal |= LDC_readConfig((uint8_t) DRIVE_CURRENT2, &data16);}
			if(channel == 3) {retVal |= LDC_readConfig((uint8_t) DRIVE_CURRENT3, &data16);}

			if (retVal != ERR_OK){
				(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");			// Notify via USB CDC if I2C communication is corrupted
			}
			else{
				data16 &= 0x7c0;		// send only current Idrive setting (bit 10:6)
				data16 = (data16>>6);
				UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
				(void)CDC1_SendString((unsigned char*)data_string);
			}
		}

	}

	else if(UTIL1_strncmp(cmd, "setNumberOfChannels ", sizeof("setNumberOfChannels ")-1)==0){		// set number of active channels (multi channel mode)
		p = cmd+sizeof("setNumberOfChannels ")-1;

		retVal |= UTIL1_xatoi(&p, &val);
		if (retVal == ERR_OK) {
			registerValue = VAL_MUX_CONFIG & 0x9FFF; 				// temporary clear Auto-Scan Sequence Configuration
			registerValue |= ((val-2)<<13);			     			// temporary set new Auto-Scan Sequence Configuration
			retVal |= LDC_writeConfig((uint8_t) MUX_CONFIG, registerValue);
			setNumberofActivatedChannels(val);						// set global variable number of active channels
		}

		if (retVal != ERR_OK){
			(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");				// Notify via USB CDC if I2C communication is corrupted
		}
		else{
			(void)CDC1_SendString((unsigned char*)"configuration successful");
		}

	}

	else if((UTIL1_strcmp(cmd, "getNumberOfChannels")==0) || (UTIL1_strcmp(cmd, "getNumberOfChannels\n")==0)){		// get number of active channels (multi channel mode)
		UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) getNumberofActivatedChannels());
		(void)CDC1_SendString((unsigned char*)data_string);
	}


	else if(UTIL1_strncmp(cmd, "setERROR_CONFIG ", sizeof("setERROR_CONFIG ")-1)==0){								// set data of LDC1614 ERROR_CONFIG register
		p = cmd+sizeof("setERROR_CONFIG ")-1;

		retVal |= UTIL1_xatoi(&p, &val);
		if (retVal == ERR_OK) {
			retVal |= LDC_writeConfig((uint8_t) ERROR_CONFIG, (uint16_t) val);
		}

		if (retVal != ERR_OK){
			(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");				// Notify via USB CDC if I2C communication is corrupted
		}
		else{
			(void)CDC1_SendString((unsigned char*)"configuration successful");
		}
	}

	else if((UTIL1_strcmp(cmd, "getERROR_CONFIG")==0) || (UTIL1_strcmp(cmd, "getERROR_CONFIG\n")==0)){	// get data of LDC1614 ERROR_CONFIG register
		if(LDC_readConfig((uint8_t) ERROR_CONFIG, &data16) != ERR_OK){
			(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");				// Notify via USB CDC if I2C communication is corrupted
		} else{
			UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
			(void)CDC1_SendString((unsigned char*)data_string);
		}

	}

	else if(UTIL1_strncmp(cmd, "setCONFIG ", sizeof("setCONFIG ")-1)==0){								// set data of LDC1614 CONFIG register
		p = cmd+sizeof("setCONFIG ")-1;

		retVal |= UTIL1_xatoi(&p, &val);
		if (retVal == ERR_OK) {
			retVal |= LDC_writeConfig((uint8_t) CONFIG, (uint16_t) val);
		}

		if (retVal != ERR_OK){
			(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");				// Notify via USB CDC if I2C communication is corrupted
		}
		else{
			(void)CDC1_SendString((unsigned char*)"configuration successful");
		}
	}

	else if((UTIL1_strcmp(cmd, "getCONFIG")==0) || (UTIL1_strcmp(cmd, "getCONFIG\n")==0)){				// get data of LDC1614 CONFIG register
			if(LDC_readConfig((uint8_t) CONFIG, &data16) != ERR_OK){
				(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");					// Notify via USB CDC if I2C communication is corrupted
			}
			else{
				UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
				(void)CDC1_SendString((unsigned char*)data_string);
			}

	}

	else if(UTIL1_strncmp(cmd, "setMUX_CONFIG ", sizeof("setMUX_CONFIG ")-1)==0){						// set data of LDC1614 MUX_CONFIG register
		p = cmd+sizeof("setMUX_CONFIG ")-1;

		retVal |= UTIL1_xatoi(&p, &val);
		if (retVal == ERR_OK) {
			retVal |= LDC_writeConfig((uint8_t) MUX_CONFIG, (uint16_t) val);
		}

		if (retVal != ERR_OK){
			(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");				// Notify via USB CDC if I2C communication is corrupted
		}
		else{
			(void)CDC1_SendString((unsigned char*)"configuration successful");
		}
	}

	else if((UTIL1_strcmp(cmd, "getMUX_CONFIG")==0) || (UTIL1_strcmp(cmd, "getMUX_CONFIG\n")==0)){		// get data of LDC1614 MUX_CONFIG register
			if(LDC_readConfig((uint8_t) MUX_CONFIG, &data16) != ERR_OK){
				(void)CDC1_SendString((unsigned char*)"Error tinyk20: configuration");				// Notify via USB CDC if I2C communication is corrupted
			}
			else{
				UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), (uint32_t) data16);
				(void)CDC1_SendString((unsigned char*)data_string);
			}
	}
	else{
		(void)CDC1_SendString((unsigned char*)"Error tinyk20: command not found");
	}
}

