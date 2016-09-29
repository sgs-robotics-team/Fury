#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <unistd.h>

int main(){
	wiringPiSetup();
	pinMode(15,0);
	pullUpDnControl(15,PUD_DOWN);
	while(true){
		usleep(100000);
		std::cout << digitalRead(15) << std::endl;
	}
}
