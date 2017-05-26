/*
 * peripheral_drivers.h
 *
 * Created: 5/17/2017 10:56:58 PM
 *  Author: Cardoz
 */ 


#ifndef PERIPHERAL_DRIVERS_H_
#define PERIPHERAL_DRIVERS_H_

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#define SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))			
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))

//#define PIR_INTERRUPT_VECT(number) INT##number##_vect
#define PIR_INTERRUPT_VECT 			INT0_vect						// PIR output should be input to controller on INT0
#define USS_INTERRUPT_VECT			INT1_vect
#define PIR_INPUT_PORT				PORTD
#define PIR_INPUT_DIR_REG			DDRD
#define PIR_INPUT_PIN				PIND2				
#define USS_PORT 					PORTD
#define USS_DIR_REG					DDRD
#define USS_TRIGGER					PD4
#define USS_ECHO					PIND3


/*********************************************************************************************************************
/*					Local variables
/********************************************************************************************************************/
uint16_t pir_trigger_count, UssPulseCount;

/**********************************************************************************************************************
/*					Function Prototypes
/*********************************************************************************************************************/
void Trigger_Ultrasonic_Sensor();
void Init_Pir();
void Init_Ultrasonic_Sensor();
uint16_t Get_Uss_Count();
uint16_t Get_Pir_count();
void Reset_Pir_count();



#endif /* PERIPHERAL_DRIVERS_H_ */