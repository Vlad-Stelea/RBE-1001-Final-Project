#include "Intake.h"
/**
 * Initializes an intake mechanism for this robot
 * @param motorPort the port that the intake motor is plugged into
 */
Intake::Intake(int motorPort){
  intakeMotor.attach(motorPort, 1000, 2000);
}
/**
 * Starts up the intake motor at the optimal output
 */
void Intake::runIntake(){
  intakeMotor.write(motorSpeed);
}
/**
 * Stops the intake from running anymore
 */
void Intake::stopIntake(){
  //90 means stop in the arduino servo library
  intakeMotor.write(90);
}



