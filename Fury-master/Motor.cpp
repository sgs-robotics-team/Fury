#include <iostream>
#include <cmath>
#include <phidget21.h>

#include "Motor.h"

Motor::Motor()
{
	leftSpeed = 0;
	rightSpeed = 0;
	leftPrevSpeed = 0;
	rightPrevSpeed = 0;
	minRate = -100;
	maxRate = 100;
	stopRate = 0;
	

	wiringPiSetup();
	pinMode(1,2);
	pinMode(2,2);
	softPwmCreate(1,15,25);
	softPwmCreate(2,15,25);
};
Motor::setLeftSpeed(int leftSpeed){
	softPwmWrite(1,leftSpeed/10+15);
};
Motor::setRightSpeed(int RightSpeed){
        softPwmWrite(1,RightSpeed/10+15);
};
Motor::setSpeed(int speed){
        softPwmWrite(1,speed/10+15);
	softPwmWrite(2,speed/10+15);
};
Motor::setDifferential(int differential){
	softPwmWrite(1,(getLeftSpeed()+differential)/10+15);
	softPwmWrite(1,(getRightSpeed()-differential)/10+15);
};

