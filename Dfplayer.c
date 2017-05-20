/*
 * dfplayer.c
 *
 * Created: 5/20/2017 12:37:57 AM
 *  Author: Cardoz
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
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

	/*	Create the CMD string	*/
	cmdbuffer[0] = CMD_STRT_BYTE;
	cmdbuffer[1] = CMD_VER;
	cmdbuffer[2] = cmdlenght;
	cmdbuffer[3] = cmd;
	cmdbuffer[4] = CMD_RECV_FB;
	cmdbuffer[5] = parameter / 256;
	cmdbuffer[6] = parameter % 256;
	cmdbuffer[7] = CMD_END_BYTE;

	Usart_Send_Array(cmdbuffer, CMD_BUFFER_SIZE);
}