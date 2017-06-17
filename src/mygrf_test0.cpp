#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <std_msgs/Float64.h>
#include <math.h>
#include <string>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

double grf_set1A(Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4);
double grf_set1B(Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4);
double grf_set2(Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4);


int main(int argc, char** argv){
  ros::init(argc, argv, "mygrf_test0");

  ros::NodeHandle node;
  ros::Publisher mygrf_test0_pub =  node.advertise<std_msgs::Float64>("/mygrf_test0/F1", 10);
  tf::TransformListener listener;
  ros::Rate rate(30.0);

  std::string USER_PREFIX = "/tracker/user_2/";

  double distance;
  
  while (node.ok()){
    ros::Time now = ros::Time::now();

    tf::StampedTransform transform_head;
    tf::StampedTransform transform_neck;
    tf::StampedTransform transform_torso;

    tf::StampedTransform transform_left_shoulder;
    tf::StampedTransform transform_left_elbow;
    tf::StampedTransform transform_left_hand;

    tf::StampedTransform transform_right_shoulder;
    tf::StampedTransform transform_right_elbow;
    tf::StampedTransform transform_right_hand;

    tf::StampedTransform transform_left_hip;
    tf::StampedTransform transform_left_knee;
    tf::StampedTransform transform_left_foot;

    tf::StampedTransform transform_right_hip;
    tf::StampedTransform transform_right_knee;
    tf::StampedTransform transform_right_foot;


    try {

      listener.waitForTransform( USER_PREFIX+"torso", USER_PREFIX+"head", now, ros::Duration(1.0) );
      listener.lookupTransform( USER_PREFIX+"torso", USER_PREFIX+"head", now, transform_head);

      listener.waitForTransform( USER_PREFIX+"torso", USER_PREFIX+"neck", now, ros::Duration(1.0) );
      listener.lookupTransform( USER_PREFIX+"torso", USER_PREFIX+"neck", now, transform_neck);

      listener.waitForTransform( USER_PREFIX+"torso", USER_PREFIX+"torso", now, ros::Duration(1.0) );
      listener.lookupTransform( USER_PREFIX+"torso", USER_PREFIX+"torso", now, transform_torso);

      listener.waitForTransform( USER_PREFIX+"torso", USER_PREFIX+"left_shoulder", now, ros::Duration(1.0) );
      listener.lookupTransform( USER_PREFIX+"torso", USER_PREFIX+"left_shoulder", now, transform_left_shoulder);

      listener.waitForTransform( USER_PREFIX+"torso", USER_PREFIX+"left_elbow", now, ros::Duration(1.0) );
      listener.lookupTransform( USER_PREFIX+"torso", USER_PREFIX+"left_elbow", now, transform_left_elbow);

      listener.waitForTransform( USER_PREFIX+"torso", USER_PREFIX+"left_hand", now, ros::Duration(1.0) );
      listener.lookupTransform( USER_PREFIX+"torso", USER_PREFIX+"left_hand", now, transform_left_hand);


      listener.waitForTransform( USER_PREFIX+"torso", USER_PREFIX+"right_shoulder", now, ros::Duration(1.0) );
      listener.lookupTransform( USER_PREFIX+"torso", USER_PREFIX+"right_shoulder", now, transform_right_shoulder);

      listener.waitForTransform( USER_PREFIX+"torso", USER_PREFIX+"right_elbow", now, ros::Duration(1.0) );
      listener.lookupTransform( USER_PREFIX+"torso", USER_PREFIX+"right_elbow", now, transform_right_elbow);

      listener.waitForTransform( USER_PREFIX+"torso", USER_PREFIX+"right_hand", now, ros::Duration(1.0) );
      listener.lookupTransform( USER_PREFIX+"torso", USER_PREFIX+"right_hand", now, transform_right_hand);

      listener.waitForTransform( USER_PREFIX+"torso", USER_PREFIX+"left_hip", now, ros::Duration(1.0) );
      listener.lookupTransform( USER_PREFIX+"torso", USER_PREFIX+"left_hip", now, transform_left_hip);

      listener.waitForTransform( USER_PREFIX+"torso", USER_PREFIX+"left_knee", now, ros::Duration(1.0) );
      listener.lookupTransform( USER_PREFIX+"torso", USER_PREFIX+"left_knee", now, transform_left_knee);

      listener.waitForTransform( USER_PREFIX+"torso", USER_PREFIX+"left_foot", now, ros::Duration(1.0) );
      listener.lookupTransform( USER_PREFIX+"torso", USER_PREFIX+"left_foot", now, transform_left_foot);

      listener.waitForTransform( USER_PREFIX+"torso", USER_PREFIX+"right_hip", now, ros::Duration(1.0) );
      listener.lookupTransform( USER_PREFIX+"torso", USER_PREFIX+"right_hip", now, transform_right_hip);

      listener.waitForTransform( USER_PREFIX+"torso", USER_PREFIX+"right_knee", now, ros::Duration(1.0) );
      listener.lookupTransform( USER_PREFIX+"torso", USER_PREFIX+"right_knee", now, transform_right_knee);

      listener.waitForTransform( USER_PREFIX+"torso", USER_PREFIX+"right_foot", now, ros::Duration(1.0) );
      listener.lookupTransform( USER_PREFIX+"torso", USER_PREFIX+"right_foot", now, transform_right_foot);

    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }

    geometry_msgs::PoseStamped head;
    head.header.frame_id = USER_PREFIX+"torso";
    head.header.stamp = now;
    head.pose.position.x = transform_head.getOrigin().x();
    head.pose.position.y = transform_head.getOrigin().y();
    head.pose.position.z = transform_head.getOrigin().z();
    Vector3d head_vec(transform_head.getOrigin().x(), transform_head.getOrigin().y(), transform_head.getOrigin().z());

    geometry_msgs::PoseStamped neck;
    neck.header.frame_id = USER_PREFIX+"torso";
    neck.header.stamp = now;
    neck.pose.position.x = transform_neck.getOrigin().x();
    neck.pose.position.y = transform_neck.getOrigin().y();
    neck.pose.position.z = transform_neck.getOrigin().z();
    Vector3d neck_vec(transform_neck.getOrigin().x(), transform_neck.getOrigin().y(), transform_neck.getOrigin().z());

    geometry_msgs::PoseStamped torso;
    torso.header.frame_id = USER_PREFIX+"torso";
    torso.header.stamp = now;
    torso.pose.position.x = transform_torso.getOrigin().x();
    torso.pose.position.y = transform_torso.getOrigin().y();
    torso.pose.position.z = transform_torso.getOrigin().z();
    Vector3d torso_vec(transform_torso.getOrigin().x(), transform_torso.getOrigin().y(), transform_torso.getOrigin().z());

    geometry_msgs::PoseStamped left_shoulder;
    left_shoulder.header.frame_id = USER_PREFIX+"torso";
    left_shoulder.header.stamp = now;
    left_shoulder.pose.position.x = transform_left_shoulder.getOrigin().x();
    left_shoulder.pose.position.y = transform_left_shoulder.getOrigin().y();
    left_shoulder.pose.position.z = transform_left_shoulder.getOrigin().z();
    Vector3d left_shoulder_vec(transform_left_shoulder.getOrigin().x(), transform_left_shoulder.getOrigin().y(), transform_left_shoulder.getOrigin().z());

    geometry_msgs::PoseStamped left_elbow;
    left_elbow.header.frame_id = USER_PREFIX+"torso";
    left_elbow.header.stamp = now;
    left_elbow.pose.position.x = transform_left_elbow.getOrigin().x();
    left_elbow.pose.position.y = transform_left_elbow.getOrigin().y();
    left_elbow.pose.position.z = transform_left_elbow.getOrigin().z();
    Vector3d left_elbow_vec(transform_left_elbow.getOrigin().x(), transform_left_elbow.getOrigin().y(), transform_left_elbow.getOrigin().z());

    geometry_msgs::PoseStamped left_hand;
    left_hand.header.frame_id = USER_PREFIX+"torso";
    left_hand.header.stamp = now;
    left_hand.pose.position.x = transform_left_hand.getOrigin().x();
    left_hand.pose.position.y = transform_left_hand.getOrigin().y();
    left_hand.pose.position.z = transform_left_hand.getOrigin().z();
    Vector3d left_hand_vec(transform_left_hand.getOrigin().x(), transform_left_hand.getOrigin().y(), transform_left_hand.getOrigin().z());

    geometry_msgs::PoseStamped right_shoulder;
    right_shoulder.header.frame_id = USER_PREFIX+"torso";
    right_shoulder.header.stamp = now;
    right_shoulder.pose.position.x = transform_right_shoulder.getOrigin().x();
    right_shoulder.pose.position.y = transform_right_shoulder.getOrigin().y();
    right_shoulder.pose.position.z = transform_right_shoulder.getOrigin().z();
    Vector3d right_shoulder_vec(transform_right_shoulder.getOrigin().x(), transform_right_shoulder.getOrigin().y(), transform_right_shoulder.getOrigin().z());

    geometry_msgs::PoseStamped right_elbow;
    right_elbow.header.frame_id = USER_PREFIX+"torso";
    right_elbow.header.stamp = now;
    right_elbow.pose.position.x = transform_right_elbow.getOrigin().x();
    right_elbow.pose.position.y = transform_right_elbow.getOrigin().y();
    right_elbow.pose.position.z = transform_right_elbow.getOrigin().z();
    Vector3d right_elbow_vec(transform_right_elbow.getOrigin().x(), transform_right_elbow.getOrigin().y(), transform_right_elbow.getOrigin().z());

    geometry_msgs::PoseStamped right_hand;
    right_hand.header.frame_id = USER_PREFIX+"torso";
    right_hand.header.stamp = now;
    right_hand.pose.position.x = transform_right_hand.getOrigin().x();
    right_hand.pose.position.y = transform_right_hand.getOrigin().y();
    right_hand.pose.position.z = transform_right_hand.getOrigin().z();
    Vector3d right_hand_vec(transform_right_hand.getOrigin().x(), transform_right_hand.getOrigin().y(), transform_right_hand.getOrigin().z());

    geometry_msgs::PoseStamped left_hip;
    left_hip.header.frame_id = USER_PREFIX+"torso";
    left_hip.header.stamp = now;
    left_hip.pose.position.x = transform_left_hip.getOrigin().x();
    left_hip.pose.position.y = transform_left_hip.getOrigin().y();
    left_hip.pose.position.z = transform_left_hip.getOrigin().z();
    Vector3d left_hip_vec(transform_left_hip.getOrigin().x(), transform_left_hip.getOrigin().y(), transform_left_hip.getOrigin().z());

    geometry_msgs::PoseStamped left_knee;
    left_knee.header.frame_id = USER_PREFIX+"torso";
    left_knee.header.stamp = now;
    left_knee.pose.position.x = transform_left_knee.getOrigin().x();
    left_knee.pose.position.y = transform_left_knee.getOrigin().y();
    left_knee.pose.position.z = transform_left_knee.getOrigin().z();
    Vector3d left_knee_vec(transform_left_knee.getOrigin().x(), transform_left_knee.getOrigin().y(), transform_left_knee.getOrigin().z());

    geometry_msgs::PoseStamped left_foot;
    left_foot.header.frame_id = USER_PREFIX+"torso";
    left_foot.header.stamp = now;
    left_foot.pose.position.x = transform_left_foot.getOrigin().x();
    left_foot.pose.position.y = transform_left_foot.getOrigin().y();
    left_foot.pose.position.z = transform_left_foot.getOrigin().z();
    Vector3d left_foot_vec(transform_left_foot.getOrigin().x(), transform_left_foot.getOrigin().y(), transform_left_foot.getOrigin().z());

    geometry_msgs::PoseStamped right_hip;
    right_hip.header.frame_id = USER_PREFIX+"torso";
    right_hip.header.stamp = now;
    right_hip.pose.position.x = transform_right_hip.getOrigin().x();
    right_hip.pose.position.y = transform_right_hip.getOrigin().y();
    right_hip.pose.position.z = transform_right_hip.getOrigin().z();
    Vector3d right_hip_vec(transform_right_hip.getOrigin().x(), transform_right_hip.getOrigin().y(), transform_right_hip.getOrigin().z());

    geometry_msgs::PoseStamped right_knee;
    right_knee.header.frame_id = USER_PREFIX+"torso";
    right_knee.header.stamp = now;
    right_knee.pose.position.x = transform_right_knee.getOrigin().x();
    right_knee.pose.position.y = transform_right_knee.getOrigin().y();
    right_knee.pose.position.z = transform_right_knee.getOrigin().z();
    Vector3d right_knee_vec(transform_right_knee.getOrigin().x(), transform_right_knee.getOrigin().y(), transform_right_knee.getOrigin().z());

    geometry_msgs::PoseStamped right_foot;
    right_foot.header.frame_id = USER_PREFIX+"torso";
    right_foot.header.stamp = now;
    right_foot.pose.position.x = transform_right_foot.getOrigin().x();
    right_foot.pose.position.y = transform_right_foot.getOrigin().y();
    right_foot.pose.position.z = transform_right_foot.getOrigin().z();
    Vector3d right_foot_vec(transform_right_foot.getOrigin().x(), transform_right_foot.getOrigin().y(), transform_right_foot.getOrigin().z());


//    mygrf_test0_pub.publish(right_hand);

/*
    distance = (double) sqrt(
	(right_hand.pose.position.x - right_elbow.pose.position.x) * (right_hand.pose.position.x - right_elbow.pose.position.x) +
        (right_hand.pose.position.y - right_elbow.pose.position.y) * (right_hand.pose.position.y - right_elbow.pose.position.y) +
        (right_hand.pose.position.z - right_elbow.pose.position.z) * (right_hand.pose.position.z - right_elbow.pose.position.z) 
    );

    printf("distance between R_Hand and R_Elbow is %f\n", (double) distance);

*/

    distance = grf_set1A(right_shoulder_vec, left_hip_vec, right_hip_vec, right_hand_vec); 
    
    std_msgs::Float64 distance_msg;
    distance_msg.data = distance;
    
//    printf("F1 is %f\n", (double) distance);
    mygrf_test0_pub.publish(distance_msg);

    rate.sleep();
  }
  return 0;
};
