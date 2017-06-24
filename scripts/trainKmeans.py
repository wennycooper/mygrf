#! /usr/bin/env python

import rospy
import roslib
roslib.load_manifest('mygrf')
import tf
import numpy as np

USER_PREFIX = "/tracker/user_2/"

HEAD  = USER_PREFIX + "head"
NECK  = USER_PREFIX + "neck"
TORSO = USER_PREFIX + "torso"

LEFT_SHOULDER = USER_PREFIX + "left_shoulder"
LEFT_ELBOW = USER_PREFIX + "left_elbow"
LEFT_HAND = USER_PREFIX + "left_hand"

RIGHT_SHOULDER = USER_PREFIX + "right_shoulder"
RIGHT_ELBOW = USER_PREFIX + "right_elbow"
RIGHT_HAND = USER_PREFIX + "right_hand"

LEFT_HIP = USER_PREFIX + "left_hip"
LEFT_KNEE = USER_PREFIX + "left_knee"
LEFT_FOOT = USER_PREFIX + "left_foot"

RIGHT_HIP = USER_PREFIX + "right_hip"
RIGHT_KNEE = USER_PREFIX + "right_knee"
RIGHT_FOOT = USER_PREFIX + "right_foot"


if __name__ == '__main__':
    rospy.init_node('trainKmeans', anonymous=True)
    
    listener = tf.TransformListener()

    rate = rospy.Rate(30) # 30hz
    while not rospy.is_shutdown():
        now = rospy.Time.now()
        duration = rospy.Duration(1.0)
        
        listener.waitFormTransform(TORSO, RIGHT_HAND, now, duration)
        (trans, rot) = listener.loopupTransform(TORSO, RIGHT_HAND, now)
        
        print(trans)
        
        rate.sleep()

