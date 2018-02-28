#include "MyRobot.h"
#include "Arduino.h"


bool r1Released = false;//keeps track if r1 has been released since it was pressed down
//Represents the team that the robot is currently on
enum team{
  RED,
  BLUE
};
team curTeam;
enum autoState{
  DRIVE_UNTIL_FOURTH,//skips until the fourth white line
  ON_LINE,
  TURN,//Turning sequence for going 90 degrees
  BACK_UP,//Final backup sequence
  DUMP_BALLS
};
autoState curState = DRIVE_UNTIL_FOURTH;
/**
 * These are the execution runtions
 */
void MyRobot::initialize(DriveTrain *driveTrain, Intake *intakeMech, Arm *armMech) {
  driveBase = driveTrain;
  intake = intakeMech;
  arm = armMech;
  pinMode(BLUE_PORT, INPUT);
  if(digitalRead(BLUE_PORT)){
    curTeam = BLUE;
  }else{
    curTeam = RED;
  }
  pinMode(BUMPER_PORT, INPUT_PULLUP);
  
}

void MyRobot::moveTo(unsigned position) {
}

/**
 * Called when the start button is pressed and the robot control begins
 */
 void MyRobot::robotStartup(){

 }
 int numLines = 0;//keeps track of the number of white lines crossed over
 long timeToStopTurning;// keeps track of when the robot should stop turning during the turning step
/**
 * Called by the controller between communication with the wireless controller
 * during autonomous mode
 * @param time the amount of time remaining
 * @param dfw instance of the DFW controller
 */
 void MyRobot::autonomous( long time){
		switch(curState){
      case DRIVE_UNTIL_FOURTH:
        if(numLines >= 5){
          driveBase->drive(0,0);
          curState = TURN;
        }else{
          if(lTracker.getState() == LineTracker::HIT_LINE){
            curState = ON_LINE; 
            numLines++;
          }
          driveBase->drive(initialDriveSpeed, initialDriveSpeed-.1);//TODO maybe change to drive straight depending on encoders
        }
        break;
      case ON_LINE://Makes sure that the robot doesn't read the same white line multiple times
        if(lTracker.getState() == LineTracker::FORWARD){
          curState = DRIVE_UNTIL_FOURTH;
        }
        break;
      case TURN: 
        if(time == timeToStopTurning){
          driveBase->drive(0, 0);
          curState = BACK_UP;
        }else if (curTeam == BLUE){
          driveBase->drive(turnSpeed ,-turnSpeed);
        }else{
          driveBase->drive(-turnSpeed, turnSpeed);
        }
        break;
      case BACK_UP:
        if(!digitalRead(BUMPER_PORT)){
          curState = DUMP_BALLS;
        }else{
          driveBase->drive(-.5,-.5);
          arm->dumpBalls();
        }
        break;
     case DUMP_BALLS:
      arm->doState();
      break;
		}
 }
/**
 * Called by the controller between communication with the wireless controller
 * during teleop mode
 * @param time the amount of time remaining
 * @param dfw instance of the DFW controller
 */
 void MyRobot::teleop( long time){   
		//Run functions in the robot class
   arm->doState();
   //Serial.println(arm->calibrationMethod());
   double rightJoystickVal = static_cast<double>(dfw->joystickrv()); 
   double leftJoystickVal = static_cast<double>(dfw->joysticklv()); 
   convertJoystickSignalToDrive(leftJoystickVal, rightJoystickVal);
   driveBase->drive(leftJoystickVal, rightJoystickVal);
   if(dfw->r2()){
      intake->runIntake();
   }else{
      intake->stopIntake();
   }
   if(dfw->r1() && r1Released){
      arm->togglePosition();
      r1Released = false;
   }else{
    r1Released = true;
   }
   
 }
/**
 * Called at the end of control to reset the objects for the next start
 */
 void MyRobot::robotShutdown(void){
		Serial.println("Here is where I shut down my robot code");
    driveBase->stopDriving();
 }

 /**
 * Converts the passed in joystick values from dfw and converts them to drive values
 *  using references
 * @param lValue the left joystick value
 * @param rValue the right joystick value
 */
 void MyRobot::convertJoystickSignalToDrive(double &lValue, double &rValue){
  lValue = ((lValue-90)/90);
  rValue = (rValue-90)/90;
 }


