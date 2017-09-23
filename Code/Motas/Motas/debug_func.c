/*
 * debug_func.c
 *
 * Created: 9/23/2017 5:41:28 PM
 *  Author: Cardoz
 */ 

#include <avr/io.h>
#include "debug_func.h"

void DebugLedInit()
{
	RED_LED_DIR_REG |= (1 << RED_LED);
	YELLOW_LED_DIR_REG |= (1 << YELLOW_LED);
	
	RED_LED_PORT &= ~(1 << RED_LED);
	YELLOW_LED_PORT &= ~(1 << YELLOW_LED);
}

void DebugLedTransmit(debug_led_state_t led_state, debug_led_colour_t led_colour)
{
	if(led_state == LED_ON)
	{
		switch(led_colour)
		{
			case LED_RED:
				RED_LED_PORT |= (1 << RED_LED);
				break;
				
			case LED_YELLOW:
				YELLOW_LED_PORT |= (1 << YELLOW_LED);
				break;
				
			case LED_ORANGE:
				RED_LED_PORT |= (1 << RED_LED);
				YELLOW_LED_PORT |= (1 << YELLOW_LED);
				break;
		} 
	}
	else if(led_state == LED_OFF)
	{
		switch(led_colour)
		{
			case LED_RED:
			RED_LED_PORT &= ~(1 << RED_LED);
			break;
		
			case LED_YELLOW:
			YELLOW_LED_PORT &= ~(1 << YELLOW_LED);
			break;
		
			case LED_ORANGE:
			RED_LED_PORT &= ~(1 << RED_LED);
			YELLOW_LED_PORT &= ~(1 << YELLOW_LED);
			break;
		}
	}
}