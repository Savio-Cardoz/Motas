<<<<<<< HEAD:Code/Motas/Motas/Main.c
/*
 * MOTAS.c
 *
 * Created: 5/17/2017 10:53:48 PM
 *  Author: Cardoz
 */

 
/*
 *	Using the factory default internal RC oscillator
*/ 
#include "Atmega_Config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Atmega_Uart.h"
#include "Dfplayer.h"
#include "Peripheral_Drivers.h"


int main(void)
{
	Atmega_init();
	
    while(1)
    {
		
		_delay_ms(1000);
		
		Dfplayer_Cmd(CMD_PLY_TRCK, 1);
		_delay_ms(100000);
		
		RELAY_ON;
		_delay_ms(3000);
		RELAY_OFF;
		_delay_ms(3000);
    }
}
=======
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
>>>>>>> d5173597cd6c2b844bd0b62452b248138da284ed:Main.c
