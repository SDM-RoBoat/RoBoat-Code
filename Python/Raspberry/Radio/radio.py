from enum import Enum
import RPi.GPIO as GPIO
import time

class radio:
    low = 1000
    zero = 1400
    high = 1800
    scale = 255
    input_setup

    class ports(Enum):
        Throttle = 1
        Aileron = 2
        Elevator = 3
        Rudder = 4
        Gear = 5
        AUX1 = 6
        scale = 255

    def __init__(self):

    #internal function
    def pulseIn(self, pin):
        start_time = time()
        while not GPIO.input(pin):
            start_time = time()
        while GPIO.input(pin):
            end_time = time()
        return end_time - start_time

    #internal function
    def map (self, num, low_in, high_in, low_out, high_out):
        return num * (high_out - low_out) / (high_in - low_in)

    #used to set ports
    def set(self, channel, pin):
        GPIO.setup(pin, GPIO.IN)
        self.input_setup[channel] = pin

    #used to read channels
    def read (self, channel):
        if channel == self.ports.Throttle:
           return self.readThrottle(self.input_setup[channel])
        elif channel < self.ports.Gear:
            return self.readJoystick(self.input_setup[channel])
        else:
            return self.readSwitch(self.input_setup[channel])

    #internal function
    def readThrottle(self, pin):
        duration = self.pulseIn(pin)
        output = self.map(duration, 973, 1915, 0, self.scale)
        if output > scale:
            return scale
        return output

    #internal function
    def readJoystick(self, pin):
        duration = self.pulseIn(pin)
        output = self.map(duration, 973, 1915, 0, self.scale)
        return  output

    #internal function
    def readSwitch(self, pin):
        output = self.pulseIn(pin)

        if abs(output - self.low) < 100:
            return 2
        elif abs(output - self.zero) < 100:
            return 1
        elif abs(output - self.high) < 100:
            return 0
        else:
            return -256