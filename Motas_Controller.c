/**
* @Motas_Controller.c
* @brief this source file contains the implementation of the Application layer
  in the form of state machine
*
* @author Faisal Khan
*
* @date 29/05/2017
*/


/*===============================Includes=================================================*/
#include <avr/io.h>
#include <util/delay.h>
#include "Atmega_Config.h"
#include "Atmega_Uart.h"
#include "Motas_Controller.h"

/*========================================================================================*/

/*===============================Global variables==========================================*/

/*Initialize the state machine to the INIT_STATE*/
static t_motascontroller_state motascontroller_state = MOTAS_INIT_STATE;
static uint16_t threshold_uss_count = 0;
/*Demo value. Can be changed or can be kept as configurable*/
uint16_t threshold_pir_count = 4;

/*========================================================================================*/

/**
* This method is the state corresponding to the Initial state of the state machine
* @author Faisal Khan
* @param none
* @date 29/05/2017
*/
void Init_State(void)
{
	//TODO: Implementation - How to read if the card is empty
	if(/*sd card is empty*/ 1)
	{
		#ifdef DEBUG_ON
		SendDebug("Motas entering Debugging state");
		#endif

		motascontroller_state = MOTAS_DEBUGGING_STATE;	
	}

	/* No debugging needed. Start calibration */
	else{
		motascontroller_state = MOTAS_CALIBRATION_STATE;	
	}

}


/**
* This method is the state corresponding to Ultrasonic calibration state where 
  Autocalibration of the ultrasonic is done and the value is stored in threshold_uss_count 
* @author Faisal Khan
* @param none
* @date 29/05/2017
*/
void Calibration_State(void)
{
	/*Update the value of threshold*/
	
	threshold_uss_count = Get_Uss_Count();
	/*Reset the PIR count*/
	Reset_Pir_count();
	//TODO: Indicate on the LED when the LED driver is ready
	motascontroller_state = MOTAS_STANDBY_STATE;
}


/**
* This method is the state corresponding to Ultrasonic standby state wherein values from 
  ultrasonic and PIR is checked continuously 
* @author Faisal Khan
* @param none
* @date 29/05/2017
*/
void Standby_State(void)
{
	uint16_t standby_pircount = 0;
	uint16_t standby_usscount = 0; 

	standby_pircount = Get_Pir_count();
	standby_usscount = Get_Uss_Count(); 

	/*Check if Ultrasonic has triggered for customer entering the room or pir*/
	if((standby_usscount < threshold_uss_count) || (standby_pircount > 1))
	{
		/*Delay of 3 seconds. Can be changed */
		_delay_ms(3000);
		/*Read pir count*/
		standby_pircount = Get_Pir_count();

		/* Ignore uss count */
		if(standby_pircount > threshold_pir_count)
		{
			motascontroller_state = MOTAS_ACTIVE_STATE;
		}

		/*Do nothing and stay in the current state*/
		else {
			motascontroller_state = MOTAS_STANDBY_STATE;
		}
	}

	/*Do nothing and stay in the current state*/
	else
	{
		motascontroller_state = MOTAS_STANDBY_STATE;
	}


}


/**
* This method is the state corresponding to System Active state wherein music is started or 
  continued if already playing 
* @author Faisal Khan
* @param none
* @date 29/05/2017
*/
void Active_State(void)
{
	uint16_t active_pir_count = 0;
	uint16_t active_usscount = 0; 

	//TODO: Change LED colour
	Reset_Pir_count();

	/*Get ultrasonic count */
	active_usscount = Get_Uss_Count(); 

	/*This delay can be changed or configured*/
	_delay_ms(3000);
	/*Customer present in the room*/	
	if((active_pir_count > threshold_pir_count) || (active_usscount >= threshold_uss_count))
	{
		/*Do not change the state. Keep audio playing*/
		motascontroller_state = MOTAS_ACTIVE_STATE;
	}

	/*Customer exits the room */
	else{
		/*change the state to standby state*/
		Reset_Pir_count();
		motascontroller_state = MOTAS_STANDBY_STATE;	
	}
}

void Debugging_State(void)
{


}

/**
* This method is the main state machine function. This function would be called from the main func  
* @author Faisal Khan
* @param none
* @date 29/05/2017
*/
void MotasController(void)
{
	//TODO: Implement some timing delay if required 

	switch(motascontroller_state)
	{
		case MOTAS_INIT_STATE:
			Init_State();
			break;	

		case MOTAS_CALIBRATION_STATE:
			Calibration_State();
			break;	

		case MOTAS_STANDBY_STATE:
			Standby_State();

			break;

		case MOTAS_ACTIVE_STATE:
			Active_State();
			break;

		case MOTAS_DEBUGGING_STATE:		
			Debugging_State();	
			break;

		default : 
			/*Do nothing*/
			break;	

	}
}
