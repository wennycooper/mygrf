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

        try:

            listener.waitForTransform(TORSO, HEAD, now, duration)
            (head, rot) = listener.lookupTransform(TORSO, HEAD, now)
            listener.waitForTransform(TORSO, NECK, now, duration)
            (neck, rot) = listener.lookupTransform(TORSO, NECK, now)
            listener.waitForTransform(TORSO, TORSO, now, duration)
            (torso, rot) = listener.lookupTransform(TORSO, TORSO, now)

            listener.waitForTransform(TORSO, LEFT_SHOULDER, now, duration)
            (left_shoulder, rot) = listener.lookupTransform(TORSO, LEFT_SHOULDER, now)
            listener.waitForTransform(TORSO, LEFT_ELBOW, now, duration)
            (left_elbow, rot) = listener.lookupTransform(TORSO, LEFT_ELBOW, now)
            listener.waitForTransform(TORSO, LEFT_HAND, now, duration)
            (left_hand, rot) = listener.lookupTransform(TORSO, LEFT_HAND, now)

            listener.waitForTransform(TORSO, RIGHT_SHOULDER, now, duration)
            (right_shoulder, rot) = listener.lookupTransform(TORSO, RIGHT_SHOULDER, now)
            listener.waitForTransform(TORSO, RIGHT_ELBOW, now, duration)
            (right_elbow, rot) = listener.lookupTransform(TORSO, RIGHT_ELBOW, now)
            listener.waitForTransform(TORSO, RIGHT_HAND, now, duration)
            (right_hand, rot) = listener.lookupTransform(TORSO, RIGHT_HAND, now)

            listener.waitForTransform(TORSO, LEFT_HIP, now, duration)
            (left_hip, rot) = listener.lookupTransform(TORSO, LEFT_HIP, now)
            listener.waitForTransform(TORSO, LEFT_KNEE, now, duration)
            (left_knee, rot) = listener.lookupTransform(TORSO, LEFT_KNEE, now)
            listener.waitForTransform(TORSO, LEFT_FOOT, now, duration)
            (left_foot, rot) = listener.lookupTransform(TORSO, LEFT_FOOT, now)

            listener.waitForTransform(TORSO, RIGHT_HIP, now, duration)
            (right_hip, rot) = listener.lookupTransform(TORSO, RIGHT_HIP, now)
            listener.waitForTransform(TORSO, RIGHT_KNEE, now, duration)
            (right_knee, rot) = listener.lookupTransform(TORSO, RIGHT_KNEE, now)
            listener.waitForTransform(TORSO, RIGHT_FOOT, now, duration)
            (right_foot, rot) = listener.lookupTransform(TORSO, RIGHT_FOOT, now)

        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            continue
        
        print(right_hand)
        
        rate.sleep()

