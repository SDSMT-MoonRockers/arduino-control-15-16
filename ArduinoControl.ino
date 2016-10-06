/*
Arduino Control Program
ArduinoControl.ino
Written by Zach Buechler
Edited by Devin Kroeber 

Updated 1/17/2016 to work with dump conveyor

This code is what runs on the arduino/Redboard in the Moonrockers NASA RMC Robot.  This code is what controls
the Excavation Conveyor actuators and the direction of the dump conveyor belt.
You can remove the comments of the some of the code to reinstate use of the dump actuators.
*/

#include <digitalWriteFast.h>

const int conveyor_actuatorOut = 10;
const int conveyor_actuatorIn = 9;
const int ActuatorSpeed = 127;
const int ActuatorOff = 0;

const int dump_conveyorFor = 5;
const int dump_conveyorRev = 6;

int Pin2 = 0;
int Pin7 = 0;
int Pin4 = 0;
int Pin8 = 0;
void setup() {

  //---------------------------------------------- Set PWM frequency for D5 & D6 -------------------------------
  
//TCCR0B = TCCR0B & B11111000 | B00000001;    // set timer 0 divisor to     1 for PWM frequency of 62500.00 Hz
TCCR0B = TCCR0B & B11111000 | B00000010;    // set timer 0 divisor to     8 for PWM frequency of  7812.50 Hz
//TCCR0B = TCCR0B & B11111000 | B00000011;    // set timer 0 divisor to    64 for PWM frequency of   976.56 Hz
//TCCR0B = TCCR0B & B11111000 | B00000100;    // set timer 0 divisor to   256 for PWM frequency of   244.14 Hz
//TCCR0B = TCCR0B & B11111000 | B00000101;    // set timer 0 divisor to  1024 for PWM frequency of    61.04 Hz


//---------------------------------------------- Set PWM frequency for D9 & D10 ------------------------------
  
//TCCR1B = TCCR1B & B11111000 | B00000001;    // set timer 1 divisor to     1 for PWM frequency of 31372.55 Hz
TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
//TCCR1B = TCCR1B & B11111000 | B00000011;    // set timer 1 divisor to    64 for PWM frequency of   490.20 Hz
//TCCR1B = TCCR1B & B11111000 | B00000100;    // set timer 1 divisor to   256 for PWM frequency of   122.55 Hz
//TCCR1B = TCCR1B & B11111000 | B00000101;    // set timer 1 divisor to  1024 for PWM frequency of    30.64 Hz

//---------------------------------------------- Set PWM frequency for D3 & D11 ------------------------------
  
//TCCR2B = TCCR2B & B11111000 | B00000001;    // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz
//TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz
//TCCR2B = TCCR2B & B11111000 | B00000011;    // set timer 2 divisor to    32 for PWM frequency of   980.39 Hz
//TCCR2B = TCCR2B & B11111000 | B00000100;    // set timer 2 divisor to    64 for PWM frequency of   490.20 Hz
//TCCR2B = TCCR2B & B11111000 | B00000101;    // set timer 2 divisor to   128 for PWM frequency of   245.10 Hz
//TCCR2B = TCCR2B & B11111000 | B00000110;    // set timer 2 divisor to   256 for PWM frequency of   122.55 Hz
//TCCR2B = TCCR2B & B11111000 | B00000111;    // set timer 2 divisor to  1024 for PWM frequency of    30.64 Hz
  
  pinMode(conveyor_actuatorOut, OUTPUT);
  pinMode(conveyor_actuatorIn, OUTPUT); 
  analogWrite(conveyor_actuatorOut, ActuatorOff);
  analogWrite(conveyor_actuatorIn, ActuatorOff);

  pinMode(dump_conveyorFor, OUTPUT);
  pinMode(dump_conveyorRev, OUTPUT); 
  analogWrite(dump_conveyorFor, ActuatorOff);
  analogWrite(dump_conveyorRev, ActuatorOff);
  pinMode(2, INPUT); //Excavation Conveyor In "down"
  pinMode(7, INPUT); //Excavation Conveyor Out "up"
  pinMode(4, INPUT); //Dump Conveyor Forward "out"
  pinMode(8, INPUT); //Dump Conveyor Reverse "in"
}

void loop() {
  ReadPins();

if (Pin2 == HIGH && Pin7 == LOW){
    analogWrite(conveyor_actuatorOut, ActuatorSpeed);
    analogWrite(conveyor_actuatorIn, 0);
  }
  else if (Pin2 == LOW && Pin7 == HIGH){
    analogWrite(conveyor_actuatorIn, ActuatorSpeed);
    analogWrite(conveyor_actuatorOut, 0);
  }
  else {
    analogWrite(conveyor_actuatorOut, 0);
    analogWrite(conveyor_actuatorIn, 0);
  }

  /*
    Check Actuator Input
   Pin 4 High - Extend
   Pin 8 High - Retract   
   */
   
   /* uncomment to to used dump actuators
  if (Pin4 == HIGH && Pin8 == LOW){
    analogWrite(dump_conveyorFor, ActuatorSpeed);
    analogWrite(dump_conveyorRev, 0);
  }
  else if (Pin4 == LOW && Pin8 == HIGH){
    analogWrite(dump_conveyorRev, ActuatorSpeed);
    analogWrite(dump_conveyorFor, 0);
  }
  else {
    analogWrite(dump_conveyorFor, 0);
    analogWrite(dump_conveyorRev, 0);
  }
  */
  ZeroPins();
}

void ReadPins ()
{
   Pin2 = digitalReadFast(2);
   Pin7 = digitalReadFast(7);
   Pin4 = digitalReadFast(4);
   Pin8 = digitalReadFast(8); 
}

void ZeroPins ()
{
   Pin2 = 0;
   Pin7 = 0;
   Pin4 = 0;
   Pin8 = 0; 
}
