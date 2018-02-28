class LineTracker{
      public:
      LineTracker();
      void calibrate();
      enum FollowInstruction{
        LEFT, //The left sensor picked up white
        FORWARD, //Neither sensor picked up white
        RIGHT, //the right sensor picked up white
        HIT_LINE//both sensors are picking up white
      };
      FollowInstruction getState();
      const int LEFT_SENSOR_PORT = 1;
      const int RIGHT_SENSOR_PORT = 0;
      const int LEFT_THRESH_HOLD = 200;// anything greater will be white
      const int RIGHT_THRESH_HOLD = 550; //anything greater will be white
 };
