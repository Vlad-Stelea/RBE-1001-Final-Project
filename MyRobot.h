#pragma once

#include <DFW.h>
#include <AbstractDFWRobot.h>
#include "DriveTrain.h"
#include "Intake.h"
#include "Arm.h"
#include "MyEncoder.h"


class MyRobot :public AbstractDFWRobot{
  private:
    void lowGoalAuto();
    void blueMidGoalAuto();
     const int bumpSwitch = 25;
  public:
  	DFW * dfw;
    DriveTrain *driveBase;
    Intake *intake;
    Arm *arm;
    MyEncoder *lEnc; 
    MyEncoder *rEnc;
   
  	/**
  	 * Called when the start button is pressed and the robot control begins
  	 */
  	 void robotStartup();
  	/**
  	 * Called by the controller between communication with the wireless controller
  	 * during autonomous mode
  	 * @param time the amount of time remaining
  	 * @param dfw instance of the DFW controller
  	 */
  	 void autonomous( long time);
  	/**
  	 * Called by the controller between communication with the wireless controller
  	 * during teleop mode
  	 * @param time the amount of time remaining
  	 * @param dfw instance of the DFW controller
  	 */
  	 void teleop(long time);
  	/**
  	 * Called at the end of control to reset the objects for the next start
  	 */
  	 void robotShutdown(void);
  	/**
  	 * Return the number of the LED used for controller signaling
  	 */
  	 int getDebugLEDPin(void){return 13;};
  
  	void initialize(DriveTrain *driveTrain, Intake*, Arm*, MyEncoder*, MyEncoder*);
  	void moveTo(unsigned position);
    void convertJoystickSignalToDrive(double &lValue, double &rValue);
  	~MyRobot(){};
};
