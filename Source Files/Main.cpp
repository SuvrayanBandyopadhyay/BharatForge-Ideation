#include "raylib.h"
#include"Pathfinding.hpp"
#include"Draw.hpp"
#include"Agent.hpp"
#include<tuple>
using namespace std;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

//Colors
Color cols[] = { BLUE,GREEN,RED,ORANGE,BROWN,BLACK };

//Some maps
std::vector<std::vector<std::vector<int>>> warehouse = {{{0,0,0,0,0},
                                                         {0,1,0,1,0},
                                                         {0,1,0,1,0},
                                                         {0,1,0,1,0},
                                                         {0,0,0,0,0} } };
std::vector<std::tuple<int, int, int, int, int>> whpaths = {make_tuple(0,0,0,4,4),
                                                          make_tuple(4,4,0,0,0),
                                                          make_tuple(0,4,0,4,0),
                                                          make_tuple(2,2,0,0,4),
                                                          make_tuple(4,0,0,2,2)};

std::vector<std::vector<std::vector<int>>> tunnel    = {{{1,1,1,1,1},
                                                         {0,0,0,0,1},
                                                         {1,1,1,0,1},
                                                         {1,1,1,0,1},
                                                         {1,1,0,0,0} } };

std::vector<std::tuple<int, int, int, int, int>> tpaths = { make_tuple(0,1,0,4,4),
                                                            make_tuple(3,4,0,0,1) };

int main()
{
    
    cout << "Choose map" << endl;
    int ch;
    cout << "1: Warehouse" << endl;
    cout << "2: Tunnel" << endl;
    cin >> ch;

    Dynamic_Pf dpf;
    vector<vector<vector<int>>> map;
   
    vector<tuple<int, int, int, int, int>> paths;
    //If warehouse
    if (ch == 1)
    {
        map = warehouse;
        paths = whpaths;
    }
    else if (ch == 2)
    {
        map = tunnel;
        paths = tpaths;
    }


    //Get paths and set agents
    vector<Agent>agents;
    for (int i = 0; i < paths.size(); i++)
    {
        Agent a;
        a.init(get<0>(paths[i]), get<1>(paths[i]),cols[i%6]);
        for (int i = 0; i < get<2>(paths[i]); i++) 
        {
            a.path += "W";
        }

        a.path+=dpf.findPath(&map,get<0>(paths[i]), get<1>(paths[i]), get<2>(paths[i]), get<3>(paths[i]), get<4>(paths[i]));
        cout << a.path<<endl;
        agents.push_back(a);
    }
    cout << endl;

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            for (int k = 0; k < map[0][0].size(); k++)
            {
                cout << map[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl << endl;
    }

    //Drawing

    init();
    int index = 0;
    while (!WindowShouldClose())
    {

        BeginDrawing();

        for (int j = 0; j < map[index].size(); j++)
        {
            for (int i = 0; i < map[index][0].size(); i++)
            {
                int val = map[index][j][i];
                
              
                if (val == BLOCKED)
                {
                    DrawRectangle(i * 64, j * 64, 64, 64, DARKGRAY);

                }
                else
                {
                    DrawRectangle(i * 64, j * 64, 64, 64, LIGHTGRAY);
                   
                }
            }
           
        }
        for (int i = 0; i < agents.size(); i++) 
        {
            agents[i].draw();
        }

        //Next state
        if (IsKeyReleased(KEY_SPACE)) 
        {
    
            for(int i=0;i<agents.size();i++)
            {
                agents[i].move(index);
            }
            index++;
        }

        //Loop it
        if (index >= map.size()) 
        {
            index = 0;
            for (int i = 0; i < agents.size(); i++)
            {
                agents[i].reset();
            }
        }

        ClearBackground(RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context

    return 0;
}