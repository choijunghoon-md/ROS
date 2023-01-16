 #include "ros/ros.h"
 #include "std_msgs/Int8.h"
 #include "std_msgs/Bool.h"
 #include "std_msgs/String.h"
 #include "sensor_msgs/Range.h"
 #include "geometry_msgs/Twist.h"
 
 
 std_msgs::Bool flag_AEB;
 
 geometry_msgs::Twist cmd_vel_msg;
 
 void UltraSonarCallback(const sensor_msgs::Range::ConstPtr&msg)
 {
	 ROS_INFO("Sonar Seq: [%d]",msg->header.seq);
	 ROS_INFO("Sonar Range: [%f]",msg->range);
	 
	 if(msg->range <= 1.8){
		 ROS_INFO("AEB_Activation!");
		 flag_AEB.data = true;
		 }
	else{
		flag_AEB.data = false;
		}
	 
	 }
 void CarControllback(const gometry_msgs::Twist& msg){\
	 ROS_INFO("Cmd vel : linear_x [%f]",msg.linear.x);
	 //printf("tset");
	 cmd_vel_msg = msg;
	 ROS_INFO("Cmd vel : linear_x [%f]",cmd_vel_msg.linear.x)
	 }
 
 void UltraSonarCallback2(const sensor_msgs::Range::ConstPtr& msg){
	 ROS_INFO("Sonar2 Seq: [%d]",msg->header.seq);
	 ROS_INFO("Sonar2 Range: [%f]",msg->range);
	 }
 
 
 int main(int argc, char **argv){
	 
	 int count = 0;
	 
	 ros::init(argc,argv,"aeb_controller");
	 
	 ros::NodeHandle n;
	 
	 ros::Subscriber sub=n.subscribe("range",1000,UltraSonarCallback);
	 ros::Subscriber sonar_sub = n.subscribe("RangeSonar1",1000,UltraSonarCallback2);
	 ros::Subscriber cmd_vel_sub = n.subscribe("/cmd_vel",1000,&CarControllback);
	 
	 ros:publisher pub_cmd vel = n.advertise<geometry_msg::Twist>("/ackermann_steering_controller/cmd_vel",10);
	 ros:publisher pub_aeb_activation_flag=n.advertise<std_msg::Bool>("/aeb_activation_flag",1);  
	 
	 ros::Rate loop_rate(10);// 10
	 
	 while(ros::ok()){
		 if((count%2)==0){
			 pub_aeb_activation/-flag.publish(flag_AEB);
			 }
		
	     if(flage_AEB == true){
			 cmd_vel_msg.linear.x = 0;
			 pub_cmd_vel.publish(cmd_vel_msg);
			 }
	     else{
			 pub_cmd_vel.publish(cmd_vel_msg);
			 }
		 loop_rate.sleep();
		 ros::spinOnce();
		 ++count;
		 }
		 
	 return 0;
	 }
