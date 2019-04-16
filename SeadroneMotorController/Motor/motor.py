import smart_thruster as thrusters
import numpy as np

import threading,time,math,sys

MOTORS = 15
port = '/dev/ttyS3'

#TODO: Figure out how threads work lmao
#TODO: Also cut power via kill switch
#Have this alongside kill switch functions for extra redundancy

class Motor:
    m=""
    rpm=[0]*MOTORS

    def __init__(self):
        print("Starting motors...")
        self.m = thrusters.start(MOTORS, port)
        self.stopAll()
        print("Starting thread...")
        thread = threading.Thread(target=self.motor_feedback_thread, args=(self.m,))
        thread.daemon = True
        thread.start()
        return




    def test(self):
        print("test passed")



    def __del__(self):
        self.stopAll()
        return

    def motor_feedback_thread(self,m):
        while self.m.running:
            print("\n\n\n\n") # empty lines for space
            for id in self.m.motors: # show feedback for each motor
                motor_feedback = 'Motor {:2d}: '.format(id)
                motor_feedback += "ON  " if self.m.is_on[id] else "OFF "
                motor_feedback += '{:5d}rpm '.format(self.m.rpm[id])
                motor_feedback += '{:5.2f}A '.format(self.m.current[id])
                motor_feedback += '{:5.2f}V '.format(self.m.voltage[id])
                motor_feedback += '{:5.2f}C '.format(self.m.driver_temperature[id])
                motor_feedback += 'Alarm: ' + self.m.get_alarm_description(id)
                print(motor_feedback)
                #TODO: Transfer motor_feedback through ethernet again so the Jetson can figure out what to do because I don't :   ^)

                if self.m.has_alarm[id]:
                    print("Auto-resetting motor alarm")
                    m.reset_alarm(id)
            time.sleep(0.01) # wait 50ms after each printout

    def run_loop(self):
        try:
            while True:
                for id in self.m.motors:
                    self.m.target_rpm[id] = 500
                time.sleep(0.01)
        except KeyboardInterrupt: # Program can be stopped pressing CTRL+C
            for id in self.m.motors:
                self.m.target_rpm[id] = 0
            self.stop()
            print("Shutting down smart thruster library...")

    def setRPM(self,id,speed):
        self.m.target_rpm[id]=speed

    def setAllRPM(self,speed):
        for id in range(MOTORS):
            self.m.target_rpm[id]=speed

    def stopAll(self):
        for id in range(MOTORS):
            #print(id)
            #print(self.rpm)
            self.rpm[id]=0
            self.m.target_rpm[id]=0

    def stopAllSlow(self):
        temp = 0
        for id in range(MOTORS):
            temp = self.rpm[id]

            temp = temp/2

            self.rpm[id] = temp
            self.m.target_rpm[id] = temp
            time.sleep(0.1)
            self.rpm[id] = 0
            self.m.target_rpm[id] = 0

    def stop(self):
        self.stopAll()
        self.m.stop()

    def getVoltage(self,id): return self.m.voltage[id]
    def getTemp(self,id): return self.m.driver_temperature[id]
    def getCurrent(self,id): return self.m.current[id]
    def getRpm(self,id): return self.m.rpm[id]

def sig_handler(signum, frame):
    print(signum)
    return None

if(__name__=="__main__"):
    signal.signal(signal.SIGSEGV, sig_handler)
    mo = Motor()
    mo.setRPM(1,500)
    mo.run_loop()
    mo.stop()
