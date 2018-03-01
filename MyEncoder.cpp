#include <Arduino.h>
#include "MyEncoder.h"

/**
 * Initializes a quadature encoder object that takes in an interupt pin
 *  to count how many ticks and a digital pin to determine the direction that the
 *  encoder is rotating
 * @param countPort the interupt port which will trigger everytime there is a tick
 * @param directionPin the digital pin that will read what direction the encoder was moving
 */
MyEncoder::MyEncoder(){
}
/**
 * Resets the encoder count back to zero
 */
void MyEncoder::zero(){
  totalDegrees = 0;
}

/**
 * returns the number of degrees that the encoder has turned since it's been last zeroed
 */
int MyEncoder::getDegrees(){
  return totalDegrees;
}

/**
 * triggered whenever the encoder turns
 * increments the count
 */
void MyEncoder::encoderTurn(){
  totalDegrees++;
}

