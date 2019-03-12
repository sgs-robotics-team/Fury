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
    rpm=[0]*N_motors

    def __init__(self):
        print("Starting motors...")
        self.m = thrusters.start(N_motors, port)
        self.stopAll()
        print("Starting thread...")
        thread = threading.Thread(target=self.motor_feedback_thread, args=(self.m,))
        thread.daemon = True
        thread.start()
        return

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
                #print(motor_feedback)
                #TODO: Transfer motor_feedback through ethernet again so the Jetson can figure out what to do because I don't :   ^)
                if self.m.has_alarm[id]:
                    print("Auto-resetting motor alarm")
                    m.reset_alarm(id)
            time.sleep(0.05) # wait 50ms after each printout

    def run(self): #TODO: Unnecessary function
        try:
            while True:
                for id in self.m.motors:
                    #self.m.target_rpm[id] = int(amplitude*math.sin(2*math.pi*(id+1)*frequency*time.time()))
                    #print(id)
                    self.m.target_rpm[id] = 100#self.rpm[id]
                time.sleep(0.01)
        except KeyboardInterrupt: # Program can be stopped pressing CTRL+C
            for id in self.m.motors:
                self.m.target_rpm[id] = 0
            print("Shutting down smart thruster library...")

    def setRPM(self,id,speed):
        self.m.target_rpm[id]=speed

    def stopAll(self):
        for id in range(N_motors):
            #print(id)
            #print(self.rpm)
            self.rpm[id]=0
            self.m.target_rpm[id]=0

    def stop(self):
        self.stopAll()
        self.m.stop()

    def getVoltage(self,id):
        return self.m.voltage[id]

    def getTemp(self,id):
        return self.m.driver_temperature[id]

    def getCurrent(self,id):
        return self.m.current[id]

    def getRpm(self,id):
        return self.m.rpm[id]

if(__name__=="__main__"):
    mo = Motor()
    print(mo.getRpm(1))
    print(mo.getCurrent(1))
    print(mo.getVoltage(1))
    print(mo.getTemp(1))
    mo.setRPM(1,500)
    while True:
        mo.run()
    m
