#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<string> platform;
const char boulder = 'O';
const char stone = '#';
const char empty_space = '.';

int main()
{
    ifstream ifs;
    string str;
    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day14.txt", ios::in);
    if(ifs)
    {
        while(!ifs.eof())
        {
            getline(ifs, str);
            if(!str.empty())
            platform.push_back(str);
        }
        /*
        for(auto row : platform)
        {
            cout << row << endl;
        }
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        */
        int row_length = platform.at(0).size();
        for(int x = 0; x <  row_length; x++)
        {
            for(int y = 0; y < platform.size(); y++)
            {
                if(empty_space == platform[y][x])
                {
                    //find the next boulder
                    for(int j = y+1; j < platform.size(); j++)
                    {
                        //move it up
                        if(boulder == platform[j][x])
                        {
                            platform[j][x] = empty_space;
                            platform[y][x] = boulder;
                            break;
                        }
                        //in case of stone break it up
                        if(stone == platform[j][x])
                        {
                            break;
                        }
                    }
                }
            }            

        }

        int edge_distance = platform.size();
        int total_weight = 0;
        int row_number = 0;
        for(auto row : platform)
        {
            for(auto c : row)
            {
                if(boulder == c)
                {
                    total_weight += edge_distance - row_number;
                }
            }
            row_number++;
        }    

        cout << "Weight: " << total_weight << endl; 
        /*
        for(auto row : platform)
        {
            cout << row << endl;
        }
        */
    }

    return 0;
}