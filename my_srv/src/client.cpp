#include "ros/ros.h"
#include "my_srv/Velocity.h"
#include <cstdlib>
#include <ostream>
#include <string>

using namespace std;
char input;
	
int main(int argc, char **argv) {
	ros::init(argc, argv, "enter_a_string_client");	
	while (1){
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<my_srv::Velocity>("/velocity");
	my_srv::Velocity velocity_srv; 

	printf("Please enter u, d or any bottom to increase, decrease speed or reset robot postion respectively\n");
	cin>>input;

	velocity_srv.request.in = input; //gives the input by the user
	
	if (client.call(velocity_srv)) {
		cout<<"Velocity = "<< velocity_srv.response.x << endl;
		}
		
	else {
		ROS_ERROR("Failed to call service Velocity");
		return 1;
		}
	}
	return 0;
}
