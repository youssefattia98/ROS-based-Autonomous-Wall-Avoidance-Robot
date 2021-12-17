#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "my_srv/Velocity.h"
#include "std_srvs/Empty.h"
#include <string>
float Leftdis, Frontdist,Rightdist;
ros::Subscriber sub;
ros::Publisher pub;
ros::ServiceClient client1;
float speed=0.5;
float ang=1.5;



bool my_new_vel (my_srv::Velocity::Request &req, my_srv::Velocity::Response &res){

		my_srv::Velocity velocity_srv;
		if (req.in == "u" && speed<1){
			res.x = speed + 0.1*speed;
			speed=res.x;
			if (speed>1){
			res.x = 1;
			speed=res.x;
			}
		}
		else if (req.in == "d" && speed>0){
			res.x = speed - 0.1*speed;
			speed=res.x;
		}
		else {
			res.x = 0.1;
			speed=res.x;
			ros::NodeHandle nh;
			ros::ServiceClient client1 = nh.serviceClient<std_srvs::Empty>("/reset_positions");
			std_srvs::Empty srv1;
			client1.waitForExistence();
			client1.call(srv1);
		}
		return res.x;
}

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg){
	/*
    for(int i=145;i<576;i++){

        if(i>=145 && i<=288){//range of the right
            if (Rightdist > msg-> ranges[i]){
            	Rightdist = msg-> ranges[i];
            }
        }

        else if (i>288 && i<=432){//range of left
            if (Frontdist > msg-> ranges[i]){
                Frontdist = msg-> ranges[i];
                }
        }

        else if (i>432 && i<=576){//range of left
            if (Leftdis > msg-> ranges[i]){
                Leftdis = msg-> ranges[i];
                }
        }
    }*/

	Rightdist = msg-> ranges[288];
	Frontdist = msg-> ranges[360];
	Leftdis = msg-> ranges[576];
    printf("the min right:%f\n",Rightdist);
    printf("the min front:%f\n",Frontdist);
    printf("the min left:%f\n",Leftdis);

	geometry_msgs::Twist my_vel;
	//my_srv::Speed speed_srv;
	//speed=speed_srv.response.x;
	my_vel.linear.x = speed;
	my_vel.angular.z = 0.0;

	if(Frontdist>1 &&  Leftdis>1 && Rightdist>1){
		//should go straight
		printf("i should go straight\n");
		my_vel.linear.x = 2*speed;
		my_vel.angular.z = 0;
	}
	
	else if ((Leftdis>1 && Frontdist>1 && Rightdist<1)||(Leftdis<1 && Frontdist>1  && Rightdist<1)){
		//should go left
		printf("i should go left\n");
		my_vel.linear.x = speed;
		my_vel.angular.z = ang;
	}

	else if ((Leftdis>1 && Frontdist<1 && Rightdist>1)||(Leftdis<1 && Frontdist<1 && Rightdist>1)){
		//should go right
		printf("i should go right\n");
		my_vel.linear.x = speed;
		my_vel.angular.z = -ang;
	}

	else if ((Leftdis<1 && Frontdist>1 && Rightdist>1)||(Leftdis>1 && Frontdist<1 && Rightdist<1)||(Leftdis<1 && Frontdist<1 && Rightdist<1)){
		//should check nearest
		printf("checking nearest...\n");
		if(Leftdis>Rightdist){ //left is far, turn left
			printf("i should go left\n");
			my_vel.linear.x = speed;
			my_vel.angular.z = ang;
		}
		else if(Leftdis<Rightdist){//right is far, turn right
			printf("i should go right\n");
			my_vel.linear.x = speed;
			my_vel.angular.z = -ang;
		}
	}
	
	pub.publish(my_vel);
}
	
	
int main (int argc, char **argv){
	ros::init(argc, argv, "turtlebot_subscriber");
	ros::NodeHandle nh;
	ros::NodeHandle n;
	ros::ServiceServer service= n.advertiseService("/velocity", my_new_vel);
	pub = nh.advertise<geometry_msgs::Twist> ("/cmd_vel", 1);
	ros::Subscriber sub = nh.subscribe("/base_scan", 1,laserCallback);
	
	ros::ServiceClient client1 = nh.serviceClient<std_srvs::Empty>("/reset_positions");
	std_srvs::Empty srv1;
 	client1.waitForExistence();
	client1.call(srv1);
	
	
	ros::spin();
	return 0;
}