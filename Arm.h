#include "Servo.h"

class Arm{

  public:
    Arm(int motorPin, int potPort);
    Servo armMotor;
    void dumpBalls();
    void togglePosition();
    void doState();
    int calibrationMethod();
  private:
    const int potPin;
    const int downAngle = 940; //TODO Tune
    const int dumpAngle = 500; // TODO Tune
    const int pK = 4;//TODO tune
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


