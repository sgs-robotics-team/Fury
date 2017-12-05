#include "Stepper.h"
#include <cstdio>

int CCONV AttachHandler(CPhidgetHandle stepper, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (stepper, &name);
	CPhidget_getSerialNumber(stepper, &serialNo);
	printf("%s %10d attached!\n", name, serialNo);

	return 0;
}

int CCONV PositionChangeHandler(CPhidgetStepperHandle stepper, void *usrptr, int Index, __int64 Value)
{
	printf("Motor: %d > Current Position: %lld\n", Index, Value);
	return 0;
}

Stepper::Stepper(){
  int result = 0;
  stepper = 0;
  
  //create the stepper object
  CPhidgetStepper_create(&stepper);
  
  //open the device for connections
  CPhidget_open((CPhidgetHandle)stepper, -1);
  
  const char* err;
  
  CPhidget_set_OnAttach_Handler((CPhidgetHandle)stepper, AttachHandler, NULL);
  CPhidgetStepper_set_OnPositionChange_Handler(stepper, PositionChangeHandler, NULL);
  //get the program to wait for an stepper device to be attached
  printf("Waiting for Phidget to be attached....");
  if((result = CPhidget_waitForAttachment((CPhidgetHandle)stepper, 10000)))
    {
      CPhidget_getErrorDescription(result, &err);
      printf("Problem waiting for attachment: %s\n", err);
    }
  
  //Set up some initial acceleration and velocity values
  CPhidgetStepper_getAccelerationMin(stepper, 0, &minAccel);
  CPhidgetStepper_setAcceleration(stepper, 0, minAccel*1000);
  CPhidgetStepper_getVelocityMax(stepper, 0, &maxVel);
  CPhidgetStepper_setVelocityLimit(stepper, 0, maxVel*500);
  
  CPhidgetStepper_setCurrentPosition(stepper, 0, 0);
  CPhidgetStepper_setEngaged(stepper, 0, 1);
}

void Stepper::setAngle(long ang){
  pos=ang*ANG_FACTOR;
  CPhidgetStepper_setTargetPosition (stepper, 0, pos);
}

Stepper::~Stepper(){
  CPhidget_close((CPhidgetHandle)stepper);
  CPhidget_delete((CPhidgetHandle)stepper);
}
