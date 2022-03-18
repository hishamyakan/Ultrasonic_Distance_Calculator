/*						UltraSonic Driver Module
 ******************************************************************************************
 ******************************************************************************************
 Written by: Hisham Yakan Abuabkr
 Project: UltraSonic Sensor - project 4
 File type: Module header file
  */


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/*
 ************************************** Included files******************************************
 */
#include "std_types.h"


/*
 ************************************* Functions **********************************************
 */

/*
 ***************************** 1.UltraSomic Initialization Functions ***********************
 Function Description: This function is used to initialize the UltraSonic Driver by:
 1- Initialize the ICU driver
 2- Setup the callback function
 3- Setup the direction for the trigger pin as output pin through the GPIO driver.

  Function Inputs:Void

 */
void Ultrasonic_init(void);

/*
 ***************************** 1.UltraSomic Trigger Function ***********************
 Function Description: This function is used to initialize the UltraSonic Driver by:
 Generate a trigger for the sensor

  Function Inputs:Void

 */
void Ultrasonic_Trigger(void);

/*
 ***************************** 3.UltraSomic Distance reading Function ***********************
 Function Description: This function is used to calculate the distance in Centimeters

  Function Inputs:Void

 */

uint16 Ultrasonic_readDistance(void);

/*
 ***************************** 4.UltraSomic edge ***********************
 Function Description: This function is used to find determine the time of high edge and
 store the value in a global variable

  Function Inputs:Void

 */
void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
