/**
 * Class that keeps track of the state of quadature encoders
 * This includes rotations since it's been zeroed
 */
class MyEncoder{
  public:
    MyEncoder();
    void zero();
    int getDegrees();
    void encoderTurn();
  private:
    volatile int totalDegrees; //Quadature encoder has 360 tickes per revolution
    const int directionPort;//port that reads which direction the encoder is turning
};

