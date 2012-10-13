#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     LeftFront,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     LeftBack,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     RightFront,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     RightBack,     tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

int y1 = 0;		//joystick #1 y axis
int x1 = 0;		//joystick #1 x axis
int x2 = 0;		//joystick #2 x axis

task main()
{
	getJoystickSettings(joystick);

	while(true)  //infinite loop
	{
		y1 = joystick.joy1_y1;		//read joystick values
		x1 = joystick.joy1_x1;
		x2 = joystick.joy1_x2;

		if(abs(y1) < 20)			//deadband with threshold of 8
		{
			y1 = 0;
		}

		if(abs(x1) < 20)			//deadband with threshold of 8
		{
			x1 = 0;
		}

		if(abs(x2) < 20)			//deadband with threshold of 8
		{
			x2 = 0;
		}
		motor[RightFront] = y1 - x2 - x1;		//code from http://www.robotc.net/blog/2011/11/22/vex-mecanum-drive-using-robotc/
		motor[RightBack] =  y1 - x2 + x1;
		motor[LeftFront] = y1 + x2 + x1;
		motor[LeftBack] =  y1 + x2 - x1;

	}

}
