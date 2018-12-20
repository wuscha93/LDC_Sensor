/*
 * Handle_Command.h
 *
 *  Created on: Nov 23, 2018
 *  Author: Adrian Bucher
 */

#ifndef __HANDLE_COMMAND_H_
#define __HANDLE_COMMAND_H_

/****************************
   global variabless
****************************/

#define OUTPUTCODE_UPPER_LIMIT 100000000 // if outputcode of a channel is higher than this limit
									     // no sensor is connected to this channel

void handleCommand(uint8_t *cmd);

void send_I2CError(void);

#endif /* SOURCES_HANDLE_COMMAND_H_ */
