from myGRF import grf_set1A
from myGRF import grf_set1B
from myGRF import grf_set2

import numpy as np

p1 = np.array([1, 0, 0])
p2 = np.array([-1, 0, -5])
p3 = np.array([1, 0, -5])
p4 = np.array([3, 2.5, 1.5])
print("grf_set1A: " , grf_set1A(p1, p2, p3, p4))


p1 = np.array([-1, 0, 0])
p2 = np.array([1, 0, 0])
p3 = np.array([0, 0, 1])
p4 = np.array([2.8, 2.9, 3.1])
print("grf_set1B: " , grf_set1B(p1, p2, p3, p4))

p1 = np.array([1, 0, 0])
p2 = np.array([2, 0, 0.1])
p3 = np.array([1, 0, 0])
p4 = np.array([0, 0, 0])
print("grf_set2: " , grf_set2(p1, p2, p3, p4))
