#include <phidget21.h>

#ifndef STEPPER_H
#define STEPPER_H

const int ANG_FACTOR = 720;//teeth times "degrees" for full circle of stepper

class Stepper{
  long pos;//zero is flat
  double minAccel, maxVel;
  int stopped;
  CPhidgetStepperHandle stepper;
 public:
  Stepper();
  long getAngle(){return pos;}
  void setAngle(long);
  ~Stepper();
};

#endif
