#include "MyRobot.h"
#include "Arduino.h"
#include "LineTracker.h"

enum autoState{
  LOW_GOAL,
  RED_MID,
  BLUE_MID
};

autoState thisAuto; //represents the auto state of this program

bool r1Released = false;//keeps track if r1 has been released since it was pressed down
/**
 * These are the execution runtions
 */
void MyRobot::initialize(DriveTrain *driveTrain, Intake *intakeMech, Arm *armMech, MyEncoder *leftEnc, MyEncoder *rightEnc) {
  pinMode(22, INPUT);
  driveBase = driveTrain;
  intake = intakeMech;
  arm = armMech;
  lEnc = leftEnc;
  rEnc = rightEnc;
  pinMode(bumpSwitch, INPUT_PULLUP);
  if(analogRead(0)){
    thisAuto = LOW_GOAL;
  }else if(analogRead(2)){
    thisAuto = RED_MID;
  }else if (analogRead(3)){
    thisAuto = BLUE_MID;
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
    switch(thisAuto){
      case LOW_GOAL:
        lowGoalAuto();
        break;
      case BLUE_MID:
        blueMidGoalAuto();
        break;
      case RED_MID:
        redMidGoalAuto();
        
    };
    
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
          driveBase->drive(.4,.4);
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
    MID_DUMP
 };
 MidGoalAutoState curMidAutoState = INITIAL_FORWARD;
  /**
   * Drives forward until the distance the robot travels is 92.75 inches
   * Rotates 90 degrees to the left
   * Drives backwards until it hits it's bump switch
   * Drives forward 1.5 inches
   * Dumps it's payload
   */
 void MyRobot::blueMidGoalAuto(){
  switch(curMidAutoState){
    case INITIAL_FORWARD:
        
      if(rEnc->getDegrees() >= 1240 || lEnc->getDegrees() >= 1240){
        driveBase->drive(0,0);
        curMidAutoState = ROTATE_NINETY;
        lEnc->zero();
        rEnc->zero();
      }else{
        driveBase->drive(.76,.75);
      }
      break;
    case ROTATE_NINETY:
      if(rEnc->getDegrees() >= 170|| lEnc->getDegrees()>= 170){
        driveBase->drive(0,0);
        curMidAutoState = DRIVE_BACKWARDS;
        lEnc->zero();
        rEnc->zero();
      }else{
        driveBase->drive(.5, -.5);
      }
      break;
    case DRIVE_BACKWARDS:
      if(!digitalRead(bumpSwitch) || rEnc->getDegrees() >= 300){
          curMidAutoState = LINEUP_FORWARDS;
          lEnc->zero();
          rEnc->zero();
        }else{
          driveBase->drive(-.5, -.5);
        }
      break;
    case LINEUP_FORWARDS:
        if(rEnc->getDegrees() >= 85 || lEnc->getDegrees() >=85){
          driveBase->drive(0,0);
          curMidAutoState = MID_DUMP;
        }else{
          driveBase->drive(.4,.4);
        }
      break;
    case MID_DUMP:
      arm->doState();
      break;
  }
 }

   /**
   * Auto for red side middle goal
   * Drives forward until the distance the robot travels is 92.75 inches
   * Rotates 90 degrees to the right
   * Drives backwards until it hits it's bump switch
   * Drives forward 1.5 inches
   * Dumps it's payload
   */
 void MyRobot::redMidGoalAuto(){
  switch(curMidAutoState){
    case INITIAL_FORWARD:
        
      if(rEnc->getDegrees() >= 1373 || lEnc->getDegrees() >= 1373){
        driveBase->drive(0,0);
        curMidAutoState = ROTATE_NINETY;
        lEnc->zero();
        rEnc->zero();
      }else{
        driveBase->drive(.76,.75);
      }
      break;
    case ROTATE_NINETY:
      if(rEnc->getDegrees() >= 170|| lEnc->getDegrees()>= 170){
        driveBase->drive(0,0);
        curMidAutoState = DRIVE_BACKWARDS;
        lEnc->zero();
        rEnc->zero();
      }else{
        driveBase->drive(-.5, .5);
      }
      break;
    case DRIVE_BACKWARDS:
      if(!digitalRead(bumpSwitch) || rEnc->getDegrees() >= 300){
          curMidAutoState = LINEUP_FORWARDS;
          lEnc->zero();
          rEnc->zero();
        }else{
          driveBase->drive(-.5, -.5);
        }
      break;
    case LINEUP_FORWARDS:
        if(rEnc->getDegrees() >= 85 || lEnc->getDegrees() >=85){
          driveBase->drive(0,0);
          curMidAutoState = MID_DUMP;
        }else{
          driveBase->drive(.4,.4);
        }
      break;
    case MID_DUMP:
      arm->doState();
      break;
  }
 }

