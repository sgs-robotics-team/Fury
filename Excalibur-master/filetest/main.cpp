#include <iostream>
#include <fstream>

int main(){
	std::ofstream myfile;
	myfile.open("log.txt");
	myfile << "test\n";
	myfile.close();
	return 0;
}
