#!/usr/bin/env python

import rospy
from custom_msg.msg import heading
from custom_msg.msg import radio
from std_msgs.msg import Bool
from numpy import interp

MAX_HEADING_SPEED = 100
MIN_HEADING_SPEED = 0
HEADING_SPEED_RANGE = [MIN_HEADING_SPEED, MAX_HEADING_SPEED]

MAX_HEADING_THETA = 180
MIN_HEADING_THETA = -180
HEADING_THETA_RANGE = [MIN_HEADING_THETA, MAX_HEADING_THETA]

#Throttle (experimental data depends on controler setup)
MAX_THROTTLE_VALUE = 1910
MIN_THROTTLE_VALUE = 1070
THROTTLE_RANGE = [MIN_THROTTLE_VALUE, MAX_THROTTLE_VALUE]

#AILERON (experimental data depends on controler setup)
MAX_AILERON_VALUE = 1910
MIN_AILERON_VALUE = 1070
AILERON_RANGE = [MIN_AILERON_VALUE, MAX_AILERON_VALUE]

class radioControler_handeler:

    def __init__(self):
        rospy.init_node('radio_controler_node', anonymous=True)

        self.heading_topic = rospy.Publisher('heading', heading, queue_size=10)
        
        rospy.Subscriber('radio', radio, self.radioControlerCallBack)
        rospy.Subscriber('soft_kill', Bool, self.softKillCallBack)
        self.rate = rospy.Rate(10) # 10hz

        self.FORWARD = True
        self.BACKWARD = False
        self.motorDirection = self.FORWARD
        self.autoState = False
        self.killState = True
        self.soft_kill = True
    
    def softKillCallBack(self, val):
        self.soft_kill = val.data

    def radioControlerCallBack(self, data):
        #kill state
        if not data.RadioConection or data.Gear or self.soft_kill:
            #CALSES THIS WILL RUN
            #1) FLAP LEVER (KILL) IS 1 (ON)
            #2) NO RADIO CONECTION Throttle BELOW THROTTLE_KILL_VALUE
            #3) RADIO NOT INITIILZED (FIRST CONECTION) ALL RADIO VALULES AT 0
            pass #currently everything handled in arduino
        else:
            #nothing on (motors forward auto off)
            if not data.ElevdD_R and not data.Flap:
                self.autoState = False
                self.motorDirection = self.FORWARD
            #FLAP ON (auto on)
            elif data.Flap: 
                self.autoState = True
                
            #ELEV D/R ON (motors backward auto off)
            elif data.ElevdD_R: 
                self.autoState = False
                self.motorDirection = self.BACKWARD
                
            #Unreachable
            else:
                rospy.logfatal("radio state Unreachable" + str(int(data.Gear)))
                return
                
            if (not self.autoState):
                heading_msg = heading()
                
                if (self.motorDirection == self.FORWARD):
                    heading_msg.Speed = int(interp(data.Throttle, THROTTLE_RANGE, HEADING_SPEED_RANGE))
                    heading_msg.Theta = int(interp(data.Aileron, AILERON_RANGE, HEADING_THETA_RANGE))
                else: #motorDirection == BACKWARD
                    heading_msg.Speed = -int(interp(data.Throttle, THROTTLE_RANGE, HEADING_SPEED_RANGE))
                    heading_msg.Theta = int(interp(data.Aileron, AILERON_RANGE, HEADING_THETA_RANGE)) #DO I NEED TO MAKE THIS NEGATIVE?
                    
                self.heading_topic.publish(heading_msg)
            else:
                #TODO: IMPLEMET AUTO CODE
                #\/ Remove later
                heading_msg = heading()
                heading_msg.Speed = 0
                heading_msg.Theta = 0
                self.heading_topic.publish(heading_msg)
                #TODO: ros publish auto state true

    def run(self):
        while not rospy.is_shutdown():
            self.rate.sleep()


if __name__ == '__main__':
    handeler = radioControler_handeler()
    try:
        handeler.run()
    except rospy.ROSInterruptException:
        pass