#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct map {
    int destination;
    int source;
    int range;
};

int main()
{
    ifstream ifs;
    string str;
    vector<int> seeds;

    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day5.txt", std::ios::in);

    if(ifs)
    {
        while(!ifs.eof())
        {
            ifs >> str;
            cout << str << endl;
        }
    }
    else
    {
        cout << "file error" << endl; 
    }
}
