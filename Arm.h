#include "Servo.h"

class Arm{

  public:
    Arm(int motorPin, int potPort);
    Servo armMotor;
    void togglePosition();
    void doState();
    int calibrationMethod();
    void dumpBalls();
  private:
    const int potPin;
    const int downAngle = 1008; //TODO Tune
    const int dumpAngle = 545; // TODO Tune
    const int pK = 5;//TODO tune
    const int POT_LEEWAY = 4;
    int requiredAngle = 0; //More efficient state since adding an enum would add a second check to methods
                           //As well as the required setting of the variable
    int convertMotorSignal(int motorSpeed);
    void pickUpPosition();
    enum State{
      dump, //Dump the balls
      collect //Collect the balls
   };
   State state;
    
};

