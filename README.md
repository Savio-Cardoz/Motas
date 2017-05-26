# Motas
Code for Motas controller with Ultrasonic, PIR and sd card implemented


Functions the abstraction layer can use.

To get the Time Count of Ultrasonic Sensor
  uint16_t Get_Uss_Count();    returns an integer with time count equivalent to distance
  
  uint16_t Get_Pir_Count();    returns an integer with the current count of PIR sensor triggers
  
  void Reset_Pir_Count();
  
  void Dfplayer_Cmd(uint8_t cmd, uint16_t parameter);   Takes command with parameter value for that command
  
  ***** Pending addition of 'reading status of DF player to enter debug mode *******
