#!/usr/bin/env python

import rospy
from custom_msg.msg import motor_speed

def motorSpeeds_node():
    rospy.init_node('motorSpeeds_node', anonymous=True)
    motorSpeeds = rospy.Publisher('motorSpeeds', motor_speed, queue_size=10)

    def ikCallBack(data):
        #this is so the arduino wont have issues with ros
        motorSpeeds.publish(data)
    
    rospy.Subscriber('ik', motor_speed, ikCallBack)
    rate = rospy.Rate(10) # 10hz

    while not rospy.is_shutdown():
        rate.sleep()

if __name__ == '__main__':
    try:
        motorSpeeds_node()
    except rospy.ROSInterruptException:
        pass
