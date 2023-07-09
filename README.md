# ROS-based Autonomous Wall-Avoidance Robot description:
The project consists of a simulation in which a robot should complete a track without colliding in the walls using ROS and Cpp as the programming language.
This repo consists of the following points:  
 1)How to Setup the Simulator.  
 2)How to use the Simulator.  
 3)Algorithm used to solve the problem, truth table and flowchart.  
 4)Final output.  
 5)Possible improvements.  

1)How to Setup the Simulator.  
================================

Installing and running
----------------------

The simulator requires specific ROS version and I recommend using the Docker image dedicated to this course to make installation and running easier. After cloning the repo to the ROS work space the following commands should be used in the workspace directory to install.

```bash
$ sudo roscore
$ sudo catkin_make
```

2)How to use the Simulator.  
================================
Once the everything is compiled, get inside the directory on the shell. To run the simulation, run the commands in separate terminals:

```bash
$ rosrun stage_ros stageros $(rospack find second_assignment)/world/my_world.world
$ rosrun assignment2 controller_node 
$ rosrun my_srv clinet
```

Or, run two bash files on two different terminals to compile and run the simulator along with the controller and the client node.

```bash
$ bash ass2.sh
$ bash ass2.2.sh
```

### Motion ###

The Controller can publish both linear and angular speed for the robot to control its motion in the simulation

```cpp
my_vel.linear.x = speed;
my_vel.angular.z = ang;
```
The Value of the speed is changed though the client node in which the user can increase the speed or decrease it according to his interest, note that the is a limit of the speed to avoid collision.


### Vision ###

The simulation send messages regarding the sensors feedback in which the front view of the robot has a range from 720 to 0 as in 180 degrees to 0 degrees.

For example, the following code prints out the values of all the sensors feedback of the robot:

```cpp
void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg){
    float dist;
    for(int i=0;i<720;i++){
    dist = msg-> ranges[i];
    printf("The distance: %f for the range: %d.\n",dist,i);
    }
```


3)Algorithm used to solve the problem and flowchart. 
================================
There are plenty of Algorithms that can be used to solve this problem which I have tried more than one algorithm.
However, the most efficient algorithm by far is used in the solution, in which the robot turns according to his distance with the right wall and left wall same as autonomous cars algorithm to follow a lane. This will be explained more further down below, in the meantime the most challenging part of the script is how the robot decides which direction it should turn.  

Truth table & Flowchart
---------

![immagine](https://github.com/youssefattia98/Research-Track-Assignment-2/blob/main/Left%20distance-1.jpg)  

The above Flowchart describes more details the communication between the ROS nodes and how data is transferred. Note that, the client can control the speed of the robot to a certain limit to assure that the robot will never crash and if the user chooses to increase the speed more than this limits the simulation will reset with minimum speed. Also, if the user input any wrong input, then that he should the simulation will reset the robot’s position and speed.

```cpp
if(Frontdist>1 &&  Leftdis>1 && Rightdist>1){
		//should go straight
		printf("i should go straight\n");
		my_vel.linear.x = 2*speed;
		my_vel.angular.z = 0;
	
	}
	else if ((Frontdist>1 &&  Leftdis>1 && Rightdist<1)||(Frontdist>1 &&  Leftdis<1 && Rightdist<1)){
		//should go left
		printf("i should go left\n");
		my_vel.linear.x = speed;
		my_vel.angular.z = ang;
	}

	else if ((Frontdist<1 &&  Leftdis>1 && Rightdist>1)||(Frontdist<1 &&  Leftdis<1 && Rightdist>1)){
		//should go right
		printf("i should go right\n");
		my_vel.linear.x = speed;
		my_vel.angular.z = -ang;
	}

	else if ((Frontdist>1 &&  Leftdis<1 && Rightdist>1)||(Frontdist<1 &&  Leftdis>1 && Rightdist<1)||(Frontdist<1 &&  Leftdis<1 && Rightdist<1)){
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
```


![immagine](https://github.com/youssefattia98/Research-Track-Assignment-2/blob/main/Untitled%20Diagram.jpg)  

The above Flowchart describes more details the communication between the ROS nodes and how data is transferred. Note that, the client can control the speed of the robot to a certain limit to assure that the robot will never crash and if the user chooses to increase the speed more than this limits the simulation will reset with minimum speed. Also, if the user input any wrong input then that he should the simulation will reset the robots position and speed.

4)Final Output. 
================================


https://user-images.githubusercontent.com/69837845/146594897-74acbbae-0cef-4baa-824a-4dbaf89cceb2.mp4


The speed up video below shows the robot behaving in the environment doing its intended task, this simulation can run for ever in which the robot will stay in this loop. Furthermore, this project enhanced my skills in using Linux, docker, GitHub, ROS and Cpp and I am very happy with the output I have reached.
Finally, I really wanted to mention how much I enjoyed working on this project with my collages.  





5)Possible improvements.  
================================
I suggest the following improvements which are as follow:  
     1)Apply a Proportional, Integral, Derivative (PID) controller on the robot so it can make the track in the least possible time and changing its driving and turn speeds according to the feedback of the readings. 
            ![immagine](https://github.com/youssefattia98/Research-Track-Assignment-2/blob/main/68747470733a2f2f626c6f672e776573742d63732e636f6d2f68732d66732f6875622f3333313739382f66696c652d3438393932363132382d6769662f426c6f675f50696374757265732f576861745f69735f5049445f436f6e74726f6c2e6769663f743d313532383731.gif)   
	2)Write a single bash script to run both process in diffrent terminals using Konsole.    
