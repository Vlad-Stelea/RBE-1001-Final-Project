#include "MyRobot.h"
#include "Arduino.h"

bool r1Released = false;//keeps track if r1 has been released since it was pressed down
/**
 * These are the execution runtions
 */
void MyRobot::initialize(DriveTrain *driveTrain, Intake *intakeMech, Arm *armMech) {
  driveBase = driveTrain;
  intake = intakeMech;
  arm = armMech;
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
		Serial.print("\r\nAuto time remaining: ");
		Serial.print(time);
    /**
     * TODO
     */
    //driveBase->drive(1,1);
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
   Serial.println(arm->calibrationMethod());
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

