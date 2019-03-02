import seadrone.smart_thruster as thrusters
import threading
import time
import math

N_motors = 15
port = '/dev/ttyS3'

#TODO: Figure out how threads work lmao
#TODO: Also cut power via kill switch
#Have this alongside kill switch functions for extra redundancy

class Motor:
    m=""
    rpm=[N_motors]

    def __init__(self):
        print("Starting motors...")
        m = thrusters.start(N_motors, port)
        self.stopAll()
        print("Starting thread...")
        thread = threading.Thread(target=motor_feedback_thread, args=(m,))
        thread.daemon = True
        thread.start()
        return

    def __del__(self):
        self.stopAll()
        return

    def motor_feedback_thread(m):
        while m.running:
            print("\n\n\n\n") # empty lines for space
            for id in m.motors: # show feedback for each motor
                motor_feedback = 'Motor {:2d}: '.format(id)
                motor_feedback += "ON  " if m.is_on[id] else "OFF "
                motor_feedback += '{:5d}rpm '.format(m.rpm[id])
                motor_feedback += '{:5.2f}A '.format(m.current[id])
                motor_feedback += '{:5.2f}V '.format(m.voltage[id])
                motor_feedback += '{:5.2f}C '.format(m.driver_temperature[id])
                motor_feedback += 'Alarm: ' + m.get_alarm_description(id)
                print(motor_feedback)
                #TODO: Transfer motor_feedback through ethernet again so the Jetson can figure out what to do because I don't :   ^)
                if m.has_alarm[id]:
                    print("Auto-resetting motor alarm")
                    m.reset_alarm(id)
            time.sleep(0.05) # wait 50ms after each printout

    def run(self): #TODO: Unnecessary function
        try:
            while True:
                for id in m.motors:
                    #m.target_rpm[id] = int(amplitude*math.sin(2*math.pi*(id+1)*frequency*time.time()))
                    m.target_rpm[id] = self.rpm[id]
                time.sleep(0.01)
        except KeyboardInterrupt: # Program can be stopped pressing CTRL+C
            for id in m.motors:
                m.target_rpm[id] = 0
            print("Shutting down smart thruster library...")

    def setRPM(self,id,speed):
        m.target_rpm[id]=speed

    def stopAll(self):
        for id in range(N_motors):
            self.rpm[id]=0
            m.target_rpm[id]=0

if(__name__=="__main__"):
    m = Motor()
