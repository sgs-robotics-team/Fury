
#include <iostream>
#include <cmath>
#include <phidget21.h>

#include "Motor.h"

int min(int a, int b){
	if(a<b){
		return a;
	}
	return b;
}

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
	pinMode(LEFT_MOTOR,2);
	pinMode(RIGHT_MOTOR,2);
	softPwmCreate(LEFT_MOTOR,15,100);
	softPwmCreate(RIGHT_MOTOR,15,100);
};
void Motor::setLeftSpeed(int leftSpeed){
	softPwmWrite(LEFT_MOTOR,leftSpeed/10+15);
};
void Motor::setRightSpeed(int RightSpeed){
        softPwmWrite(RIGHT_MOTOR,RightSpeed/10+15);
};
void Motor::setSpeed(int speed){
        softPwmWrite(LEFT_MOTOR,speed/10+15);
	softPwmWrite(RIGHT_MOTOR,speed/10+15);
};
void Motor::setDifferential(int differential){
	softPwmWrite(LEFT_MOTOR,(min((getLeftSpeed()+differential)/10+15,100)));
	softPwmWrite(RIGHT_MOTOR,(min((getRightSpeed()-differential)/10+15,100)));
};

