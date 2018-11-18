#include <cstdio> 
#include <cstdlib>
#include <cerrno>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include "Motor.h"

std::string alarm_description[27];

Motor::Values::Values(){

	


}

Motor::Motor()
{

	std::string portname = "/dev/ttyUSB0";
	std::cout << "start" << std::endl;
	fd = open(portname.c_str(),O_RDWR);//|O_NOCTTY|O_NDELAY);
	if(fd < 0){
		printf("Error attaching SeaDrone Smart Motor Thruster on %s.\n", portname.c_str());
		printf(" %d\n",fd);
	}
	std::cout << "connected port\n";
	initializeInterface(B921600);
	std::cout << "initiazlied interface\n";
	readMotor();
	std::cout << "read motor\n";
	sendCommand();
	std::cout << "sent command\n";
}

int Motor::initializeInterface(int speed){

	struct termios tty;
	memset(&tty,0,sizeof tty);
	if(tcgetattr(fd,&tty)!=0){
		printf("Error %d from tcgetattr.\n",errno);
		return -1;
	}
	
	cfsetspeed(&tty,speed);
	
	tty.c_cflag &= ~PARENB; //no parity
	tty.c_cflag &= ~CSTOPB; //two stop bits
	tty.c_cflag &= ~CSIZE; //
	tty.c_cflag |= CS8; //eight bits

	tty.c_cc[VMIN]	= 0;
	tty.c_cc[VTIME] = 0.01;

	if(tcsetattr(fd,TCSANOW,&tty)!=0){
		printf("Error %d from tcgetattr.\n",errno);
		return -1;
	}
	
        alarm_description[0] = "No alarm";
        alarm_description[16] = "Driver temperature too high";
        alarm_description[18] = "Input voltage too high";
        alarm_description[19] = "Input voltage too low";
        alarm_description[20] = "Motor speed/acceleration too high";
        alarm_description[21] = "Over current, payload is too high";
        alarm_description[26] = "Alarm 0x1A, overcurrent";
	return 0;
}

void Motor::readMotor(){

	char c = 0;
	int a = 0;
	while(a<100){
		read (fd,&c,1);
		std::cout<<c;
		buf[a++]=c;
	}

}

void Motor::sendCommand(){
	
	
}

std::string getAlarm(int code){
}







