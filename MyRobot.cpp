#include "MyRobot.h"
#include "Arduino.h"
#include "LineTracker.h"

enum autoState{
  LOW_GOAL,
  RED_MID,
  BLUE_MID
};

bool doneWithAuto = false;
autoState thisAuto; //represents the auto state of this program

bool r1Released = false;//keeps track if r1 has been released since it was pressed down
/**
 * These are the execution runtions
 */
void MyRobot::initialize(DriveTrain *driveTrain, Intake *intakeMech, Arm *armMech, MyEncoder *leftEnc, MyEncoder *rightEnc) {
  driveBase = driveTrain;
  intake = intakeMech;
  arm = armMech;
  lEnc = leftEnc;
  rEnc = rightEnc;
  pinMode(bumpSwitch, INPUT_PULLUP);
  if(digitalRead(24)){
    thisAuto = LOW_GOAL;
  }
}

void MyRobot::moveTo(unsigned position) {
}

/**
 * Called when the start button is pressed and the robot control begins
 */
 void MyRobot::robotStartup(){

 }

/**
 * Called by the controller between communication with the wireless controller
 * during autonomous mode
 * @param time the amount of time remaining
 * @param dfw instance of the DFW controller
 */
 void MyRobot::autonomous( long time){
  if(!doneWithAuto){
    Serial.println("IN AUTO");
    switch(thisAuto){
      case LOW_GOAL:
        lowGoalAuto();
        break;
    };
  }
    /**
     * TODO
     */
    //driveBase->drive(1,1);
  /*Serial.println("NumLines : " + String(numLines));
		switch(curState){
      case DRIVE_UNTIL_FOURTH:
      Serial.println("DRIVING");
        if(numLines >= 4){
          driveBase->drive(0,0);
          curState = TURN;
        }else{
          if(lTracker.getState() == LineTracker::HIT_LINE){
            curState = ON_LINE; 
            numLines++;
          }
          driveBase->drive(initialDriveSpeed, initialDriveSpeed);
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
		}*/
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
 enum LowGoalState{
    BACKWARDS,
    FORWARDS,
    DUMP
 };
 LowGoalState curLowGoalState = BACKWARDS;
/**
 * Drives backwards until it hits the bumper switch and dumps
 */
 void MyRobot::lowGoalAuto(){
    switch(curLowGoalState){
      case BACKWARDS:
      if(!digitalRead(bumpSwitch)){
        curLowGoalState = FORWARDS;
        lEnc->zero();
        rEnc->zero();
      }else{
        driveBase->drive(-.5, -.5);
      }
        break;
      case FORWARDS:
        if(rEnc->getDegrees() >= 45 || lEnc->getDegrees() >=45){
          driveBase->drive(0,0);
          curLowGoalState = DUMP;
        }else{
          driveBase->drive(.2,.2);
        }
        break;
      case DUMP:
      arm->doState();
        break;
    }
 }
 enum MidGoalAutoState{
    INITIAL_FORWARD,
    ROTATE_NINETY,
    DRIVE_BACKWARDS,
    LINEUP_FORWARDS,
    DUMP
 };
 MidGoalAutoState curMidAutoState = INITIAL_FORWARD;
  /**
   * Drives forward until the distance the robot travels is 92.75 inches
   * Rotates 90 degrees
   * Drives backwards until it hits it's bump switch
   * Drives forward 1.5 inches
   * Dumps it's payload
   */
 void MyRobot::blueMidGoalAuto(){
  
 }

