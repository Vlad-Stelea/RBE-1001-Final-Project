#include <Encoder.h>
#include "Servo.h"

/**
 * Represents the drivetrain part of this robot
 */
class DriveTrain{
  private:
    Servo leftMotor, rightMotor;
    const int leftPort;
    const int rightPort;
    void testEncoders();
  public:
    DriveTrain(int leftMotorPort, int rightMotorPort);
    void driveStraight(double distance, double speedVal);
    void drive(double lValue, double rValue);
    void rotateTo(int angle);
    void stopDriving();
};
