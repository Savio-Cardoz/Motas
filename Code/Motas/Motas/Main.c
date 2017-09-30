/*
 * MOTAS.c
 *
 * Created: 5/17/2017 10:53:48 PM
 *  Author: Cardoz
 */

 
/*
 *	Using the factory default internal RC oscillator
*/ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Atmega_Uart.h"
#include "Dfplayer.h"
#include "Peripheral_Drivers.h"
#include "Atmega_Config.h"
#include "Motas_Controller.h"
#include "debug_func.h"



int main(void)
{
	Atmega_init();
	SendDebug("initizd");
	
    while(1)
    {
		MotasController();
    }
}