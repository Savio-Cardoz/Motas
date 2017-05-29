/**
* @Motas_Controller.h
* @brief this header file contains the declarations of all the functions of the Application
  layer impelemented in the form of state machine
*
* @author Faisal Khan
*
* @date 29/05/2017
*/



typedef enum 
{
	MOTAS_INIT_STATE = 0;
	MOTAS_CALIBRATION_STATE = 1;
	MOTAS_STANDBY_STATE = 2;
	MOTAS_PROCESSING_STATE = 3;
	MOTAS_ACTIVE_STATE = 4;
	MOTAS_DEBUGGING_STATE = 5;

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
  Autocalibration of the ultrasonic is done and the value is stored in threshold_Uss_Count 
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


void MotasController(void);


void Processing_State(void);

