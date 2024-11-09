#include"Pathfinding.hpp"
#include<tuple>

using namespace std;

//Node class
class node
{
public:
	int x;//x
	int y;//y
	int t;//Time 
	float gcost;//Move cost
	int prev;//Previous index
};


//Manhatten distance between two nodes
float manDist(node a,float bx,float by)
{
	float ax = static_cast<float>(a.x);
	float ay = static_cast<float>(a.y);

	//Return the distance
	return abs(ax - bx) + abs(ay - by);
}

//f cost function for nodes (a ->current , b ->end)
float fcost(node a, float bx,float by)
{
	return a.gcost+a.t + manDist(a, bx,by);
}
//Get state
int getMapState(vector<vector<vector<int>>>*map, int x, int y, int t) 
{
	int value = 0;
	if(t>=0)
		value = (*map)[t][y][x];
	return value;
}
//Set map state
void setMapState(vector<vector<vector<int>>>* map, int x, int y, int t,int val)
{

	if(t>=0)
		(*map)[t][y][x] = val;
	
}

//Function definitions
string Dynamic_Pf::findPath(std::vector<std::vector<std::vector<int>>>* map, int currx, int curry,int currt, int endx, int endy,int timeout) 
{
	//Find the limits of the map;
	int tlimit = map->size();//Time in the future which the map is considering. This can be extended if we need to expand our horizon
	int ylimit = (*map)[0].size();//Because number of rows = y. 
	int xlimit = (*map)[0][0].size();//Number of columns = x;
	


	//Our open, closed list
	//We define our nodes 5 element tuple (x,y,time,g,prev_index). prev_index is the index of the previous node in our closed list and g is the move cost

	vector<node>olist;
	vector<node>clist;

	//We append the current node to our open list
	node start{ currx, curry, currt,2, -1 };//-1 because it has no parent

	olist.push_back(start);


	node current;//Current node
	int tout = 0;//For timeout
	while (tout < TIMEOUT) 
	{
		
		//Find minimum m cost
		auto mincost = min_element(olist.begin(), olist.end(), [endx, endy](const node& a, const node& b)
			{
				return fcost(a, endx, endy) < fcost(b, endx, endy);
			});

		if (mincost == olist.end()) 
		{
			//No path found;
			return NOPATH;
		}

		int i = distance(olist.begin(), mincost);

		//Now we deal with the lowest fcost
		current = olist[i];

		if (current.x == endx && current.y == endy) 
		{
			//We have reached;
			break;
		}
		else 
		{
		
			int x = current.x;//x
			int y = current.y;//y
			int t = current.t + 1;//We are looking at the next time index
			float cost = current.gcost;
			int parent = clist.size();//Since the current node will occupy this position

			
			if (t >= map->size()) 
			{
				map->push_back(map->at(map->size() - 1));//Expand time horizon
			
			}

			//Add 4 nodes
			//Left node
			if (x - 1 >= 0) 
			{
				
				int v = getMapState(map, x - 1, y, t);
				//cout <<"left"<< v << endl;
				if (v == FREE) 
				{
					node n{ x - 1,y,t,cost + 1+MOVEPENALTY,parent };
					olist.push_back(n);//Push back left node
				}
				else if (v == ROBOT||v==CONGESTED)
				{
					//Robots should not be close to each other.. but it may be impossible to avoid it at times
					//Give penalty
					node n{ x - 1,y,t,cost + PENALTY+MOVEPENALTY,parent };
					olist.push_back(n);//Push back left node
				}
			}

			//Right node
			if (x + 1 < xlimit)
			{
				int v = getMapState(map, x + 1, y, t);
				//cout << "right" << v << endl;
				if (v == FREE)
				{
					node n{ x + 1,y,t,cost + 1,parent };
					olist.push_back(n);//Push back left node
				}
				else if (v == ROBOT || v == CONGESTED)
				{
					//Robots should not be close to each other.. but it may be impossible to avoid it at times
					//Give penalty
					node n{ x + 1,y,t,cost + PENALTY+MOVEPENALTY,parent };
					olist.push_back(n);//Push back left node
				}
			}

			//UP
			if (y- 1 >=0)
			{
				int v = getMapState(map, x , y-1, t);
				//cout << "up" << v << endl;
				if (v == FREE)
				{
					node n{ x,y-1,t,cost + 1+MOVEPENALTY,parent };
					olist.push_back(n);//Push back left node
				}
				else if (v == ROBOT || v == CONGESTED)
				{
					//Robots should not be close to each other.. but it may be impossible to avoid it at times
					//Give penalty
					node n{ x ,y-1,t,cost + PENALTY+MOVEPENALTY,parent };
					olist.push_back(n);//Push back left node
				}
			}

			//Down 
			if (y + 1 < ylimit)
			{

				int v = getMapState(map, x, y+1, t);
				//cout << "down" << v << endl;
				if (v == FREE)
				{
					node n{ x ,y+1,t,cost + 1,parent };
					olist.push_back(n);//Push back left node
				}
				else if (v == ROBOT || v == CONGESTED )
				{
					//Robots should not be close to each other.. but it may be impossible to avoid it at times
					//Give penalty
					node n{ x,y+1,t,cost + PENALTY+MOVEPENALTY,parent };
					olist.push_back(n);//Push back left node
				}
			}
			//Same position
			if (true) 
			{
				int v = getMapState(map, x, y, t);
				//cout << "same" << v << endl;
				if (v == FREE)
				{
					node n{ x,y,t,cost + 1,parent };
					olist.push_back(n);//Push back left node
				}
				else if (v == ROBOT || v == CONGESTED)
				{
					//Robots should not be close to each other.. but it may be impossible to avoid it at times
					//Give penalty
					node n{ x,y,t,cost + PENALTY,parent };
					olist.push_back(n);//Push back left node
				}
			}
		}
	
		tout++;//Timeout
		clist.push_back(current);
		//Erase it from the open list
		olist.erase(olist.begin() + i);
	}

	//If reached
	if (current.x == endx && current.y == endy)
	{
		//Add it to the remaining paths
		int lt = current.t;
		if (lt < map->size()) 
		{
			for (int i = lt; i < map->size(); i++) 
			{
				setMapState(map, current.x, current.y, i, ROBOT);
			}
		}
		string path="";
		while (current.prev != -1) 
		{
			setMapState(map, current.x, current.y, current.t, ROBOT);

		
			setMapState(map, current.x, current.y, current.t-1, CONGESTED);
			
			node prev = clist[current.prev];

			if (prev.x < current.x)
			{
				path += "R";//Right
			}
			else if (prev.x > current.x) 
			{
				path += "L";//Left
			}
			else if (prev.y > current.y) 
			{
				path += "U";//Up
			}
			else if (prev.y < current.y) 
			{
				path += "D";//Down
			}
			else 
			{
				path += "W";//Wait
			}
			
			current = prev;
		}
		//Map states
		setMapState(map, current.x, current.y, current.t, ROBOT);

		setMapState(map, current.x, current.y, current.t - 1, CONGESTED);
		
		//Final path
		reverse(path.begin(),path.end());
		return path;
	}

	else 
	{
		return NOPATH;
	}

}