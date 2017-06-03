#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

double grf_set1A(Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4);
double grf_set1B(Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4);
double grf_set2(Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4);

int main()
{
  Matrix3d m = Matrix3d::Random();
  m = (m + Matrix3d::Constant(1.2)) * 50;
  cout << "m =" << endl << m << endl;
  Vector3d v(1.1,2.2,3.3);
  
  cout << "m * v =" << endl << m * v << endl;

  cout << v(0) << endl << v(1) << endl << v(2) << endl;

  Vector3d u1(1.1, 2.2, 3.3);
  Vector3d v1(3.0, 2.0, 4.0);
  cout << "dot product: " << u1.dot(v1) << endl;
  cout << "cross product: " << u1.cross(v1) << endl;
  cout << "norm: " << u1.cross(v1).norm() << endl;

  Vector3d u2 = u1.cross(v1);
  cout << "normalize: " << u2.normalized() << endl;

  Vector3d p1(1, 0, 0);
  Vector3d p2(2, 0, 0.1);
  Vector3d p3(1, 0, 0);
  Vector3d p4(0, 0, 0);

  cout << "signed_distance: " << grf_set2(p1, p2, p3, p4) << endl;

}

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



