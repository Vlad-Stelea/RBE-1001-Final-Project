#include <MD_REncoder.h>
#include "Servo.h"


/**
 * Represents the drivetrain part of this robot
 */
class DriveTrain{
  private:
    int leftRotations, rightRotations = 0; //The number of full rotations from the left and right side
    Servo leftMotor, rightMotor;
    const int leftPort;
    const int rightPort;
    const int lineTrackingSpeed = .5;
    void testEncoders();
    void followLine();
    public:
    DriveTrain(int leftMotorPort, int rightMotorPort);
    void driveStraight(double speedVal);
    void drive(double lValue, double rValue);
    void rotateTo(int angle);
    void stopDriving();
};

