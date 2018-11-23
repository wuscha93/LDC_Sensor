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
	uint32_t data;	// data received from LDC1614
	uint32_t val;	// command value (e.g. Channel, settings)
	unsigned char data_string[32];	// string to send information
	const unsigned char *p;
	uint8_t retVal = ERR_OK;

	if (UTIL1_strncmp(cmd, "getDigitalOutputCode ", sizeof("getDigitalOutputCode ")-1)==0){		// get DigitalOutput Code of Channel 0
		p = cmd+sizeof("getDigitalOutputCode ")-1;
		if (UTIL1_xatoi(&p, &val)==ERR_OK) {
			if(LDC_getDigitalOutputCode((unsigned char) val, &data)){	// if I2C communication corrupted -> data = -1
				data = 0;	// data corrupted
			}
		}
		UTIL1_Num32uToStr(&data_string[0], sizeof(data_string), data);
		(void)CDC1_SendString((unsigned char*)data_string);
	}
}
