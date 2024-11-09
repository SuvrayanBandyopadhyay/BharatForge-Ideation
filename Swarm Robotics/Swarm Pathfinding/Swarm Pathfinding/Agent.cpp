#include"Agent.hpp"
#include<iostream>
using namespace std;
#define SIZE 64

void Agent::init(int xpos, int ypos,Color c) 
{
	sx = xpos;
	sy = ypos;
	x = sx;
	y = sy;
	color = c;
}

void Agent::move(int index) 
{
	if (index < path.size()) 
	{
		char c = path[index];
		if (c == 'U') 
		{
			y--;
		}
		else if (c == 'D') 
		{
			y++;
		}
		else if (c == 'L') 
		{
			x--;
		}
		else if(c=='R')
		{
			x++;
		}
	}
}
void Agent::draw() 
{
	DrawRectangle(x * SIZE + SIZE / 4, y * SIZE + SIZE / 4, SIZE / 2, SIZE / 2, color);
}

void Agent::reset() 
{
	x = sx;
	y = sy;
}