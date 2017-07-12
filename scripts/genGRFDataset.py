#! /usr/bin/env python

import rospy
import roslib
roslib.load_manifest('mygrf')
import tf
import numpy as np
import pickle
from myGRF import grf_set1A
from myGRF import grf_set1B
from myGRF import grf_set2

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

NORM_FACTOR = 0.3

grfDataset = np.array([])


def myhook():
    # CTRL+C will come to here
    pickle.dump(grfDataset, open( "grfDataset_hello", "wb" ))
    print("dataset dump completed!")
    

if __name__ == '__main__':
    rospy.init_node('genGRFDataset', anonymous=True)

    rospy.on_shutdown(myhook)
    
    listener = tf.TransformListener()
    firstFlag = 1;

    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        now = rospy.Time.now()
        duration = rospy.Duration(10.0)

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

        except:
#            print("got exception!!")
#            print(grfDataset.shape)
#            pickle.dump(grfDataset, open( "grfDataset_walking", "wb" ))
#            print("dataset dump completed!! please press CTRL-C")
            continue

        head_vec = np.array([head[0], head[1], head[2]])
        neck_vec = np.array([neck[0], neck[1], neck[2]])
        torso_vec = np.array([torso[0], torso[1], torso[2]])

        left_shoulder_vec = np.array([left_shoulder[0], left_shoulder[1], left_shoulder[2]])
        left_elbow_vec = np.array([left_elbow[0], left_elbow[1], left_elbow[2]])
        left_hand_vec = np.array([left_hand[0], left_hand[1], left_hand[2]])

        right_shoulder_vec = np.array([right_shoulder[0], right_shoulder[1], right_shoulder[2]])
        right_elbow_vec = np.array([right_elbow[0], right_elbow[1], right_elbow[2]])
        right_hand_vec = np.array([right_hand[0], right_hand[1], right_hand[2]])

        left_hip_vec = np.array([left_hip[0], left_hip[1], left_hip[2]])
        left_knee_vec = np.array([left_knee[0], left_knee[1], left_knee[2]])
        left_foot_vec = np.array([left_foot[0], left_foot[1], left_foot[2]])

        right_hip_vec = np.array([right_hip[0], right_hip[1], right_hip[2]])
        right_knee_vec = np.array([right_knee[0], right_knee[1], right_knee[2]])
        right_foot_vec = np.array([right_foot[0], right_foot[1], right_foot[2]])

        
        F1 = grf_set1A(right_shoulder_vec, left_hip_vec, right_hip_vec, right_hand_vec) / NORM_FACTOR
        F2 = grf_set1A(left_shoulder_vec, right_hip_vec, left_hip_vec, left_hand_vec) / NORM_FACTOR
        F3 = grf_set1A(left_shoulder_vec, right_shoulder_vec, right_hip_vec, right_foot_vec) / NORM_FACTOR
        F4 = grf_set1A(right_shoulder_vec, left_shoulder_vec, left_hip_vec, left_foot_vec) / NORM_FACTOR

        F5 = grf_set1B(left_shoulder_vec, right_shoulder_vec, head_vec, right_hand_vec) / NORM_FACTOR
        F6 = grf_set1B(left_shoulder_vec, right_shoulder_vec, head_vec, left_hand_vec) / NORM_FACTOR

        F7 = grf_set2(right_elbow_vec, right_hand_vec, right_elbow_vec, right_shoulder_vec)
        F8 = grf_set2(left_elbow_vec, left_hand_vec, left_elbow_vec, left_shoulder_vec)
        F9 = grf_set2(right_knee_vec, right_foot_vec, right_knee_vec, right_hip_vec)
        F10 = grf_set2(left_knee_vec, left_foot_vec, left_knee_vec, left_hip_vec)

#        print(right_hand)
#        print([[F1, F2, F3, F4, F5, F6, F7, F8, F9, F10]])
        
        i10D = np.array([F1, F2, F3, F4, F5, F6, F7, F8, F9, F10])
        if firstFlag == 1:
            grfDataset = i10D
            firstFlag = 0
        else:
            grfDataset = np.vstack((grfDataset, i10D))
            print(grfDataset.shape[0])
            #if grfDataset.shape[0] >= 1990:
            #    pickle.dump(grfDataset, open( "grfDataset_walking", "wb" ))
            #    print("dataset dump completed! Please press CTRL-C.")
        
        rate.sleep()

