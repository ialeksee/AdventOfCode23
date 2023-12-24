#define L_BOUNDARY 200000000000000
#define H_BOUNDARY 400000000000000

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
namespace ranges = std::ranges;

struct Point
{
    long long x,y;
};


int direction(Point a, Point b, Point c) {
   int val = (b.y-a.y)*(c.x-b.x)-(b.x-a.x)*(c.y-b.y);
   if (val == 0)
      return 0;     //colinear
   else if(val < 0)
      return 2;    //anti-clockwise direction
      return 1;    //clockwise direction
}

struct HailPath
{
    Point begin{0}, end{0};
    long long time_ns;
    HailPath(long long x1, long long y1, int dir_x, int dir_y);
    void print(){ cout << "x1: " << begin.x << " x2:" << end.x << " y1: " << begin.y << " y2: " << end.y << " For: " << time_ns << endl;};

    bool onLine(Point p) {   //check whether p is on the line or not
    if(p.x <= max(begin.x, end.x) && p.x <= min(begin.x, end.x) &&
        (p.y <= max(begin.y, begin.y) && p.y <= min(begin.y, begin.y)))
        return true;
   
        return false;
    }

    bool operator ==(HailPath r)
    {
        //four direction for two lines and points of other line
        int dir1 = direction(begin, end, r.begin);
        int dir2 = direction(begin, end, r.end);
        int dir3 = direction(r.begin, r.end, begin);
        int dir4 = direction(r.begin, r.end, end);
        
        if(dir1 != dir2 && dir3 != dir4)
            return true; //they are intersecting

        if(dir1==0 && this->onLine(r.begin)) //when p2 of line2 are on the line1
            return true;

        if(dir2==0 && this->onLine(r.end)) //when p1 of line2 are on the line1
            return true;

        if(dir3==0 && r.onLine(begin)) //when p2 of line1 are on the line2
            return true;

        if(dir4==0 && r.onLine(end)) //when p1 of line1 are on the line2
            return true;
                
        return false;
    }
};


HailPath::HailPath(long long x1, long long y1, int dir_x, int dir_y) : begin{x1,y1}, time_ns(0)
{
    end.x = x1;
    end.y = y1;
    long long time_to_leave_x = 0;
    long long time_to_leave_y = 0; 

    if(dir_x < 0)
        time_to_leave_x = (begin.x - L_BOUNDARY) / abs(dir_x);
    else
        time_to_leave_x = (H_BOUNDARY - begin.x) / dir_x;

    if(dir_y < 0)
        time_to_leave_y = (begin.y - L_BOUNDARY) / abs(dir_y);
    else
        time_to_leave_y = (H_BOUNDARY - begin.y) / dir_y;

    if(time_to_leave_x > time_to_leave_y)
    {
        time_ns = time_to_leave_y;
        end.y = (dir_y < 0) ? L_BOUNDARY : H_BOUNDARY;
        end.x = begin.x + (time_ns*dir_x);
    }
    else
    {
        time_ns = time_to_leave_x;
        end.x = (dir_x < 0) ? L_BOUNDARY : H_BOUNDARY;
        end.y = begin.y + (time_ns*dir_y);
    }

}




int main()
{
    ifstream ifs;
    string str;
    vector<HailPath> hail;

    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day24.txt", ios::in);
    if(ifs)
    {
        while(!ifs.eof())
        {
            getline(ifs, str);
            if(!str.empty())
            {
                vector<string> params;
                stringstream ss;
                ss << str;
                while(getline(ss, str,','))
                {
                    params.push_back(str);
                }
                Point p;
                p.x = stoll(params[0]);
                p.y = stoll(params[1]);
                size_t pos = params[2].find('@');
                params[2] = params[2].substr(pos+2);
                int dir_x = stoi(params[2]);
                int dir_y = stoi(params[3]);
                hail.emplace_back(HailPath{p.x, p.y, dir_x, dir_y});
            }
        }
        
        int intersections = 0;
        for(auto h_iter = hail.begin(); h_iter != hail.end(); h_iter++)
        {
            for(auto iter2 = h_iter + 1; iter2 != hail.end(); iter2++)
            {
                if(*h_iter == *iter2)
                    intersections++;
            }
        }
        cout << "Intersections: " << intersections << endl;
    }

    return 0;
}