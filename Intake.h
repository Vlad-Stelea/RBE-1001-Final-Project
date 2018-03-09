#include "Servo.h"
/*
 * Class representation of the intake mechanism
 * This mechanism is responsible for collecting ping pong balls from the floor
 * by rotating a motor
 */
 
class Intake{
  public:
    Intake(int motorPort);
    void runIntake();
    void stopIntake();
  private:
    Servo intakeMotor;
    const int motorSpeed = 180;//TODO tune optimal write output for the motor to pick up ping pong balls
};

