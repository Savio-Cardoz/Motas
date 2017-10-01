/*
 * debug_func.h
 *
 * Created: 9/23/2017 5:41:56 PM
 *  Author: Cardoz
 */ 

#ifndef DEBUG_FUNC_H_
#define DEBUG_FUNC_H_

#include <avr/io.h> 

#define DEBUG_ON			0
#define RED_LED				PC0
#define YELLOW_LED			PC1
#define RED_LED_PORT		PORTC
#define YELLOW_LED_PORT		PORTC
#define RED_LED_DIR_REG		DDRC
#define YELLOW_LED_DIR_REG	DDRC

typedef enum{
	LED_YELLOW	= 1,
	LED_RED,
	LED_ORANGE
	}debug_led_colour_t;
	
typedef enum{
	LED_OFF = 0,
	LED_ON
	}debug_led_state_t;

/* if entering the debug state use the functions below	*/
void DebugLedInit();																// Initialize the port registers for LED functions
void DebugLedTransmit(debug_led_state_t led_state, debug_led_colour_t led_colour);

#endif /* DEBUG_FUNC_H_ */