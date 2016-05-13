void mazeEnd(void)
{
  motorStop();
  BT1.print("The End");
  mode = STOPPED;
  while (digitalRead(buttonPin))
  { 
    ledBlink();
  }
}

//----------------------------------------------
void followingLine(void)
{
   readLFSsensors(); 
   calculatePID();
   motorPIDcontrol();   
}

//----------------------------------------------

