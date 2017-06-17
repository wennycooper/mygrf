#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

double grf_set1A(Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4);
double grf_set1B(Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4);
double grf_set2(Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4);


double grf_set1A(Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4)
{
  Vector3d n = ((p1 - p3).cross(p2 - p3)).normalized();
  double  signed_distance = n.dot(p4 - p3);

  return signed_distance;
}

double grf_set1B(Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4)
{
  Vector3d n = (p2 - p1).normalized();
  
  double  signed_distance = n.dot(p4 - p3);

  return signed_distance;
}

double grf_set2(Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4)
{
  Vector3d n1 = (p2 - p1).normalized();
  Vector3d n2 = (p4 - p3).normalized();

  double  angle = acos(n1.dot(n2));

  return angle;
}



