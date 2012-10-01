/*  Function returns true if input variable "time" has elapsed.  It resets itself automatically...
The wait function will probably return true the first time it is used.

Use the index to start separate timers for each thing you are tested.

Usage:  Step up function for ball picker upper... increases power by 10 every 0.1 seconds.  Full rampup in 1 second

  #include "auxiliaryfunctions.h"
  task main()
  {
    int power = 0;
    while(true)
    {
      if(joy2Btn(6) == 1)
      {
        motor[motorA] = power;
        if(wait(100, 0))
        {
          power = power + 10;
        }
      }
    }
  }

*/

long currenttime[10];
long previoustime[10] = {0,0,0,0,0,0,0,0,0,0};
long changetime[10];

bool wait(int time, int index)
{
  currenttime[index] = nPgmTime;
  changetime[index] = currenttime[index] - previoustime[index];
  if(changetime[index] > time)
  {
    previoustime[index] = currenttime[index];
    return true;
  }
  else
  {
   return false;
  }
}



/* Function returns the speed of a Tetrix DC motor equipped with encoder in RPMs.

Inputs to the function are the motor you want to check, and an index.  Use a different index for every
motor you are checking.

ex:
  #include "auxiliaryfunctions.h"
  task main()
  {
    while(true)
    {
      motor[motorD] = 10;
      writeDebugStreamLine("%3.0f", SpeedCheck(motorD, 0));
      wait1Msec(1000);
    }
  }


*/

float CurrentMotorPosition[8] = {0,0,0,0,0,0,0,0};
float PreviousMotorPosition[8] = {0,0,0,0,0,0,0,0};
float ChangeMotorPosition[8] = {0,0,0,0,0,0,0,0};
float CurrentTime[8] = {0,0,0,0,0,0,0,0};
float PreviousTime[8] = {0,0,0,0,0,0,0,0};
float ChangeTime[8] = {0,0,0,0,0,0,0,0};
float MotorSpeed[8] = {0,0,0,0,0,0,0,0};

float SpeedCheck(tMotor checkmotor, int motorindex)
{

  CurrentMotorPosition[motorindex] = nMotorEncoder[checkmotor];  // Read Current Motor Position
  ChangeMotorPosition[motorindex] = abs(CurrentMotorPosition[motorindex] - PreviousMotorPosition[motorindex]);  //Read Change since last checked
  CurrentTime[motorindex] = nPgmTime;  // Read Total Time Passed since program began
  ChangeTime[motorindex] = CurrentTime[motorindex] - PreviousTime[motorindex];    //Read Time Passed in this loop
  MotorSpeed[motorindex] = ChangeMotorPosition[motorindex]/ChangeTime[motorindex]*1000/1440*60;   //RPMs
  PreviousMotorPosition[motorindex] = CurrentMotorPosition[motorindex];
  PreviousTime[motorindex] = CurrentTime[motorindex];
  return MotorSpeed[motorindex];

}



/*  High Pass Filter:  takes an input and clips it to zero if it is below threshold

Usage:
  motor[motorD] = highpass(joy1_y1, 7);   clips any values of joystick below 7 to zero.

Useful if you only want a motor to turn forwards with a deadband.

*/

int highpass(int power, int threshold)
{
  if(power < threshold)
  {
    power = 0;
  }
  return power;
}


/*  Low Pass Filter:  takes an input and clips it to zero if it is above threshold

Usage:
  motor[motorD] = highpass(joy1_y1, -7);   clips any values of joystick above -7 to zero.

Useful if you only want a motor to turn backwards with a deadband.

*/

int lowpass(int power, int threshold)
{
  if(power > threshold)
  {
    power = 0;
  }
  return power;
}


/* Deadband:  clips an input to zero if the input is between -threshold and threshold.

  ex:   motor[motorA] = deadband(joy1_x1, 7);
*/

int deadband(int power, int threshold)
{
  if(abs(power) < threshold)
  {
    power = 0;
  }
  return power;
}
