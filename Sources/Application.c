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
	uint32_t val = 0;
	unsigned char buf[16];

	  if(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))==ERR_BUSOFF) {						// while no USB CDC connection
	    /* device not enumerated */
	    WAIT1_Waitms(2);
	  }
	  else{																					// check USB CDC input buffer
		  //LED1_Off();
		  if (CDC1_GetCharsInRxBuf()!=0) {													// if input buffer != zero
			  WAIT1_Waitms(1);
			  i = 0;																		// call handleCommand()
			  while(i<sizeof(in_buffer)-1 && CDC1_GetChar(&in_buffer[i])==ERR_OK) {
				  i++;
			  }
			  in_buffer[i] = '\0';
			  handleCommand(in_buffer);
		  } else {
			  WAIT1_Waitms(1);
		  }
	  }
}


void APP_Run(void) {
	LED1_Off();
	for(;;){
		CDC_Run();
	}
}
