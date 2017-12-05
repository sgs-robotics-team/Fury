#include "Compass.h"
#include <iostream>
#include <unistd.h>
int main(){
	Compass c;
	usleep(1000000);
	std::cout << c.getHeading() << " " << c.getPitch() << " " << c.getRoll() << std::endl;
}
