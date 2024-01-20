#!/usr/bin/env python

import rospy
from custom_msg.msg import heading
from custom_msg.msg import motor_speed
import numpy as np


MAX_MOTOR_SPEED = 1900
MIN_MOTOR_SPEED = 1100
MOTOR_STOP = 1500
MAX_SPEED_PRECENT = 0.6
MAX_TURN_SPEED_PRECENT = 0.3


def ik_node():
    rospy.init_node('ik_node', anonymous=True)
    ik_out = rospy.Publisher('ik', motor_speed, queue_size=10)

    SPEED_RANGE = (MAX_MOTOR_SPEED - MIN_MOTOR_SPEED) / 2 

    MAX_SPEED = SPEED_RANGE * MAX_SPEED_PRECENT
    MAX_TURN_SPEED = SPEED_RANGE * MAX_TURN_SPEED_PRECENT

    def headingCallBack(data):
        speed = data.Speed #PRECENT <FLOAT32>
        angle = data.Theta #ANGLE IN RAD <FLOAT32>
 
        if speed > 100.0:
            speed = 100.0
        elif speed < -100.0:
            speed = -100.0

        angle = np.radians(angle) #TODO: remove, used for testing
        PI = np.pi
        if angle > PI:
            angle = PI
        elif angle < -PI:
            angle = -PI

        f_speed = np.interp(speed,[-100.0, 100.0],[-MAX_SPEED, MAX_SPEED])


        angle_right_speed = MAX_TURN_SPEED*np.sin(angle)
        angle_left_speed = -angle_right_speed


        ik_speed_msg = motor_speed()
        ik_speed_msg.leftMotor = int(MOTOR_STOP + f_speed + angle_left_speed)
        ik_speed_msg.rightMotor = int(MOTOR_STOP + f_speed + angle_right_speed)
        ik_out.publish(ik_speed_msg)


    rospy.Subscriber('heading', heading, headingCallBack)
    rate = rospy.Rate(10) # 10hz

    while not rospy.is_shutdown():
        rate.sleep()

if __name__ == '__main__':
    try:
        ik_node()
    except rospy.ROSInterruptException:
        pass