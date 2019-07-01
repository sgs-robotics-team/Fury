#ifndef MOTOR_H
#define MOTOR_H

#include <string>

using std::string;

class Motor{

public:
	Motor();

private:

	class Values{
	public:
		Values();


	private:

		bool running;
		bool is_on;

		int motors;
		int has_alarm;
		int alarm_code;

		float rpm;
		float target_rpm;
		float current;
		float voltage;
		float driver_temperature;

	};

	//int checkLSB();
	//int checkMSB();

	int initializeInterface(int speed);
	void readMotor();
	void sendCommand();
	void setRPM(int id,int target_rpm);

	int fd;
	char buf[100];
};

#endif
