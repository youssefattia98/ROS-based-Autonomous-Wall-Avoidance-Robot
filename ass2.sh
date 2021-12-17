roscore &
catkin_make &
rosrun stage_ros stageros $(rospack find second_assignment)/world/my_world.world &
rosrun assignment2 controller_node
