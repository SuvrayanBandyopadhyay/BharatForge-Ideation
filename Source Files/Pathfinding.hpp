//This is our pathfinding class it takes a 3 dimensional grid (x,y and t). 
//Our map is defined as a 3d vector (time,y and x)
//For example 
/*
	_*_		_*_  _*_ 	 
	r__		_r_  __r
	__*		__*  __*

	shows a robot moving from (0,1) to (2,1) 

	A bot can move from (x,y,t) to (x,y,t+1)//Not move,
								   (x+1,y,t+1), 
								   (x-1,y,t+1),
								   (x,y-1,t+1),
								   (x,y+1,t+1),

We define our map in the following way
0 -> Empty space... can move here
1 -> Immovable object Cannot move here
2 -> Robot ... Technically we cannot move, but initially we will assume it is movable with
a high move cost. This is because that robot will most probably move by the time we get there.
If that does not happen, we can do dynamic corrections.
*/

#include<iostream>
#include<vector>
#define TIMEOUT 20000
#define PENALTY 500
#define MOVEPENALTY 1 //We want it to wait more than move
#define NOPATH "X"
#define FREE 0
#define BLOCKED 1
#define ROBOT 2
#define CONGESTED 3


//Dynmaic Pathfinding
class Dynamic_Pf
{
public:
	//Finds the path for us
	std::string findPath(std::vector<std::vector<std::vector<int>>>*map,int currx,int curry,int currt,int endx,int endy,int timeout = TIMEOUT);

};

