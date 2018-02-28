#include "DriveTrain.h"
MD_REncoder leftEncoder(12,13);
MD_REncoder rightEncoder(22,23);

/**
 * Instantiates a drive train object
 * @param leftMotorPort the port that the left motor is attached to
 * @param rightMotorPort the port that the right motor is attached to
 */
DriveTrain::DriveTrain(int leftMotorPort, int rightMotorPort):
                          leftPort(leftMotorPort),rightPort(rightMotorPort){
  leftMotor.attach(leftMotorPort, 1000, 2000);
  rightMotor.attach(rightMotorPort, 1000, 2000);
  drive(0,0);
  leftEncoder.begin();
}
/**TODO
 * Drives the robot straight using Proportion control for a set given speed
 * @param speedVal the speed that the motors should be idealy driving during this 
 *  function. This is a value between 0 and 1.
 */
void DriveTrain::driveStraight(double speedVal){
  
}

/**
 * Drive the robot using teleoperated control
 * @param lValue double between -1 and 1: -1 being full back, 1 being full forward for left motor 
 * @param rValue double between -1 and 1: -1 being full back, 1 being full forward for right motor 
 */
void DriveTrain::drive(double lValue, double rValue){
  rightMotor.write(90 - (90*rValue));
  leftMotor.write(90 + (90*lValue));
  //testEncoders();
}
int rotateAngle = 0;
/** TODO implement
 * Rotate to the given angle using encoders and PID
 * @param angle angle in degrees to rotate to from starting position
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

/**
 * Prints out the values of the encoders
 */
void DriveTrain::testEncoders(){
  uint8_t x = leftEncoder.read();
  if (x) 
  {
    Serial.print(x == DIR_CW ? "\n+1" : "\n-1");
#if ENABLE_SPEED
    Serial.print("  ");
    Serial.print("Left Encoder " + String(leftEncoder.speed()) + " Right Encoder: " + String(rightEncoder.speed()));
#endif
  }
}



