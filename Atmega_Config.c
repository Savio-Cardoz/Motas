/*
 * Atmega_Config.c
 *
 * Created: 5/23/2017 10:55:15 PM
 *  Author: Cardoz
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Atmega_Config.h"

void Atmega_init()
{
	USART_Init();
	USART_putstring("Serial OK!");
	Init_Ultrasonic_Sensor();
	Init_Pir();
	sei();
}