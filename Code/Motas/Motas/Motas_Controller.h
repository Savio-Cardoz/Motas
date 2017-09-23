/**
* @Motas_Controller.h
* @brief this header file contains the declarations of all the functions of the Application
  layer impelemented in the form of state machine
*
* @author Faisal Khan
*
* @date 29/05/2017
*/


/*===============================Includes=================================================*/
#include "Atmega_Config.h"


/*========================================================================================*/
#define False	0
#define True	1

typedef struct			// Using to access individual bits/pins of a register/port
{
	unsigned int bit0:1;
	unsigned int bit1:1;
	unsigned int bit2:1;
	unsigned int bit3:1;
	unsigned int bit4:1;
	unsigned int bit5:1;
	unsigned int bit6:1;
	unsigned int bit7:1;
} _io_reg;

#define REGISTER_BIT(rg,bt) ((volatile _io_reg*)&rg)->bit##bt


/**
* enum for states of the state machine.   
* @author Faisal Khan
* @param none
* @date 29/05/2017
*/
typedef enum 
{
	MOTAS_INIT_STATE = 0,
	MOTAS_CALIBRATION_STATE = 1,
	MOTAS_STANDBY_STATE = 2,
	MOTAS_ACTIVE_STATE = 3,
	MOTAS_DEBUGGING_STATE = 4,
}t_motascontroller_state;

/**
* This method is the state corresponding to the Initial state of the state machine
* @author Faisal Khan
* @param none
* @date 29/05/2017
*/
void Init_State(void);

/**
* This method is the state corresponding to Ultrasonic calibration state where 
  Autocalibration of the ultrasonic is done and the value is stored in threshold_uss_count 
* @author Faisal Khan
* @param none
* @date 29/05/2017
*/
void Calibration_State(void);

/**
* This method is the state corresponding to Ultrasonic standby state wherein values from 
  ultrasonic and PIR is checked continuously 
* @author Faisal Khan
* @param none
* @date 29/05/2017
*/
void Standby_State(void);


/**
* This method is the state corresponding to System Active state wherein music is started or 
  continued of already playing 
* @author Faisal Khan
* @param none
* @date 29/05/2017
*/
void Active_State(void);

//TODO: To be implemented
void Debugging_State(void);

/**
* This method is the main state machine function. This function would be called from the main func  
* @author Faisal Khan
* @param none
* @date 29/05/2017
*/
void MotasController(void);


