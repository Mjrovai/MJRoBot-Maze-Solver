int mode = 0;

# define STOPPED 0
# define FOLLOWING_LINE 1
# define NO_LINE 2
# define CONT_LINE 3
# define POS_LINE 4
# define RIGHT_TURN 5
# define LEFT_TURN 6

const int power = 250;
const int iniMotorPower = 250;
const int adj = 0;
float adjTurn = 8;
int extraInch = 200;
int adjGoAndTurn = 800;

const int ledPin = 13;
const int buttonPin = 9;

// LFSensor more to the Left is "0"
const int lineFollowSensor0 = 12; 
const int lineFollowSensor1 = 18; 
const int lineFollowSensor2 = 17; 
const int lineFollowSensor3 = 16;
const int lineFollowSensor4 = 19;

const int farRightSensorPin = 0; //Analog Pin A0
const int farLeftSensorPin = 1; //Analog Pin A0
const int THRESHOLD = 150;
int farRightSensor = 0;
int farLeftSensor = 0;


int LFSensor[5]={0, 0, 0, 0, 0};

// PID controller
float Kp=50;
float Ki=0;
float Kd=0;

float error=0, P=0, I=0, D=0, PIDvalue=0;
float previousError=0, previousI=0;

#define RIGHT 1
#define LEFT -1

Servo leftServo;
Servo rightServo;

//-------------------------------------------------
//Specific Maze Phase 2 (optimization) definitions and variables 

unsigned char dir; 

// The path variable will store the path that the robot has taken:
//  'L' for left
//  'R' for right
//  'S' for straight (going straight through an intersection)
//  'B' for back (U-turn)

char path[100] = "";
unsigned char pathLength = 0; // the length of the path
int pathIndex = 0;
unsigned int status = 0; // solving = 0; reach end = 1



