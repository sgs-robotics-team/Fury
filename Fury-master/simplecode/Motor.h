#ifndef MOTOR_H
#define MOTOR_H

#include <wiringPi.h>
#include <softPwm.h>
const int LEFT_MOTOR = 1;
const int RIGHT_MOTOR = 2;

class Motor
{
public:
    Motor();
    
    int getLeftSpeed() { return leftSpeed; }
    int getRightSpeed() { return rightSpeed; }

    void setLeftSpeed(int leftSpeed);
    void setRightSpeed(int rightSpeed);
    
    void setSpeed(int speed);
    
    void setDifferential(int differential);
    
private:
    int leftSpeed;
    int rightSpeed;
    
    int leftPrevSpeed;
    int rightPrevSpeed;

    float minRate;
    float maxRate;
    float stopRate;
};

#endif // MOTOR_H
