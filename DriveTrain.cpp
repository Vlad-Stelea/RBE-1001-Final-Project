#include "DriveTrain.h"
/**
 * Instantiates a drive train object
 * @param leftMotorPort the port that the left motor is attached to
 * @param rightMotorPort the port that the right motor is attached to
 */
DriveTrain::DriveTrain(int leftMotorPort, int rightMotorPort):
                          leftPort(leftMotorPort),rightPort(rightMotorPort){
  leftMotor.attach(leftMotorPort, 1000, 2000);
  rightMotor.attach(rightMotorPort, 1000, 2000);
}
/**TODO
 * Drives the robot straight using PID for a set distance at a given speed
 * @param distance the distance in inches that the robot has to drive
 * @param speedVal the speed that the motors should be driving during this 
 *  function. This is a value between 0 and 1.
 */
void DriveTrain::driveStraight(double distance, double speedVal){
  
}

/**TODO invert one of the motors
 * Drive the robot using teleoperated control
 * @param lValue double between -1 and 1: -1 being full back, 1 being full forward for left motor 
 * @param rValue double between -1 and 1: -1 being full back, 1 being full forward for right motor 
 */
void DriveTrain::drive(double lValue, double rValue){
  rightMotor.write(lValue);
  leftMotor.write(rValue);
}
/** TODO implement
 * Rotate to the given angle using encoders and PID
 * @param angle angle in radians to rotate to from starting position
 */
void DriveTrain::rotateTo(int angle){
  
}
/**
 * Sets all motor output to zero
 */
void DriveTrain::stopDriving(){
  leftMotor.write(90);
  rightMotor.write(90);
}


