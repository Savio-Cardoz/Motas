/*
 * peripheral_drivers.c
 *
 * Created: 5/17/2017 10:57:21 PM
 *  Author: Cardoz
 */ 
#include "Atmega_Config.h"
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

void Init_Led()
{
	SETBIT(DDRC, PC0);
	SETBIT(DDRC, PC1);
	CLEARBIT(PORTC, PC0);
	CLEARBIT(PORTC, PC1);	
}

void Led_On(uint8_t led_color)
{
	SETBIT(PORTC, led_color);
}

void Led_Off(uint8_t led_color)
{
	CLEARBIT(PORTC, led_color);
}

uint16_t Get_Uss_Count()
{
	Trigger_Ultrasonic_Sensor();
	_delay_ms(1000);
	#ifdef DEBUG_ON
	SendDebug("USS Triggered");
	SendDebug("USS count:");
	USART_Transmit_dec(UssPulseCount);
	USART_SendByte(0x0D);
	USART_SendByte(0x0A);
	#endif
	return UssPulseCount;
}

void Init_Timer1()
{
	TCNT1 = 0;
}

void Start_Timer1()
{
	TCCR1B |= (1 << CS10);		// No pre-scalar
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

/*
 *	Return the digital level of the pin connected to the PIR output
 *	return 1 - if PIR is being triggered
 *	return 0 - No motion is detected by the PIR.
*/ 
uint8_t Get_Pir_status()
{
	if(CHECKBIT(PIND, PIR_INPUT_PIN))
	{
		#ifdef DEBUG_ON
		SendDebug("Motion active");
		#endif
		
		return 1;
	}
	#ifdef DEBUG_ON
	SendDebug("No Motion");
	#endif
	
	return 0;
}


