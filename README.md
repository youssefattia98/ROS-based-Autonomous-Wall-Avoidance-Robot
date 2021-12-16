# Research Track Assignment 2 description:
Assignment 2 for Research Track course, the project consists of a simulation in which a robot should complete a track without colliding in the walls using ROS and cpp as the prgramming langaue.
This repo consists of the following points:  
 1)How to Setup the Simulator.  
 2)How to use the Simulator.  
 3)Algorithm used to solve the problem ,truth tabel and flowchart.  
 4)Final output.  
 5)Possible improvements.  

1)How to Setup the Simulator.  
================================

Installing and running
----------------------

The simulator requires specific ros version and i reccomend using the Docker image dedicated to this course to make installation and running easier. After cloning the repo to the ros work space the follwing commands should be used in the workspace directiory to intsall.

```bash
$ sudo roscore
$ sudo catkin_make
```

2)How to use the Simulator.  
================================
Once the everything is compiled, get inside the directory on the shell. To run the simulation, run the commands in seperate terminals:

```bash
$ rosrun stage_ros stageros $(rospack find second_assignment)/world/my_world.world
$ rosrun assignment2 controller_node 
$ rosrun my_srv clinet_node 
```

### Motion ###

The Controller can publish both linear and angular speed for the robot to control its motion in the simulation

```cpp
my_vel.linear.x = speed;
my_vel.angular.z = ang;
```
The Value of the speed is changed though the client node in which the user can increase the speed or decrease it accoring to his intreaset, note that the is a limit of the speed to avoid collison.


### Vision ###

The simulation send messages regarding the sensors fedback in which the front view of the robot has a range form 720 to 0 as in 180 degrees to 0 degress.

For example, the following code prints out the values of all the sesnros feedback of the robot:

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
There are plenty of Algorithms that can be used to solve this assignment which I have tried more then one algorithm.
However, the most efficient algorithm by far is used in the solution, in which the robot turns according to his distance with the right wall and left wall same as autonomous cars algorithm to follow a lane. This will be explained more further down below, in the meantime the most challenging part of the script is how the robot decides which direction it should turn.  

Truth table & Flowchart
---------

![immagine](https://github.com/youssefattia98/Research-Track-Assignment-2/blob/main/Left%20distance-1.jpg)  

The above Truth table describes in details the working algorithm of the solution, In which there are 8 conditons according to the reading that the robot recives from the messages. 1 in the truth table means that wall is near and vise versa for the 0 conditon, according to the situation the robot is, it can decide to go straight, turn right, turn left or check what is nearer to turn the oppsite way. At the end this trasnlates to 4 if condtions indicted below.

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


![immagine]()  

The above Flowchart describes more details the working algorithm of the solution.

4)Final Output. 
================================

https://user-images.githubusercontent.com/69837845/146397365-f4ed9b4b-f90a-41b5-b385-2e2354150dbc.mp4


The speed up video below shows the robot behaving in the environment doing its intended task, this simulation can run for ever in which the robot will stay in this loop. Furthermore, this assignment enhanced my skills in using Linux, docker, GitHub, ROS and Cpp and I am very happy with the output I have reached.
Finally, I really wanted to mention how much I enjoyed working on this project with my collages.  





5)Possible improvements.  
================================
I suggest the follwing improvements which are as follow:  
     Apply a Proportional, Integral, Derivative (PID) controller on the robot so it can make the track in the least possible time and changing its driving and turn speeds according to the feedback of the readings. 
            ![immagine](https://github.com/youssefattia98/Research-Track-Assignment-2/blob/main/68747470733a2f2f626c6f672e776573742d63732e636f6d2f68732d66732f6875622f3333313739382f66696c652d3438393932363132382d6769662f426c6f675f50696374757265732f576861745f69735f5049445f436f6e74726f6c2e6769663f743d313532383731.gif)  
