/* This is the RBE 1001 Template as of
 *
 * 3/28/17
 *
 * This Template
 * is designed to run the autonomous and teleop sections of the final
 * competition. Write and test your autonomous and teleop code on your
 * own and place the code in auto.cpp or teleop.cpp respectively.
 * The functions will be called by the competition framework based on the
 * time and start button. DO NOT change this file, your code will be called
 * by the framework. The framework will pass your code a reference to the DFW
 * object as well as the amount of MS remaining.
 */
#include <DFW.h>
#include "MyRobot.h"

const int LEFT_DRIVE_MOTOR_PORT = 11;
const int RIGHT_DRIVE_MOTOR_PORT = 9;
const int INTAKE_MOTOR_PORT = 8;
const int ARM_MOTOR_PORT = 10;
const int ARM_POT_PIN = 11;
void convertJoystickSignalToDrive(double &lValue, double &rValue);


MyRobot robot;
DFW dfw(&robot); // Instantiates the DFW object and setting the debug pin. The debug pin will be set high if no communication is seen after 2 seconds
DriveTrain *driveTrain;
Intake *intake;
Arm *arm;

void setup() {
	Serial.begin(9600); // Serial output begin. Only needed for debug
	dfw.begin(); // Serial1 output begin for DFW library. Buad and port #."Serial1 only"
	robot.initialize(new DriveTrain(LEFT_DRIVE_MOTOR_PORT, RIGHT_DRIVE_MOTOR_PORT),
	                 new Intake(INTAKE_MOTOR_PORT),
	                 new Arm(ARM_MOTOR_PORT, ARM_POT_PIN));
  robot.dfw=&dfw;
}
void loop() {
  dfw.run();
  robot.teleop(0);
}



