import numpy as np
from numpy import linalg as LA 

def grf_set1A(p1, p2, p3, p4):
    n = np.cross(p1 - p3, p2 - p3)
    n = n / LA.norm(n)
    signed_distance = np.dot(n, p4 - p3)

    return signed_distance


def grf_set1B(p1, p2, p3, p4):
    n = p2 - p1
    n = n / LA.norm(n)
    signed_distance = np.dot(n, p4 - p3)

    return signed_distance

def grf_set2(p1, p2, p3, p4):
    n1 = p2 - p1
    n1 = n1 / LA.norm(n1)
    n2 = p4 - p3
    n2 = n2 / LA.norm(n2)

    angle = np.arccos(np.dot(n1, n2))

    return angle

