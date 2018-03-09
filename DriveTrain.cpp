#include "DriveTrain.h"
Encoder leftEncoder(2,3);
Encoder rightEncoder(18,19);
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


/**
 * Drive the robot using teleoperated control
 * @param lValue double between -1 and 1: -1 being full back, 1 being full forward for left motor 
 * @param rValue double between -1 and 1: -1 being full back, 1 being full forward for right motor 
 */
void DriveTrain::drive(double lValue, double rValue){
  rightMotor.write(90 - (90*rValue));
  leftMotor.write(90 + (90*lValue));
  //Make sure encoders are working properly
  //testEncoders();
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
  Serial.println("Left: " + String(leftEncoder.read()) + "Right: " + String(leftEncoder.read()));
}


