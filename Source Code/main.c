/*						Main Application
 ******************************************************************************************
 ******************************************************************************************
 Written by: Hisham Yakan Abuabkr
 Project: UltraSonic Sensor - project 4
 File type: Source file
  */


/*
 ************************************** Included files******************************************
 */
#include "LCD.h"    /*To interface with LCD*/
#include "ultraSonic.h" /*To interface with ultraSonic sensor*/
#include "avr/interrupt.h"

/*
************************************************************************************************
 */


int main(){

	/*******************Enable Global interrupt bit *******************************8
	 */
	SREG |= (1<<7);

/*
 ****************************************LCD_Initialization*************************************
 */
	LCD_init();
/*
***********************************************************************************************
 */

/*
 ********************************Ultra_Sonic_sensor_Initialization*******************************
 */
	Ultrasonic_init();
/*
***********************************************************************************************
 */

	while(1)
	{

		LCD_displayString("Distance = ");

/*Receiving the sensor reading in the a variable */
		uint16 currentDistance = Ultrasonic_readDistance();

/*Displaying the distance through the variable currentDistance */
		if(currentDistance<10)
		{
			LCD_intgerToString(currentDistance);
			LCD_displayString("  ");
		}
		else if(currentDistance>10 && currentDistance<100)
		{
			LCD_intgerToString(currentDistance);
			LCD_displayString(" ");
		}
		else
		{
			LCD_intgerToString(currentDistance);
		}

		LCD_moveCursor(0,14);
		LCD_displayString("cm");
		LCD_moveCursor(1,0);

		LCD_moveCursor(0,0);

	}


	return 0;
}

