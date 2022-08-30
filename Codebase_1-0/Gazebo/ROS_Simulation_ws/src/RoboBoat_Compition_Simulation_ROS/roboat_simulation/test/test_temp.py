#!/usr/bin/env python
from __future__ import print_function

import roslib
import os
import sys
import unittest
import rospy
import rostest
from optparse import OptionParser
import numpy as np
import datetime
import time

# example msg imports
# from dse_msgs.msg import PoseMarkers
# from std_msgs.msg import Float64MultiArray
# from std_msgs.msg import MultiArrayLayout
# from std_msgs.msg import MultiArrayDimension
# from dse_msgs.msg import InfFilterPartials
# from dse_msgs.msg import InfFilterResults

from scipy.spatial.transform import Rotation as R
import copy

sys.path.append(os.path.join(sys.path[0], "../src"))

# example lib
# import dse_lib
# import consensus_lib

PKG = 'roboat_simulation'
roslib.load_manifest(PKG)

##############################################################################
##############################################################################
# Example class with test calls


# class TestInformationFilterCommon(unittest.TestCase):
    # ##############################################################################
    # ##############################################################################
    # # def set_up(self):
    # ##############################################################################
    # def __init__(self, *args):
        # ##############################################################################
        # # rospy.loginfo("-D- TestRangeFilter __init__")
        # # super(TestRangeFilterCommon, self).__init__(*args)
        # self.set_up()
        # super(TestInformationFilterCommon, self).__init__(*args)

    # ##############################################################################
    # def set_up(self):
        # ##############################################################################
        # rospy.init_node("test_observation_jacobian")
        # # self.coefficient = rospy.get_param("range_filter/coefficient", 266)
        # # self.exponent = rospy.get_param("range_filter/exponent", -1.31)
        # # self.rolling_pts = rospy.get_param("range_filter/rolling_pts", 4)
        # self.test_rate = rospy.get_param("~test_rate", 100)
        # self.results_sub = rospy.Subscriber("/tb3_0/dse/inf/results", InfFilterResults, self.estimator_results_callback)
        # self.inf_pub = rospy.Publisher("/tb3_0/dse/inf/partial", InfFilterPartials, queue_size=10)

        # # self.latest_filtered = 1e10
        # # self.latest_std = 2e10
        # self.dim_state = 6
        # self.dim_obs = 3
        # self.euler_order = 'zyx'
        # self.got_callback = False

    # ##############################################################################
    # def send_poses(self, poses, rate):
        # ##############################################################################
        # r = rospy.Rate(rate)
        # # rospy.loginfo("-D- sendmsgs: sending %s" % str(msgs))
        # for pose in poses:
            # rospy.loginfo("-D- publishing %d" % pose)
            # self.pose_pub.publish()
            # r.sleep()

    # # When the information filter sends back results, store them locally
    # def information_callback(self, data):
        # rospy.loginfo("-D- information_filter.py sent back data")
        # inf_id_list = data.ids
        # self.inf_Y_prior = dse_lib.multi_array_2d_output(data.inf_matrix_prior)
        # self.inf_y_prior = dse_lib.multi_array_2d_output(data.inf_vector_prior)
        # self.inf_I = dse_lib.multi_array_2d_output(data.obs_matrix)
        # self.inf_i = dse_lib.multi_array_2d_output(data.obs_vector)

    # # When the direct estimator or consensus returns the combined information variables
    # def estimator_results_callback(self, data):
        # rospy.loginfo("-D- information_filter.py sent back data")
        # self.inf_id_list = np.array(data.ids)
        # self.inf_Y = dse_lib.multi_array_2d_output(data.inf_matrix)
        # self.inf_y = dse_lib.multi_array_2d_output(data.inf_vector)
        # self.got_callback = True

# class TestInformationFilterValid(TestInformationFilterCommon):
    # ##############################################################################
    # ##############################################################################

    # ##############################################################################
    # def test_one_Equal_one(self):
        # ##############################################################################
        # rospy.loginfo("-D- test_one_Equal_one")
        # self.assertEqual(1, 1, "1!=1")

    # def test_theta_2_rotm_zero(self):
        # ##############################################################################
        # rospy.loginfo("-D- test_theta_2_rotm_0")
        # rotm = dse_lib.theta_2_rotm(0)
        # x_0 = np.transpose([1, 2])
        # x_rotm = rotm.dot(x_0)
        # x_true = x_0
        # self.assertEqual(True, np.allclose(x_true, x_rotm))

    # def test_theta_2_rotm_90(self):
        # ##############################################################################
        # rospy.loginfo("-D- test_theta_2_rotm_0")
        # theta = 90
        # rotm = dse_lib.theta_2_rotm(theta * np.pi / 180.0)
        # x_0 = np.transpose([1, 2])
        # x_rotm = rotm.dot(x_0)
        # x_true = np.transpose([-2, 1])
        # self.assertEqual(True, np.allclose(x_true, x_rotm))

    # def test_theta_2_rotm_45(self):
        # ##############################################################################
        # rospy.loginfo("-D- test_theta_2_rotm_0")
        # theta = 45
        # rotm = dse_lib.theta_2_rotm(theta * np.pi / 180.0)
        # x_0 = np.transpose([1, 1])
        # x_rotm = rotm.dot(x_0)
        # x_true = np.transpose([0, np.sqrt(2)])
        # self.assertEqual(True, np.allclose(x_true, x_rotm))

    # def test_to_frame_1(self):
        # ##############################################################################
        # rospy.loginfo("-D- test_from_frame_1")
        # agent1_global = np.array([[0], [0], [np.pi]])
        # agent2_global = np.array([[1], [0], [0]])
        # agent2_in_frame_agent1_true = np.array([[-1], [0], [np.pi]])
        # agent1_in_frame_agent2_true = np.array([[-1], [0], [np.pi]])

        # agent2_in_frame_agent1_est = dse_lib.agent2_to_frame_agent1_3D(agent1_global, agent2_global)
        # agent1_in_frame_agent2_est = dse_lib.agent2_to_frame_agent1_3D(agent2_global, agent1_global)

        # if agent2_in_frame_agent1_est[2, 0] < 0:
            # agent2_in_frame_agent1_est[2, 0] += 2*np.pi
        # if agent1_in_frame_agent2_est[2, 0] < 0:
            # agent1_in_frame_agent2_est[2, 0] += 2*np.pi

        # self.assertEqual(True, np.allclose(agent2_in_frame_agent1_true, agent2_in_frame_agent1_est))
        # self.assertEqual(True, np.allclose(agent1_in_frame_agent2_true, agent1_in_frame_agent2_est))

##############################################################################
##############################################################################

class tempTestInformation():
	hello = "nope"


if __name__ == '__main__':
    rospy.loginfo("-I- test_temp started")
    rospy.loginfo("-D- sys.argv: %s" % str(sys.argv))
    rostest.rosrun(PKG, 'test_temp_valid', tempTestInformation, sys.argv)
