# 2D Elevation Map Robot #

## About ##
So this is the simple elevation map for the robot

So the task is to:
1. Create the data structure
2. Insertion of the new heights both with and without a roboot-centric pose
3. Computes min/max over a cell-index range
4. Clears all data
5. Test all

## Approach ##
I am using std::deque as a data structure, so to shift the data when the robot moves, it doesn't have to get more expensive to move the array. 

I thought in the first place to use std::vector, but to shift, you need to get more space in a size of N to be a temporary data, then move the data to the temporary first, then put the data back to the real place.

So, using std::deque, it's just O(S) while S is the number of shift. In this case deque also useful if the robot move backwards, so we can pop back also to remove.

But there is still a optimization gap when doing the getMin and getMax, as need to go O(n). I tried to use other data structure such as monotonic stack, but I don't have time.

## Setup ##
1. create your ws `mkdir -p catkin_ws/src`
2. copy `robertsen-putra-sugianto` folder inside the src folder
3. `cd catkin_ws`
4. `catkin_make`

## Usage ##
Run `./build/robertsen-putra-sugianto/test_elevation_map` to test