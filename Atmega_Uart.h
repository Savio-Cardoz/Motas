/*
 * atmegaUart.h
 *
 * Created: 5/19/2017 12:53:28 AM
 *  Author: Cardoz
 */ 


#ifndef ATMEGAUART_H_
#define ATMEGAUART_H_

#ifndef F_CPU
#define F_CPU 11059200UL//8000000UL
#endif


#define USART_BAUDRATE 4800
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void USART_Init(void);
void USART_SendByte(uint8_t u8Data);
void USART_putstring(char* StringPtr);
void Usart_Send_Array(uint8_t* arrayptr, uint8_t len);
uint8_t USART_ReceiveByte();




#endif /* ATMEGAUART_H_ */