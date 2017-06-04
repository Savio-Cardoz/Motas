/*
 * Atmega_Config.c
 *
 * Created: 5/23/2017 10:55:15 PM
 *  Author: Cardoz
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Atmega_Config.h"
#include "Peripheral_Drivers.h"

void Atmega_init()
{
	USART_Init();
	
#ifdef DEBUG_ON
	SendDebug("Serial OK!");
#endif // DEBUG_ON
	
	Init_Ultrasonic_Sensor();
	Init_Pir();
	Init_Timer1();
	sei();
}