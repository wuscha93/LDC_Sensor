/*
 * Application.c
 *
 *  Created on: Nov 16, 2018
 *      Author: ADRIAN
 */

#include "Application.h"
#include "CDC1.h"
#include "LED1.h"
#include "UTIL1.h"
#include "USB1.h"
#include "SD.h"
#include "ADDR.h"
#include "GI2C1.h"
#include "LDC_I2C.h"
#include "WAIT1.h"
#include "Handle_Command.h"

// Variables
static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];
static uint8_t in_buffer[USB1_DATA_BUFF_SIZE];

static void CDC_Run(){
	int i = 0;

	if(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))==ERR_BUSOFF) {						// USB CDC connection every 2ms
	  /* device not enumerated */
	  WAIT1_Waitms(2);
	}
	else{																				// check USB CDC input buffer
		if (CDC1_GetCharsInRxBuf()!=0) {												// if data received
		 WAIT1_Waitms(1);																// wait to receive full data string
			i = 0;
			while(i<sizeof(in_buffer)-1 && CDC1_GetChar(&in_buffer[i])==ERR_OK) {
		      i++;
			}
			in_buffer[i] = '\0';
			handleCommand(in_buffer);													// call handleCommand()
		} else {
			WAIT1_Waitms(1);															// no data received yet
		}
	}
}


void APP_Run(void) {
	LED1_Off();
	for(;;){
		CDC_Run();
	}
}
