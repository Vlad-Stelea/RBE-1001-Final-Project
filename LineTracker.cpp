/**
 * An interface for the Line tracker on this robot
 */
#include <Arduino.h>
#include "LineTracker.h"

/**
 * Instantiates a line tracker object
 */
LineTracker::LineTracker(){
}
/**
 * Evaluates what state the line tracker is in 
 * @return a FollowInstruction based on what the robot needs to do
 */
LineTracker::FollowInstruction LineTracker::getState(){
  bool leftValue = analogRead(LEFT_SENSOR_PORT) > LEFT_THRESH_HOLD;
  bool rightValue = analogRead(RIGHT_SENSOR_PORT) > RIGHT_THRESH_HOLD;

  if(leftValue && rightValue){
    return HIT_LINE;
  }else if (leftValue){
    return LEFT;
  }else if(rightValue){
    return RIGHT;
  }
  return FORWARD;
}

void LineTracker::calibrate(){
  Serial.println("LEFT PHOTO-RESISTOR: " + String(RIGHT_SENSOR_PORT) + " RIGHT PHOTO-RESISTOR: " + String(analogRead(LEFT_SENSOR_PORT)));
}

