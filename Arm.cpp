#include "Arm.h"
#include <Arduino.h>

Arm::Arm(int motorPin, int potPort):potPin(potPort){
  armMotor.attach(motorPin, 1000, 2000);
}
/**
 * Sets the state to be ready to dump balls by changing the requiredAngle
 */
void Arm::dumpBalls(){
  requiredAngle = dumpAngle;
}
/**
 * Sets the state to be in the pickup position by changing the requiredAngle
 */
void Arm::pickUpPosition(){
  requiredAngle = downAngle;
}
/**
 * incrementally moves the arm to the desired angle using proportional control
 */
void Arm::doState(){
  int potValue;
  int perDev;
  if(abs(perDev = (requiredAngle - (potValue = analogRead(potPin)))) > POT_LEEWAY){
    armMotor.write(convertMotorSignal(-(perDev * pK)));
  }
}
/**
 * Returns the value that the potentiometer attached to the arm is outputing
 * @return integer from 0 to 1023 where 0 and 1023 represent full rotations in oposite directions
 */
int Arm::calibrationMethod(){
  return analogRead(potPin);
}
/**
 * TODO give proper commenting
 */
int Arm::convertMotorSignal(int motorSpeed){
  if(motorSpeed > 90)
    motorSpeed = 90;
  if(motorSpeed < -90)
    motorSpeed = -90;
  return 90 + motorSpeed;
}
