/*
 * atmegaUart.c
 *
 * Created: 5/19/2017 12:53:43 AM
 *  Author: Cardoz
 */

#include <avr/io.h>
#include "atmegaUart.h"
 
void USART_Init(void)
{
   UBRRL = BAUD_PRESCALE;// Load lower 8-bits into the low byte of the UBRR register
   UBRRH = (BAUD_PRESCALE >> 8); 
	 /* Load upper 8-bits into the high byte of the UBRR register
    Default frame format is 8 data bits, no parity, 1 stop bit
  to change use UCSRC, see AVR datasheet*/ 

  // Enable receiver and transmitter and receive complete interrupt 
  UCSRB = ((1<<TXEN)|(1<<RXEN) | (1<<RXCIE));
}


void USART_SendByte(uint8_t u8Data)
{
  while((UCSRA &(1<<UDRE)) == 0);
  UDR = u8Data;
}

void USART_putstring(char* StringPtr)
{
	while(*StringPtr != 0x00)
	{
		USART_SendByte(*StringPtr);
		StringPtr++;
	}
}

uint8_t USART_ReceiveByte()
{
  while(!(UCSRA & (1<<RXC)));
  return UDR;
}

void USART0_Transmit_dec(unsigned int int_data)
{
	unsigned int temp1, temp2, dec_adc_value = 0;
	
	temp1 = int_data % 4096;
	temp2 = int_data / 4096;
	dec_adc_value = dec_adc_value + (temp2 * 4096);
	temp2 = temp1;
	temp1 = temp1 % 256;
	temp2 = temp2 / 256;
	dec_adc_value = dec_adc_value + (temp2 * 256);
	temp2 = temp1;
	temp1 = temp1 % 16;
	temp2 = temp2 / 16;
	dec_adc_value = (dec_adc_value + (temp2 * 16) + temp1);
	temp1 = dec_adc_value;
	USART_SendByte((dec_adc_value / 10000) | 0x30);
	dec_adc_value = temp1 % 10000;
	USART_SendByte((dec_adc_value / 1000) | 0x30);
	dec_adc_value = temp1 % 1000;
	USART_SendByte((dec_adc_value /100) | 0x30);
	dec_adc_value = temp1 % 100;
	USART_SendByte((dec_adc_value / 10) | 0x30);
	dec_adc_value = temp1 % 10;
	USART_SendByte(dec_adc_value | 0x30);
}