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
#include "Atmega_Config.h"
#include "Atmega_Uart.h"
#include "Motas_Controller.h"

/*========================================================================================*/

/* All required flags in the application layer are present in this variable (8 per variable) */
uint8_t flag_register_controller;			

/* Flag to indicate if the sd card is empty */
#define flag_sd_card_empty_g REGISTER_BIT(flag_register_controller, 0)

/*===============================Global variables==========================================*/

/*Initialize the state machine to the INIT_STATE*/
static t_motascontroller_state motascontroller_state = MOTAS_INIT_STATE;
static uint16_t threshold_uss_count = 0;

/* threshold uss count can be set different than normal. Delete if not required */
static uint16_t debug_threshold_uss_count = 0;
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
	//TODO: extern this flag. Please do not change the name
	if(TRUE == flag_sd_card_empty_g)
	{
		#ifdef DEBUG_ON
			SendDebug("Motas entering Debugging state");
		#endif

		motascontroller_state = MOTAS_DEBUGGING_STATE;	
	}

	//TODO: Check if any additional condition is required for this transition
	/* No debugging required. Start calibration */
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

/**
* This method is for the debugging state. Check if sensors are working as required.
* Note that no state would be changed after this
* @author Faisal Khan
* @param none
* @date 29/05/2017
*/
void Debugging_State(void)
{
	uint16_t pir_count = 0;
	uint16_t uss_count = 0;

	/* Yellow led light indicating start of Debugging mode */
	DebugLedTransmit(LED_ON ,LED_YELLOW);
	_delay_ms(2000);
	
	/* Get the pir count */
	Reset_Pir_count();
	pir_count = Get_Pir_count();

	/* Get the USS count */
	uss_count = Get_Uss_Count();

	/* Check if pir is triggered */
	if(pir_count > 1)
	{
		/* Red led light indicating pir triggered */
		DebugLedTransmit(LED_ON, LED_RED);
		_delay_ms(2000);
		
	}
	/* Check if USS is triggered */
	else if(uss_count > debug_threshold_uss_count);
	{
		/* Orange led light indicating uss triggered */
		DebugLedTransmit(LED_ON, LED_ORANGE);
		_delay_ms(2000);
	}
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
