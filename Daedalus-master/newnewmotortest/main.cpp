#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
int main(){
	wiringPiSetup();
	pinMode(1,2);
	pinMode(2,2);
	pinMode(15,0);
	pullUpDnControl(15,PUD_DOWN);
	while (!digitalRead(15));
	softPwmCreate(1,19,100);
	softPwmCreate(2,23,100);
	delayMicroseconds (40000000);
}
