/*
 * dfplayer.c
 *
 * Created: 5/20/2017 12:37:57 AM
 *  Author: Cardoz
 *
 * Functions to access the status of DFPlayer Module. Send Commands.
 *  Note we are using micro-SD card is U-Disk for this module. Hence, while quering the number 
 * of files on card use the 'Query U-Disk files' command
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "Atmega_Uart.h"
#include "Dfplayer.h"

/************************************************************************/
/*		Function to send a command to the DFplayer
	
	argument 1: Type of command. Refer Dfplayer.h for command name definitions
	argument 2: Parameter to the command         
	                                                            
/************************************************************************/
void dfplayer_Cmd(uint8_t cmd, uint16_t parameter)
{
	uint8_t cmdlenght = 0x06;			// Currently all commands that'll be used have a lenght of 6. So this is fixed
	uint8_t tempholder = 0;

	/*	Create the CMD string	*/
	cmdbuffer[0] = CMD_STRT_BYTE;
	cmdbuffer[1] = CMD_VER;
	cmdbuffer[2] = cmdlenght;
	cmdbuffer[3] = cmd;
	cmdbuffer[4] = CMD_RECV_NFB;
	cmdbuffer[5] = parameter / 256;
	cmdbuffer[6] = parameter % 256;
	cmdbuffer[7] = CMD_END_BYTE;

	Usart_Send_Array(cmdbuffer, CMD_BUFFER_SIZE);

/*************************************************************************/
/*  If Commands are query based, a immediate response will be received
/*************************************************************************/
	_delay_ms(10);
	if(Is_Buffer_Empty == BUFFER_NOT_EMPTY)
	{
		do{
			tempholder = Ring_Remove();
		}while(tempholder != CMD_STRT_BYTE);
		tempholder = Ring_Remove();				// Remove the VER byte from the buffer
		tempholder = Ring_Remove();				// Remove the CMD byte from the buffer
	}
	
	
}

