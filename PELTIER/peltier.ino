#include <PID_v1.h>
//#define PIN_INPUT 0
#define PIN_OUTPUT 3
#define BITSIZE 10
#include <Wire.h>
#include "Protocentral_MAX30205.h"
MAX30205 tempSensor;
//Define Variables we'll be connecting to
double Setpoint, Input, Output;
int Bits[] = {2,3,4,5,6,7,8,9,10,11};
int digit[BITSIZE];
int i;
//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  tempSensor.begin();
  //initialize the variables we're linked to
  Input = tempSensor.getTemperature();
  Setpoint = 100;
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}
void loop()
{
  float temp = tempSensor.getTemperature();
  Serial.print(temp ,2);
  Serial.println("'c" );
  //Input = analogRead(PIN_INPUT);
  Input = temp;
  myPID.Compute();
  analogWrite(PIN_OUTPUT, Output);
} (edited) 