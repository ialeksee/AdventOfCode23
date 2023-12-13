#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>


using namespace std;
map<string, int> solutions;

int get_sym_line (string pattern, int pos)
{
    if(pos + 1 < pattern.size())
    {
        int pos1 = pos;
        int pos2 = pos+1;
        bool b_sym_line_found = true;
        while(pos2 < pattern.size())
        {
            char c1 = pattern.at(pos1--);
            char c2 = pattern.at(pos2++);

            if(c1!=c2)
            {
                b_sym_line_found = false;
                break;
            }
            if(pos1 == 0)
            {break;}
        }
        if(b_sym_line_found)
            return pos;
        else
            return get_sym_line(pattern, pos+1);
    }
    return -1;
};


int main()
{
    
    string pattern = "#.##..##.";
    int line_of_symetry = 0;
    int old_line = 0;
    int v_reflections = 0;
    int h_reflections = 0;
    ifstream ifs;
    string str;
    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day13.txt", ios::in);
    if(ifs)
    {
        int i = 0;
        while(!ifs.eof())
        {
            getline(ifs, str);

            if(!str.empty())
            {
                if(0 == line_of_symetry)
                {
                    line_of_symetry = 1;//str.size()/2;
                }   
                if(-1 == line_of_symetry)
                    continue;

             //   if(auto search = solutions.find(str); search != solutions.end())
             //   {
                 //   cout << "Found: " << search->first << ", " << search->second <<endl;
           //         line_of_symetry = search->second;
           ///     }
          //      else
                {
                    line_of_symetry = get_sym_line(str, line_of_symetry);

                    if(-1 != line_of_symetry)
                    {
                        solutions.insert({str, line_of_symetry});
                        if(old_line == 0)
                        {
                            old_line = line_of_symetry;
                        }
                        else
                        {
                            if(old_line != line_of_symetry)
                            {
                       //         line_of_symetry = -1;
                       //         continue;
                            }
                        }
                    }
                    else
                    {
                        continue;
                    }
                }        
            }
            else
            {
                cout << "Line " << i++ << ": " << line_of_symetry << endl;
                if(-1 != line_of_symetry)
                    v_reflections += line_of_symetry + 1;
                line_of_symetry = 0;
                old_line = 0;
            }
            
        }
        ifs.clear();
        ifs.seekg(0);
        vector<string> rows; 
        vector<string> columns;
        bool is_first_char = true;
        i =0;
        while(!ifs.eof())
        {
            getline(ifs, str);
            if(!str.empty())
            {
                rows.push_back(str);
            }
            else
            {
                is_first_char = true;
                i = 0;
                for(string row : rows)
                {
                    for(char c : row)
                    {
                        if(is_first_char)
                        {
                            string temp_str;
                            temp_str += c;
                            columns.push_back(temp_str);
                        }
                        else
                        {
                            columns.at(i++) += c;
                        }
                    }
                    is_first_char = false;
                    i = 0;
                }
                line_of_symetry = 0;
                old_line = 0;
                for(auto column : columns)
                {
                    if(0 == line_of_symetry)
                    {
                        line_of_symetry = 1;//column.size()/2;
                    }   
                    if(-1 == line_of_symetry)
                        break;

              //      if(auto search = solutions.find(column); search != solutions.end())
                    {
                    //   cout << "Found: " << search->first << ", " << search->second <<endl;
             //           line_of_symetry = search->second;
                    }
             //       else
                    {
                        line_of_symetry = get_sym_line(column, line_of_symetry);

                        if(-1 != line_of_symetry)
                        {
                            solutions.insert({column, line_of_symetry});
                            if(old_line == 0)
                            {
                                old_line = line_of_symetry;
                            }
                            else
                            {
                                if(old_line != line_of_symetry)
                                {
                             //       line_of_symetry = -1;
                                 //   break;
                                }
                            }
                        }
                        else
                        {
                            break;
                        }
                    }                        
                }                
                cout << "horizontal Line " << i++ << ": " << line_of_symetry << endl;
                if(-1 != line_of_symetry)
                    h_reflections += line_of_symetry+1;
                columns.clear();
                rows.clear();
            }
        }

        cout << "Vertical: " << v_reflections << endl;
        cout << "Horizontal: " << h_reflections << endl;
        cout << "Total: " << v_reflections + (h_reflections*100) << endl;
    }
    return 0;
}