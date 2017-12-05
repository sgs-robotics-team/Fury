#include <roboard.h>
#include <iostream>
int main(){
	if (io_init()){
		if(rcservo_Initialize(RCSERVO_USECHANNEL0)){
			rcservo_EnterPWMMode();
			unsigned long PWM_period = 20000;
			unsigned long PWM_duty = 1000;
			unsigned long count = 100;
			rcservo_SendPWMPulses(RCSERVO_USECHANNEL0, PWM_period, PWM_duty, count);
			while (!rcservo_IsPWMCompleted(RCSERVO_USECHANNEL0)){
				std::cout << "duty: " << ((float)PWM_duty)/PWM_period << std::endl;
			}
			PWM_duty = 2000;
			rcservo_SendPWMPulses(RCSERVO_USECHANNEL0, PWM_period, PWM_duty, count);
			while (!rcservo_IsPWMCompleted(RCSERVO_USECHANNEL0)){
				std::cout << "duty: " << ((float)PWM_duty)/PWM_period << std::endl;
			}
			PWM_duty = 6000;
			rcservo_SendPWMPulses(RCSERVO_USECHANNEL0, PWM_period, PWM_duty, count);
			while (!rcservo_IsPWMCompleted(RCSERVO_USECHANNEL0)){
				std::cout << "duty: " << ((float)PWM_duty)/PWM_period << std::endl;
			}

			rcservo_Close();
		}
		io_close();
	}
}