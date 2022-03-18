/*						UltraSonic Driver Module
 ******************************************************************************************
 ******************************************************************************************
 Written by: Hisham Yakan Abuabkr
 Project: UltraSonic Sensor - project 4
 File type: Module Source file
  */

/*
 ************************************** Included files******************************************
 */


#include "ultraSonic.h"
#include "ICU.h"
#include "gpio.h"
#include "util/delay.h"



#define COMING_RISING_EDGE 1
#define COMING_FALLING_EDGE 2

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint8 edgeCount = 0;
uint64 timeHigh = 0;
uint16 distance = 0;


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

void Ultrasonic_init(void)
{
	/*
	 Initialize the ICU driver
	 clock frequency = F_CPU/8
	 edge type = rising edge
	 */
	Icu_ConfigType myICU;
	myICU.edge =RISING;
	myICU.clock = F_CPU_8;
	Icu_init(&myICU);

	/*
	 Setup the callback function
	 */
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	/*
	 Setup the direction for the trigger pin as output pin through the GPIO driver.
	 */
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT);
}

/*
 ***************************** 2.UltraSomic Trigger Function ***********************
 Function Description: This function is used to initialize the UltraSonic Driver by:
 Generate a trigger for the sensor

  Function Inputs:Void

 */


void Ultrasonic_Trigger(void)
{
	/*Right digital high to the trigger pin*/
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_HIGH);

	/*Wait more than 10uSeconds*/
	_delay_us(25);

	/*Right digital low to the trigger pin*/
	GPIO_writePin(PORTB_ID,PIN5_ID,	LOGIC_LOW);

}

/*
 ***************************** 3.UltraSomic Distance reading Function ***********************
 Function Description: This function is used to calculate the distance in Centimeters

  Function Inputs:Void

 */

uint16 Ultrasonic_readDistance(void)
{
	/*Trigger the sensor*/
	Ultrasonic_Trigger();

	/*Calculate the distance in Centimeters*/
	distance = ((float)timeHigh) / 58.8;

	return distance;
}

/*
 ***************************** 4.UltraSomic edge ***********************
 Function Description: This function is used to find determine the time of high edge and
 store the value in a global variable

  Function Inputs:Void

 */
void Ultrasonic_edgeProcessing(void)
{

	edgeCount++;
	/*Every time the coming edge is a rising edge, edgeCount variable
	 is going to be 1. so clear the time and change into falling edge
	 **/
	if(edgeCount == COMING_RISING_EDGE)
	{
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(FALLING);
	}

	/*Every time the coming edge is a falling edge, edgeCount variable
	 is going to be 2. so capture the time , restore edge count to 0 and
	 change the direction to rising age again
	 **/
	else if (edgeCount == COMING_FALLING_EDGE)
	{
		timeHigh = Icu_getInputCaptureValue();
		edgeCount = 0;
		Icu_setEdgeDetectionType(RISING);

	}

}
