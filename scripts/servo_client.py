#!/usr/bin/env python
import numpy as np
import math
import rospy
from std_msgs.msg import Float32MultiArray

class ServoClient:
    def __init__(self, min_angle, rate):
        self.min_angle = min_angle
        self.array = np.array([90.0, 89.0, 87.0, 90.0])
        self.pub = rospy.Publisher("test", Float32MultiArray, queue_size = 1)
        self.rate = rospy.Rate(rate)

    def send_angle(self, target_angle):
        target_array = np.array(target_angle)
        max_diff = np.max(np.abs(target_array - self.array))
        div_num = int(math.ceil(max_diff/self.min_angle))
        angle_list = self.interpolation(self.array, target_array, div_num)
        for segment_angle in angle_list:
            msg = Float32MultiArray(data = segment_angle)
            self.pub.publish(msg)
            self.rate.sleep()
        self.array = np.array(angle_list[-1])

    def interpolation(self, initial, target, div_num):
        ret = np.zeros((div_num, initial.size))
        for i in range(initial.size):
            for j in range(div_num): 
                ret[j][i] = math.ceil(initial[i]+(target[i]-initial[i])/div_num * (j+1))
        return ret.tolist()

