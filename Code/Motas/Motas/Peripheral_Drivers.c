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
#include "Motas_Controller.h"
#include "debug_func.h"
#include "Atmega_Uart.h"

static volatile uint16_t pir_trigger_count, UssPulseCount;
static volatile uint16_t timer1_ovf_count = 0;
extern uint8_t flag_register_controller;
extern uint16_t threshold_uss_count;

#define SET_USS_FLAG	({flag_register_controller |= (1 << 2);})
#define CLEAR_USS_FLAG  ({flag_register_controller &= ~(1 << 2);})

ISR(TIMER1_OVF_vect)
{
	++timer1_ovf_count;
}

ISR(TIMER0_OVF_vect)
{
	static uint16_t timer_ovf_count = 0;
	
	if((timer_ovf_count++) == 500)
	{
		Trigger_Ultrasonic_Sensor();
		timer_ovf_count = 0;
		TCCR0 &= ~(1 << CS00);		// Stop the timer. Timer is restarted in the USS echo received interrupt
		TCNT0 = 0;
	}
}

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
		timer1_ovf_count = 0;
		TCNT1 = 0;
		UssEdgeCount = 0;
		MCUCR |= (1 << ISC01) | (1 << ISC00);												// Rising edge will trigger the next interrupt
		TCCR0 |= (1 << CS00);					// Start the timer0 to wait for 1ms to trigger the USS
		
		if(UssPulseCount < threshold_uss_count)
		{
			#if DEBUG_ON
			SendDebug("Thres_cross");
			USART_Transmit_dec(UssPulseCount);
			#endif	
			DebugLedTransmit(LED_ON, LED_RED);
			SET_USS_FLAG;	
		}
	}
	else 
	{
		Start_Timer1();
		UssEdgeCount = 1;
		MCUCR &= ~(1 << ISC00);										// falling edge for INT0 enabled
		MCUCR |= (1 << ISC01);
	}
}

void Trigger_Ultrasonic_Sensor()									// Function tested for 10us trigger 
{
	SETBIT(USS_TRIGGER_PORT, USS_TRIGGER_PIN);
	_delay_us(10);													// 10us Pulse as per datasheet of HC-SR04 Ultrasonic Sensor
	CLEARBIT(USS_TRIGGER_PORT, USS_TRIGGER_PIN);
}

void Init_Pir()
{
	CLEARBIT(PIR_INPUT_DIR_REG, PIR_INPUT_PIN);						// Set the pin direction as input
	SETBIT(PIR_INPUT_PORT, PIR_INPUT_PIN);							// Setup the controllers internal Pull up resistor

	MCUCR |= (1 << ISC11) | (1 << ISC10);
	GICR |= (1 << INT1);
}

void Init_Ultrasonic_Sensor()
{
	USS_TRIGGER_DIR_REG |= (1 << USS_TRIGGER_PIN);					// Set the pin direction as output
	USS_TRIGGER_PORT &= ~(1 << USS_TRIGGER_PIN);					// Initial state of trigger is LOW
	
	USS_ECHO_DIR_REG &= ~(1 << USS_ECHO_PIN);						// ECHO pin is set a s input
	USS_ECHO_PORT |= (1 << USS_ECHO_PIN);							// Keep ECHO pin pulled up
	
	/* Setup rising edge interrupt on the echo pin	*/	
	MCUCR |= (1 << ISC01) | (1 << ISC00);							// Set the interrupt to trigger at the rising edge.
	GICR |= (1 << INT0);
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
	// TODO: replace with a flag to check if the USS ECHO pulse has been received Speed can be 
	return UssPulseCount;
}


/* Timer 0 will be used to auto trigger the USS	@ periodic intervals	*/
void Init_Timer0()
{
	TIMSK |= (1 << TOIE0);
	TCCR0 |= (1 << CS00);		// Start the timer	default 256us overflow rate @ 1MHZ.
}

void Init_Timer1()
{
	TCNT1 = 0;
	TIMSK |= (1 << TOIE1);
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
	#if DEBUG_ON
	SendDebug("PIR@");
	USART_Transmit_dec(pir_trigger_count);
	#endif
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

void Init_Gpio()
{
	RELAY_PORT_DIR_REG |= (1 << RELAY_PIN);		// Set the relay pin as a output pin
	RELAY_PORT &= ~(1 << RELAY_PIN);			// Initialise relay in OFF state.
}


