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

// Variables
static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];
static uint8_t in_buffer[USB1_DATA_BUFF_SIZE];

static void CDC_Run(){
	int i = 0;
	uint32_t val = 0;
	unsigned char buf[16];

	for(;;) {
	  while(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))==ERR_BUSOFF) {
	    /* device not enumerated */
	    LED1_Neg();
	    WAIT1_Waitms(10);
	  }
	  LED1_Off();
	  if (CDC1_GetCharsInRxBuf()!=0) {
	    i = 0;
	    while(i<sizeof(in_buffer)-1 && CDC1_GetChar(&in_buffer[i])==ERR_OK) {
	      i++;
	    }
	    in_buffer[i] = '\0';
	    (void)CDC1_SendString((unsigned char*)"echo: ");
	    (void)CDC1_SendString(in_buffer);
	    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"val: ");
	    UTIL1_strcatNum32u(buf, sizeof(buf), val);
	    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
	    (void)CDC1_SendString(buf);
	    val++;
	  } else {
	    WAIT1_Waitms(10);
	  }
	}
}


void APP_Run(void) {
	CDC_Run();
}
