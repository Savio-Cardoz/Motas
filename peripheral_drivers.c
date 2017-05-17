/*
 * peripheral_drivers.c
 *
 * Created: 5/17/2017 10:57:21 PM
 *  Author: Cardoz
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "peripheral_drivers.h"

ISR(PIR_INTERRUPT_VECT)
{
	pirTriggerCount++;
}

ISR(USS_INTERRUPT_VECT)				
{
	static uint8_t UssEdgeCount = 0;
	if (UssEdgeCount)		
	{
		Stop_Timer(1);
		UssPulseCount = TCNT1;		// Store the time duration of the echo pulse.
		TCNT1 = 0;
		UssEdgeCount = 0;
		MCUCR = 0x0F;												// Rising edge will trigger the next interrupt
	}
	else 
	{
		Start_timer(1);
		UssEdgeCount = 1;
		MCUCR = 0x0B;												// falling edge for INT0 enabled
	}
}

void Trigger_Ultrasonic_Sensor()
{
	SETBIT(USS_PORT, USS_TRIGGER);
	_delay_us(10);													// 10us Pulse as per datasheet of HC-SR04 Ultrasonic Sensor
	CLEARBIT(USS_PORT, USS_TRIGGER);
}

void Init_Pir()
{
	CLEARBIT(PIR_INPUT_DIR_REG, PIR_INPUT_PIN);						// Set the pin direction as input
	SETBIT(PIR_INPUT_PORT, PIR_INPUT_PIN);							// Setup the controllers internal Pull up resistor
}

void Init_Ultrasonic_Sensor()
{
	SETBIT(USS_DIR_REG, USS_TRIGGER);								// Set the pin direction as output
	CLEARBIT(USS_PORT, USS_TRIGGER);								// Initial state of trigger is LOW
	SETBIT(USS_PORT, USS_ECHO);										// Activate pull-up on ECHO pin.
}

uint8_t Get_Uss_Count()
{
	Trigger_Ultrasonic_Sensor();
	return UssPulseCount;
}

