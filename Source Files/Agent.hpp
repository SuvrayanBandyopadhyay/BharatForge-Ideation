#include"raylib.h"
#include<iostream>
#include<string>
class Agent 
{
public:
	std::string path;
	Color color;
	int sx;//Start pos x
	int sy;//Start pos y
	int x;//
	int y;
	int cindex;//Current index

	void init(int xpos,int ypos,Color c);
	void move(int index);
	void draw();
	void reset();
};

