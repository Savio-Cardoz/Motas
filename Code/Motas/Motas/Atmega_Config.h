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

void Atmega_init();


#endif /* ATMEGA_CONFIG_H_ */