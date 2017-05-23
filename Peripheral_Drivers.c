/*
 * peripheral_drivers.c
 *
 * Created: 5/17/2017 10:57:21 PM
 *  Author: Cardoz
 */ 

#define F_CPU 11059200UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Peripheral_Drivers.h"

ISR(PIR_INTERRUPT_VECT)
{
	pir_trigger_count++;
}

ISR(USS_INTERRUPT_VECT)				
{
	static uint8_t UssEdgeCount = 0;
	if (UssEdgeCount)		
	{
		Stop_Timer1();
		UssPulseCount = TCNT1;		// Store the time duration of the echo pulse.
		TCNT1 = 0;
		UssEdgeCount = 0;
		MCUCR |= (1 << ISC10);												// Rising edge will trigger the next interrupt
	}
	else 
	{
		Start_Timer1();
		UssEdgeCount = 1;
		MCUCR &= ~(1 << ISC10);										// falling edge for INT0 enabled
	}
}

void Trigger_Ultrasonic_Sensor()									// Function tested for 10us trigger 
{
	SETBIT(USS_PORT, USS_TRIGGER);
	_delay_us(10);													// 10us Pulse as per datasheet of HC-SR04 Ultrasonic Sensor
	CLEARBIT(USS_PORT, USS_TRIGGER);
}

void Init_Pir()
{
	CLEARBIT(PIR_INPUT_DIR_REG, PIR_INPUT_PIN);						// Set the pin direction as input
	SETBIT(PIR_INPUT_PORT, PIR_INPUT_PIN);							// Setup the controllers internal Pull up resistor

	MCUCR |= (1 << ISC01) | (1 << ISC00);
	GICR |= (1 << INT0);
}

void Init_Ultrasonic_Sensor()
{
	SETBIT(USS_DIR_REG, USS_TRIGGER);								// Set the pin direction as output
	CLEARBIT(USS_PORT, USS_TRIGGER);								// Initial state of trigger is LOW
	SETBIT(USS_PORT, USS_ECHO);										// Activate pull-up on ECHO pin.
	
	MCUCR |= (1 << ISC11) | (1 << ISC10);							// Set the interrupt to trigger at the rising edge.
	GICR |= (1 << INT1);
}

uint16_t Get_Uss_Count()
{
	Trigger_Ultrasonic_Sensor();
	_delay_ms(1000);
	return UssPulseCount;
}

void Init_Timer1()
{
	TCNT1 = 0;
}

void Start_Timer1()
{
	TCCR1B |= (1 << CS10);		// No prescalar
}

void Stop_Timer1()
{
	TCCR1B &= ~(1 << CS10);
}

uint16_t Get_Pir_count()
{
	return pir_trigger_count;
}

void Reset_Pir_count()
{
	pir_trigger_count = 0;
}