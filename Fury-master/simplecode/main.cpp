#include "Motor.h"
#include "Stepper.h"
#include "PID_Controller.h"
#include "Compass.h"
#include <unistd.h>
#include <iostream>
#include <fstream>

int diff(int ang1, int ang2){//ang1-ang2
	int diff=ang1-ang2;
	if (diff > 180){
		diff-=360;
	}
	if (diff < 180){
		diff+=360;
	}
}

int main(){
	std::ofstream log;
	Motor m;
	Stepper s;
	PID_Controller PID;
	Compass c;
	log.open("log.txt");
	pinMode(15,0);
	pullUpDnControl(15,PUD_DOWN);
	while(!digitalRead(15));
	int head = c.getHeading();
	m.setSpeed(30);
	for(int i = 0; i < 30; i++){
		usleep(1000000);
		int currhead=c.getHeading();
		int err = diff(currhead,head);
		int corr = (int)(PID.getCorrection(err));
		m.setSpeed(60);
		m.setDifferential(corr);
		log << i << ": head-" << currhead << " err-" << err << " corr-" << corr << " lsp-" << m.getLeftSpeed() << " rsp-" << m.getRightSpeed() << "\n";
	}
/*	m.setLeftSpeed(60);
	m.setRightSpeed(40);
	usleep(10000000);
	m.setSpeed(0);
	usleep(5000000);
	m.setLeftSpeed(60);
	m.setRightSpeed(50);
	usleep(10000000);
	m.setSpeed(0);
	usleep(5000000);
	m.setSpeed(60);
	usleep(10000000);
	m.setSpeed(0);
	usleep(5000000);
	m.setLeftSpeed(60);
	m.setRightSpeed(70);
	usleep(10000000);
	m.setSpeed(0);
	usleep(5000000);
	m.setLeftSpeed(60);
	m.setRightSpeed(80);
	usleep(10000000);*/
	log.close();
}
