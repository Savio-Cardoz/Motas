/*
 * MOTAS.c
 *
 * Created: 5/17/2017 10:53:48 PM
 *  Author: Cardoz
 */ 
#define F_CPU 11059200UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Atmega_Uart.h"
#include "Dfplayer.h"
#include "Peripheral_Drivers.h"
#include "Atmega_Config.h"

int main(void)
{
	/*Initialize the Project*/
	Atmega_init();
		
    while(1)
    {
    	//Implement some delay if required

    	/*Call the main function of the state machine */
		MotasController();
    }
}
