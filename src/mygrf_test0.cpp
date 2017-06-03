#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PoseStamped.h>
#include <math.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "mygrf_test0");

  ros::NodeHandle node;
  ros::Publisher mygrf_test0_pub =  node.advertise<geometry_msgs::PoseStamped>("/mygrf_test0/right_hand", 10);
  tf::TransformListener listener;
  ros::Rate rate(10.0);

  double distance;
  
  while (node.ok()){
    ros::Time now = ros::Time::now();

    tf::StampedTransform transformRightHand;
    tf::StampedTransform transformRightElbow;
//    try{
//      listener.lookupTransform("/tracker/user_1/torso", "/tracker/user_1/right_hand",  
//                               now, transform);
//    }

    try {
      listener.waitForTransform("/tracker/user_2/torso", "/tracker/user_2/right_hand", now, ros::Duration(10.0) );
      listener.lookupTransform( "/tracker/user_2/torso", "/tracker/user_2/right_hand", now, transformRightHand);

      listener.waitForTransform("/tracker/user_2/torso", "/tracker/user_2/right_elbow", now, ros::Duration(10.0) );
      listener.lookupTransform( "/tracker/user_2/torso", "/tracker/user_2/right_elbow", now, transformRightElbow);


    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }

    geometry_msgs::PoseStamped right_hand;
    right_hand.header.frame_id = "/tracker/user_2/torso";
    right_hand.header.stamp = now;
    right_hand.pose.position.x = transformRightHand.getOrigin().x();
    right_hand.pose.position.y = transformRightHand.getOrigin().y();
    right_hand.pose.position.z = transformRightHand.getOrigin().z();
    right_hand.pose.orientation.x = transformRightHand.getRotation().x();
    right_hand.pose.orientation.y = transformRightHand.getRotation().y();
    right_hand.pose.orientation.z = transformRightHand.getRotation().z();
    right_hand.pose.orientation.w = transformRightHand.getRotation().w();

    geometry_msgs::PoseStamped right_elbow;
    right_elbow.header.frame_id = "/tracker/user_2/torso";
    right_elbow.header.stamp = now;
    right_elbow.pose.position.x = transformRightElbow.getOrigin().x();
    right_elbow.pose.position.y = transformRightElbow.getOrigin().y();
    right_elbow.pose.position.z = transformRightElbow.getOrigin().z();
    right_elbow.pose.orientation.x = transformRightElbow.getRotation().x();
    right_elbow.pose.orientation.y = transformRightElbow.getRotation().y();
    right_elbow.pose.orientation.z = transformRightElbow.getRotation().z();
    right_elbow.pose.orientation.w = transformRightElbow.getRotation().w();

//    mygrf_test0_pub.publish(right_hand);

    distance = (double) sqrt(
	(right_hand.pose.position.x - right_elbow.pose.position.x) * (right_hand.pose.position.x - right_elbow.pose.position.x) +
        (right_hand.pose.position.y - right_elbow.pose.position.y) * (right_hand.pose.position.y - right_elbow.pose.position.y) +
        (right_hand.pose.position.z - right_elbow.pose.position.z) * (right_hand.pose.position.z - right_elbow.pose.position.z) 
    );

    printf("distance between R_Hand and R_Elbow is %f\n", (double) distance);



    rate.sleep();
  }
  return 0;
};
