#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <thread>

using namespace std;

//#define GRID_SIZE 110
#define GRID_SIZE 9

const char left_mirror = '\\';
const char right_mirror = '/';
const char v_splitter = '|';
const char h_splitter = '-';
const char empty_space = '.';

enum class Direction
{
    up,
    down,
    left,
    right
};

struct Tile
{
    char tileType;
    bool isEnergized;
};



struct Light
{
    int x;
    int y;

    Direction dir;
};

array<array<Tile,GRID_SIZE>,GRID_SIZE> grid;

vector<thread> beams;

void traverseGrid(int x, int y, Direction dir)
{
    bool b_hit_wall = false;
    Light beam{x,y,dir}; 

    while(!b_hit_wall)
    {
        switch (beam.dir)
        {
        case Direction::down:
            {
                beam.y += 1;
                if(beam.y >= GRID_SIZE)
                {
                    b_hit_wall = true;
                }
            }
            break;
        case Direction::up:
            {
                beam.y -= 1;
                if(beam.y < 0)
                {
                    b_hit_wall = true;
                }
            }
            break;
        case Direction::left:
            {
                beam.x -= 1;
                if(beam.x < 0)
                {
                    b_hit_wall = true;
                }
            }            
            break;
        case Direction::right:
            {
                beam.x += 1;
                if(beam.x >= GRID_SIZE)
                {
                    b_hit_wall = true;
                }
            }
            break;
        }

        if(!b_hit_wall)
        {
            grid[beam.y][beam.x].isEnergized = true;
            if(grid[beam.y][beam.x].tileType == left_mirror)
            {
                switch(beam.dir)
                {
                case Direction::up:
                    {
                        beam.dir = Direction::left;
                    }
                    break;
                case Direction::down:
                    {
                        beam.dir = Direction::right;
                    }
                    break;
                case Direction::left:
                    {
                        beam.dir = Direction::up;
                    }
                    break;
                case Direction::right:
                    {
                        beam.dir = Direction::down;
                    }
                    break;
                }
            }
            else if(grid[beam.y][beam.x].tileType == right_mirror)
            {
                switch(beam.dir)
                {
                case Direction::up:
                    {
                        beam.dir = Direction::right;
                    }
                    break;
                case Direction::down:
                    {
                        beam.dir = Direction::left;
                    }
                    break;
                case Direction::left:
                    {
                        beam.dir = Direction::down;
                    }
                    break;
                case Direction::right:
                    {
                        beam.dir = Direction::up;
                    }
                    break;
                }
            }
            else if(grid[beam.y][beam.x].tileType == v_splitter)
            {
                switch(beam.dir)
                {
                case Direction::up:
                case Direction::down:
                break;
                case Direction::left:
                case Direction::right:
                    {
              //          beams.emplace_back(thread(traverseGrid, beam.x, beam.y, Direction::up));
                        traverseGrid(beam.x, beam.y, Direction::up);
                        beam.dir = Direction::down;
                    }
                    break;
                }
            }
            else if(grid[beam.y][beam.x].tileType == h_splitter)
            {
                switch(beam.dir)
                {
                case Direction::up:
                case Direction::down:
                    {
                        //beams.emplace_back(thread(traverseGrid, beam.x, beam.y, Direction::left));
                        traverseGrid(beam.x, beam.y, Direction::left);
                        beam.dir = Direction::right;
                    }
                break;
                case Direction::left:
                case Direction::right:
                    break;
                }
            }     
        }
    }
}

int main()
{
    ifstream ifs;
    string str;
    int x = 0;
    int y = 0;
    char c;

    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day16.txt", ios::in);
    if(ifs)
    {
        int count = 0;
        while(!ifs.eof())
        {
         //  getline(ifs, str);
            if(ifs >> c)        
            {
                if(ifs.peek() != '\n')
                    grid[y][x++].tileType = c;
                else
                {
                    x = 0;
                    y++;
                }
            }
        //   grid[y][x++].tileType = c; 
        }
        
        traverseGrid(0,0, Direction::right);

     //   for(int i = 0;i < beams.size(); i++)
       //     beams[i].join();
       
        for(auto row : grid)
        {
            for(auto tile : row)
            {
                if(tile.isEnergized)
                    cout << '#';
                else
                    cout << empty_space;
            }
            cout << endl;
        }
    }
}
