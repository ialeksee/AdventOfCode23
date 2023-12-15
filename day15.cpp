#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <array>

using namespace std;

class Box 
{
    vector<string> lenses;
    public:
    Box(){};
    void remove(string label);
    void add_lens(string label, char focal_length);
    void print_box(int idx);
    int get_focusing_power(int idx);
};

void Box::remove(string label)
{
    auto it = find_if(lenses.begin(), lenses.end(), [&](string str){ return str.find(label) != string::npos;}); 
    if(it != lenses.end())
    {
        lenses.erase(it);
    }
}

void Box::add_lens(string label, char focal_length)
{
    auto it = find_if(lenses.begin(), lenses.end(), [&](string str){ return str.find(label) != string::npos;}); 
    if(it != lenses.end())
    {
        size_t pos = it->find(" ");
        it->replace(pos + 1, 1, 1, focal_length);
    }
    else
    {
        lenses.push_back(label + " " + focal_length);
    }

}

void Box::print_box(int idx)
{
    if(!lenses.empty())
    {
        cout << "Box " << idx <<": ";
        for(auto lens : lenses)
            if(!lens.empty())
                cout << "[" << lens << "]" <<endl; 
    }               
}

int Box::get_focusing_power(int idx)
{
    int result = 0;
    if(!lenses.empty())
    {
        for(int i = 0; i < lenses.size(); i++)
        {
            size_t pos = lenses[i].find(" ");
            int focal_length = (int)(((char)lenses[i][pos+1]) - '0');
            result += (idx + 1) * (i + 1) * focal_length;
        }
    }

    return result;
}

int main()
{
    ifstream ifs;
    string str;
    long hash = 0;
    long sum = 0;
    char c;
    array<Box, 256> boxes{};

    auto calculate_hash = [&] ()
    {
        hash += (long)c;
        hash *= 17;
        hash = hash%256;
    };
    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day15.txt", ios::in);
    if(ifs)
    {
        string label = "";
        while(!ifs.eof())
        {
            if(ifs >> c)        
            {
                if((c >= 'a') && (c<='z'))
                {
                    calculate_hash();
                    label += c;
                }
                
                if('-' == c)
                {
                    boxes[hash].remove(label);
                  //  boxes[hash].print_box(hash);
                }
                
                if('=' == c)
                {
                    ifs >> c;
                    boxes[hash].add_lens(label, c);
                  //  boxes[hash].print_box(hash);
                }

                if(c==',')
                {
                    hash = 0;
                    label.clear();
                }
            }
        }

        int idx = 0;
        int final_result = 0;
        for(auto box : boxes)
            final_result += box.get_focusing_power(idx++);
     //      box.print_box(idx++);

        cout << "Total: " << final_result << endl;

    }
    return 0;
}