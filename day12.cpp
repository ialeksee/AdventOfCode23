#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{

   vector<int> springs_count;
   vector<int> patterns_count;

    ifstream ifs;
    string str;
    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day12.txt", ios::in);
    if(ifs)
    {
        while(!ifs.eof())
        {
            getline(ifs, str);
            if(!str.empty())
            {
                string word;
                int count = 0;
                stringstream ss;
                ss << str;
                ss>>word;
                springs_count.push_back(word.size());
                ss>>word;
                ss << word;
                
                for(char c : word)
                {
                    if(c!=',')
                        count++;
                }
                patterns_count.push_back(count);
            }
        }
        cout << "Springs: " << *(max_element(springs_count.begin(),springs_count.end())) << endl;
        cout << "Patterns: " << *(max_element(patterns_count.begin(),patterns_count.end())) << endl;

        //max spring count: 20
        //max pattern pieces: 6
        //????????????????????
        //find 1 in a pattern
        //find how to divide the spring string
        // pattern has 3 numbers = maximum 3 parts
        //find longest part of the spring in which the first pattern can fit
        string springs = "?###????????";
        string pattern = "3,2,1";            


        int pattern_pieces = 0;
        vector<int> spring_pattern;
        for(char c : pattern)
        {
            if(c!=',')
                spring_pattern.push_back(c - '0');
        }

        //get the piece where the number will fit
        string temp_string = "";
        //temp_string 
        //find if there are springs
        //first piece size
        int max_size = 0; 
        for(int spring_number : spring_pattern)
        {
            max_size += spring_number + 1;
        }
        string::iterator it = springs.begin();
        for(int spring_number : spring_pattern)
        {
            int max_piece_size = max_size - spring_number;
            while(max_piece_size > 0)
            {
                temp_string.push_back(*it);
                it++;
                max_piece_size--;
            }
        }
        pattern_pieces = spring_pattern.size();
        for ( string::reverse_iterator it=springs.rbegin(); it!=springs.rend(); ++it)
        {    
            std::cout << *it;
            std::cout << '\n';
        }
        int spring_size = springs.size();
   //     while(pattern_pieces-- != 0)
        {

        }
    }

    return 0;
}