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

/*************************************************************************/
/*		Ring Buffer declarations
/*************************************************************************/
#define RING_SIZE   64
#define BUFFER_EMPTY 0
#define BUFFER_NOT_EMPTY 1
typedef uint8_t ring_pos_t;
volatile ring_pos_t ring_head;
volatile ring_pos_t ring_tail;
volatile char ring_data[RING_SIZE];

#define USART_BAUDRATE 4800
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
/*************************************************************************/

void USART_Init(void);
void USART_SendByte(uint8_t u8Data);
void USART_putstring(char* StringPtr);
uint8_t USART_ReceiveByte();
void USART_Transmit_dec(unsigned int int_data);
int Ring_Add(char c);
int Ring_Remove(void);



#endif /* ATMEGAUART_H_ */