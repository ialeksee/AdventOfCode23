#include <map>
#include <vector>
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
#define GARDEN_SIZE 131

const char elf = 'O';
const char virtual_elf = 'o';
const char plot = '.';

struct Position
{
    int x;
    int y;
};

int main()
{
    ifstream ifs;
    string str;
    vector<string> garden;
    queue<Position> possible_steps;
    queue<Position> next_steps;
    int counter = 0;

    Position start_position{};
    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day21.txt", ios::in);
    if(ifs)
    {
        while(!ifs.eof())
        {
            getline(ifs, str);
            if(!str.empty())
            {
                garden.push_back(str);
            }
        }
        for(int i = 0; i < GARDEN_SIZE; i++)
        {
            for(int j = 0; j < GARDEN_SIZE; j++)
            {
                if('S' == garden[i][j])
                {
                    start_position.x = j;
                    start_position.y = i;
                    garden[i][j] = '.';
                    break;    
                }
            }
            if(start_position.x != 0)
                break;
        }

        possible_steps.push(start_position);
        //start stepping
        for(int i = 0; i < 85; i++)
        {
            vector<string> copy_garden = garden;
            for(;!possible_steps.empty();possible_steps.pop())
            {
                Position pos = possible_steps.front();
                if((pos.y - 1 >=0) && (copy_garden[pos.y-1][pos.x] == plot))
                {
                    next_steps.push(Position{pos.x, pos.y-1});
                    copy_garden[pos.y-1][pos.x] = virtual_elf;
                }                    
                if((pos.x + 1 < GARDEN_SIZE) && (copy_garden[pos.y][pos.x+1] == plot))
                {
                    next_steps.push(Position{pos.x+1, pos.y});
                    copy_garden[pos.y][pos.x+1] = virtual_elf;
                }                    
                if((pos.y + 1 < GARDEN_SIZE) && (copy_garden[pos.y+1][pos.x] == plot))
                {
                    next_steps.push(Position{pos.x, pos.y+1});
                    copy_garden[pos.y+1][pos.x] = virtual_elf;
                }                    
                if((pos.x - 1 >=0) && (copy_garden[pos.y][pos.x-1] == plot))
                {
                    next_steps.push(Position{pos.x-1, pos.y});
                    copy_garden[pos.y][pos.x-1] = virtual_elf;
                }
                // if(!next_steps.empty())
                //     garden[pos.y][pos.x] = rock;                    
            }
            possible_steps.swap(next_steps);
      //      cout << "Step: " << i << " finished. Queue size: " << possible_steps.size() << endl;
        }

        vector<string> copy_garden = garden;
        for(;!possible_steps.empty();possible_steps.pop())
        {
            Position pos = possible_steps.front();
            if(copy_garden[pos.y][pos.x] != elf)
            {
                copy_garden[pos.y][pos.x] = elf;
                counter++;
            }
        }
        
        for(int i = 0; i < GARDEN_SIZE; i++)
        {
            for(int j = 0; j < GARDEN_SIZE; j++)
            {
                cout << copy_garden[i][j];
            }
            cout << endl;
        }
        
        //Part 2:
        //7307 possible positions on a full map after 130 steps.
        //130 steps are in 26501365 -> 203856,653846153846154 times... 130*203856 = 26501280
        // 26501280 + additional 85 steps. so, 203856 steps are 203856 * 7307 = 1489575792 possible positions + 85 to calculate
        //The figure will be a rhombus. 203856 full maps and 4 maps where it there will be triangles. So we need to calculate the 4 triangles in 85 steps
        //The sides don't have rocks, so one queue with 65 elements to start and project 85 steps from there... 
        // however need to account for the edges which will be partial gardens
/*
        for(int i = 0; i < GARDEN_SIZE; i++)
        {
            if(i%2 == 0)
                possible_steps.push(Position{130,i});
        }

        //start stepping
        for(int i = 0; i < 85; i++)
        {
            vector<string> copy_garden = garden;
            for(;!possible_steps.empty();possible_steps.pop())
            {
                Position pos = possible_steps.front();
                if((pos.y - 1 >=0) && (copy_garden[pos.y-1][pos.x] == plot))
                {
                    next_steps.push(Position{pos.x, pos.y-1});
                    copy_garden[pos.y-1][pos.x] = virtual_elf;
                }   
                /*                 
                if((pos.x + 1 < GARDEN_SIZE) && (copy_garden[pos.y][pos.x+1] == plot))
                {
                    next_steps.push(Position{pos.x+1, pos.y});
                    copy_garden[pos.y][pos.x+1] = virtual_elf;
                } 
                                   
                if((pos.y + 1 < GARDEN_SIZE) && (copy_garden[pos.y+1][pos.x] == plot))
                {
                    next_steps.push(Position{pos.x, pos.y+1});
                    copy_garden[pos.y+1][pos.x] = virtual_elf;
                }                    
                if((pos.x - 1 >=0) && (copy_garden[pos.y][pos.x-1] == plot))
                {
                    next_steps.push(Position{pos.x-1, pos.y});
                    copy_garden[pos.y][pos.x-1] = virtual_elf;
                }
                // if(!next_steps.empty())
                //     garden[pos.y][pos.x] = rock;                    
            }
            possible_steps.swap(next_steps);
      //      cout << "Step: " << i << " finished. Queue size: " << possible_steps.size() << endl;
        }
        
        copy_garden = garden;
        for(;!possible_steps.empty();possible_steps.pop())
        {
            Position pos = possible_steps.front();
            if(copy_garden[pos.y][pos.x] != elf)
            {
                copy_garden[pos.y][pos.x] = elf;
                counter++;
            }
        }

        for(int i = 0; i < GARDEN_SIZE; i++)
        {
            for(int j = 0; j < GARDEN_SIZE; j++)
            {
                cout << copy_garden[i][j];
            }
            cout << endl;
        }

*/
        cout << "Final result: " << counter << endl;
    }
    return 0;
}