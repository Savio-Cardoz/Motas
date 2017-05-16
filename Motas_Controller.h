
typedef enum 
{
	MOTAS_INIT_STATE = 0;
	MOTAS_CALIBRATION_STATE = 1;
	MOTAS_STANDBY_STATE = 2;
	MOTAS_PROCESSING_STATE = 3;
	MOTAS_ACTIVE_STATE = 4;
	MOTAS_DEBUGGING_STATE = 5;

}t_motascontroller_state;


void Init_State(void);


void Calibration_State(void);


void Standby_State(void);


void Processing_State(void);


void Active_State(void);


void Debugging_State(void);


void MotasController(void);



