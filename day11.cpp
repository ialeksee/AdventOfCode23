#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


int main()
{
    ifstream ifs;
    string str;
    const char empty_space = '.';
    const char galaxy = '#';
    
    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day11.txt", ios::in);
    if(ifs)
    {
        vector<vector<char>> universe;
        while(!ifs.eof())
        {
            char c;
            vector<char> row;
            stringstream ss;
            getline(ifs, str);
            if(!str.empty())
            {
                ss << str;
                while(ss>>c)
                {
                    row.push_back(c);
                }
                universe.push_back(row);
            }
        }

        //explode the universe
        //first determine the columns

        vector<long> columns_offset;
        vector<long> rows_offset;
        vector<char> row = universe.at(0);

        for(int i = 0; i < row.size(); i++)
        {
            if(row.at(i) == empty_space)
            {
                bool are_all_empty = true;
                //check all rows at this index
                for(auto next_row : universe)
                {
                    if(next_row.at(i) != empty_space)
                    {
                        are_all_empty = false;
                        break;
                    }
                }
                if(are_all_empty)
                    columns_offset.push_back(i);
            }
        }

        for(int i = 0; i < universe.size(); i++)
        {
            auto row = universe.at(i);
            bool is_row_empty = true;
            for(auto c : row)
            {
                if (c!=empty_space)
                {
                    is_row_empty = false;
                    break;
                }
            }
            if(is_row_empty)
            {
                rows_offset.push_back(i);
            }
        }

        auto find_all_paths = [&] (long x, long y)
        {
            long path_sum = 0;
            long local_x = 0;
            long local_y = 0; 
            for(auto row : universe)
            {
                long offset_y = 0;
                for(auto temp : rows_offset)
                {
                    if(local_y > temp)
                    {
                        offset_y++;
                    }
                    else
                    {
                        break;
                    }
                }
                long temp_y = local_y + (offset_y*999999);
                local_x = 0;
                for(auto c : row)
                {
                    long offset_x = 0;
                    for(auto temp : columns_offset)
                    {
                        if(local_x > temp)
                        {
                            offset_x++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    long temp_x = local_x + (offset_x*999999);
                    if(((temp_y == y) && ( temp_x >= x)) || (temp_y > y))
                    {
                        if(c == galaxy)
                        {
                            long distance = abs(x - temp_x) + abs(y - temp_y);
                            path_sum += distance;
                        }
                    }
                    local_x++;
                }
                local_y++;
            }

            return path_sum;
        };
        long x = 0;
        long y = 0;
        vector<long> path_sum;
        for(auto row : universe)
        {
            long offset_y = 0;
            for(auto temp : rows_offset)
            {
                if(y > temp)
                {
                    offset_y++;
                }
                else
                {
                    break;
                }
            }
            offset_y *= 999999;
            x = 0;
            for(auto c : row)
            {
                long offset_x = 0;
                for(auto temp : columns_offset)
                {
                    if(x > temp)
                    {
                        offset_x++;
                    }
                    else
                    {
                        break;
                    }
                }
                offset_x *= 999999;

                if(c == galaxy)
                {
                    path_sum.push_back(find_all_paths(x+offset_x,y+offset_y));
                }
                x++;
            }
            y++;
        }



/*
        // add the new columns
        for(auto& row : universe)
        {
            for(auto c : row)
            {
                cout << c;
            }
            cout << endl;
            auto it = row.begin();
            for( auto idx : columns_to_expand_idx)
            {
                row.insert(next(it, idx), empty_space);
            }
            for(auto c : row)
            {
                cout << c;
            }
            cout << endl;   
        }
//29, 56, 87, 91, 93, 113, 119, 124, 132,
        //copy to exploded universe
        vector<vector<char>> exploded_universe;
        for(auto row : universe)
        {
            bool isRowEmpty = true;

            exploded_universe.push_back(row);
            for(auto c : row)
            {
                if(c!=empty_space)
                {
                    isRowEmpty = false;
                    break;
                }
            }
            if(isRowEmpty)
            {
                //add it second time
                exploded_universe.push_back(row);
            }
        }
*/
/*
        for(auto row : universe)
        {
            for(auto c : row)
            {
                cout << c;
            }
            cout << endl;
        }
*/
    for(auto i : columns_offset)
        cout << i << ", ";

    cout << endl;        

    for(auto i : rows_offset)
        cout << i << ", ";

    cout << endl;        

    long sum = 0;
    for(auto i : path_sum)
    {
        sum += i; 
        cout << i << ", ";
    }

    cout << endl;
    cout << "Sum: " << sum << endl; 

    }
    return 0;
}