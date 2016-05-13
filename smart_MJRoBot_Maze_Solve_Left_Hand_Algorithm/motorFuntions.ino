
void motorStop()
{
  leftServo.writeMicroseconds(1500);
  rightServo.writeMicroseconds(1500);
  delay(200);
}

//--------------------------------------------- 
void motorForward()
{
  leftServo.writeMicroseconds(1500 - (power+adj));
  rightServo.writeMicroseconds(1500 + power);
}

//---------------------------------------------
void motorBackward()
{
  leftServo.writeMicroseconds(1500 + power);
  rightServo.writeMicroseconds(1500 - power);
}

//---------------------------------------------
void motorFwTime (unsigned int time)
{
  motorForward();
  delay (time);
  motorStop();
}

//---------------------------------------------
void motorBwTime (unsigned int time)
{
  motorBackward();
  delay (time);
  motorStop();
}

//------------------------------------------------
void motorTurn(int direction, int degrees)
{
  leftServo.writeMicroseconds(1500 - (iniMotorPower+adj)*direction);
  rightServo.writeMicroseconds(1500 - iniMotorPower*direction);
  delay (round(adjTurn*degrees+1));
  motorStop();
}

//---------------------------------------------------
void motorPIDcontrol()
{
  
  int leftMotorSpeed = 1500 - (iniMotorPower+adj) - PIDvalue;
  int rightMotorSpeed = 1500 + iniMotorPower - PIDvalue;
  
  // The motor speed should not exceed the max PWM value
   constrain(leftMotorSpeed, 1000, 2000);
   constrain(rightMotorSpeed, 1000, 2000);
  
  leftServo.writeMicroseconds(leftMotorSpeed);
  rightServo.writeMicroseconds(rightMotorSpeed);
  
  //Serial.print (PIDvalue);
  //Serial.print (" ==> Left, Right:  ");
  //Serial.print (leftMotorSpeed);
  //Serial.print ("   ");
  //Serial.println (rightMotorSpeed);
}

//---------------------------------------------------
void runExtraInch(void)
{
  motorPIDcontrol();
  delay(extraInch);
  motorStop();
}

//---------------------------------------------------
void goAndTurn(int direction, int degrees)
{
  motorPIDcontrol();
  delay(adjGoAndTurn);
  motorTurn(direction, degrees);
}
//-----------------------------
void drivePolygon(unsigned int time, int sides) // for motor test only
{
    for (int i = 0; i<sides; i++)
    {
        motorFwTime (time);
        motorTurn(RIGHT, 360/sides);
    }

}
