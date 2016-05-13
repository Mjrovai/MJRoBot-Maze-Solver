/*------------------------------------------------------------------
7 sensors Smart Robot - Maze Solver and Line Follower with programable PID controller via BT
==> Basic movement based on Nano Mouse Robot, developed by Michael Backus (http://www.akrobotnerd.com/ )
==> Line follow based on http://samvrit.tk/tutorials/pid-control-arduino-line-follower-robot/?ckattempt=1
==> CREDIT to Patrick McCabe for the path Solving Code, visit patrickmccabemakes.com!!
Marcelo Jose Rovai - 23 April, 2016 - Visit: http://mjrobot.org
-------------------------------------------------------------------*/

#include <Servo.h>
#include "robotDefines.h"

String command;
String device;

// BT Module
#include <SoftwareSerial.h>
SoftwareSerial BT1(10, 11); // El pin 10 es Rx y el pin 11 es Tx

//---------------------------------------------
void setup() 
{
  
  Serial.begin(9600);
  BT1.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  // line follow sensors
  pinMode(lineFollowSensor0, INPUT);
  pinMode(lineFollowSensor1, INPUT);
  pinMode(lineFollowSensor2, INPUT);
  pinMode(lineFollowSensor3, INPUT);
  pinMode(lineFollowSensor4, INPUT);
  
  // servos
  leftServo.attach(5);
  rightServo.attach(3);
  
  BT1.print("check the PID constants to be sent to Robot");
  BT1.println('\n');

  
  
  
  while (digitalRead(buttonPin) && !mode)
  {  
    checkBTcmd();  // verify if a comand is received from BT remote control
    manualCmd ();    
    command = "";  
  }
  
  motorFwTime (3000);
  
  checkPIDvalues();
  mode = STOPPED;
}

void loop() 
{
  readLFSsensors();  
  switch (mode)
  {   
    case NO_LINE:  
      motorStop();
      goAndTurn (LEFT, 180);
      break;
    
    case CONT_LINE: 
      runExtraInch();
      readLFSsensors();
      if (mode == CONT_LINE) mazeEnd();
      else goAndTurn (LEFT, 90);  // or it is a "T" or "Cross"). In both cases, goes to LEFT 
      break;
      
   case RIGHT_TURN: 
      runExtraInch();
      readLFSsensors();
      if (mode == NO_LINE) goAndTurn (RIGHT, 90); 
      break;   
      
   case LEFT_TURN: 
      goAndTurn (LEFT, 90); 
      break;   
   
   case FOLLOWING_LINE: 
      followingLine();
      break;      
      
  }
}


