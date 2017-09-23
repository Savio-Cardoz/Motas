/*
 * Atmega_Config.h
 *
 * Created: 5/23/2017 10:54:53 PM
 *  Author: Cardoz
 */ 


#ifndef ATMEGA_CONFIG_H_
#define ATMEGA_CONFIG_H_

//This is used to switch ON/OFF Debugging. Comment for switching the debugging mode to off.
//#define DEBUG_ON
#ifndef F_CPU
#define F_CPU 1000000UL
#endif

typedef struct			// Using to access individual bits/pins of a register/port
{
	unsigned int bit0:1;
	unsigned int bit1:1;
	unsigned int bit2:1;
	unsigned int bit3:1;
	unsigned int bit4:1;
	unsigned int bit5:1;
	unsigned int bit6:1;
	unsigned int bit7:1;
} _io_reg;

#define REGISTER_BIT(rg,bt) ((volatile _io_reg*)&rg)->bit##bt

void Atmega_init();


#endif /* ATMEGA_CONFIG_H_ */