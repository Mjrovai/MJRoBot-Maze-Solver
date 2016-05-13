void mazeSolve(void)
{
    while (!status)
    {
        readLFSsensors();  
        switch (mode)
        {   
          case NO_LINE:  
            motorStop();
            goAndTurn (LEFT, 180);
            recIntersection('B');
            break;
          
          case CONT_LINE: 
            runExtraInch();
            readLFSsensors();
            if (mode != CONT_LINE) {goAndTurn (LEFT, 90); recIntersection('L');} // or it is a "T" or "Cross"). In both cases, goes to LEFT
            else mazeEnd(); 
            break;
            
         case RIGHT_TURN: 
            runExtraInch();
            readLFSsensors();
            if (mode == NO_LINE) {goAndTurn (RIGHT, 90); recIntersection('R');}
            else recIntersection('S');
            break;   
            
         case LEFT_TURN: 
            goAndTurn (LEFT, 90); 
            recIntersection('L');
            break;   
         
         case FOLLOWING_LINE: 
            followingLine();
            break;      
        
         }
    }
}

//---------------------------------------------
void recIntersection(char direction)
{
  path[pathLength] = direction; // Store the intersection in the path variable.
  pathLength ++;
  simplifyPath(); // Simplify the learned path.
}

//----------------------------------------------
void mazeEnd(void)
{
  motorStop();
  BT1.print("The End  ==> Path: ");
  for(int i=0;i<pathLength;i++)
    BT1.print(path[i]);
    //Serial.print(path[i]);
  BT1.println("");
  Serial.print("  pathLenght ==> ");
  Serial.println(pathLength);
  status = 1;
  mode = STOPPED;
}

//----------------------------------------------
void followingLine(void)
{
   //readLFSsensors(); 
   calculatePID();
   motorPIDcontrol();   
}

//------------------------------------------------------------------------------------------
// Path simplification.  The strategy is that whenever we encounter a
// sequence xBx, we can simplify it by cutting out the dead end.  For
// example, LBL -> S, because a single S bypasses the dead end
// represented by LBL.
void simplifyPath()
{
  // only simplify the path if the second-to-last turn was a 'B'
  if(pathLength < 3 || path[pathLength-2] != 'B')
    return;

  int totalAngle = 0;
  int i;
  for(i=1;i<=3;i++)
  {
    switch(path[pathLength-i])
    {
      case 'R':
        totalAngle += 90;
	break;
      case 'L':
	totalAngle += 270;
	break;
      case 'B':
	totalAngle += 180;
	break;
    }
  }

  // Get the angle as a number between 0 and 360 degrees.
  totalAngle = totalAngle % 360;

  // Replace all of those turns with a single one.
  switch(totalAngle)
  {
    case 0:
	path[pathLength - 3] = 'S';
	break;
    case 90:
	path[pathLength - 3] = 'R';
	break;
    case 180:
	path[pathLength - 3] = 'B';
	break;
    case 270:
	path[pathLength - 3] = 'L';
	break;
  }

  // The path is now two steps shorter.
  pathLength -= 2;
  
} 

//----------------------------------------------------------------------------------------------
void mazeOptimization (void)
{
  while (!status)
  {
    readLFSsensors();  
    switch (mode)
    {
      case FOLLOWING_LINE:
        followingLine();
        break;    
      case CONT_LINE:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (path[pathIndex]); pathIndex++;}
        break;  
      case LEFT_TURN:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (path[pathIndex]); pathIndex++;}
        break;  
      case RIGHT_TURN:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (path[pathIndex]); pathIndex++;}
        break;   
    }    
   }  
}

//-----------------------------------------------------
void mazeTurn (char dir) 
{
  switch(dir)
  {
    case 'L': // Turn Left
       goAndTurn (LEFT, 90);      
       break;   
    
    case 'R': // Turn Right
       goAndTurn (RIGHT, 90);     
       break;   
       
    case 'B': // Turn Back
       goAndTurn (RIGHT, 800);     
       break;   
       
    case 'S': // Go Straight
       runExtraInch(); 
       break;
  }
}
