



/*
Workflow:

struct Operation
{
    char name = x,m,a,s
    int to_compare
    char operation
    string outcome
}    

px{a<2006:qkq,m>2090:A,rfg}
    int x = 0;
    int m = 2090;
    int a = 2006;
    int s = 0;
    
    char operation_x = null;
    char operation_m= '>';
    char operation_a ;
    char operation_s;

    string operation_outcome_x
    string operation_outcome_m
    string operation_outcome_a
    string operation_outcome_s

    vector<Operation> operations
    for( operation : operations)

string result = px...
if result = A -> combine the ratings
if result = R -> do nothing
if result = "wf" -> find a wf in the map and execute it

map <Key = wf_name, Workflow>
parse workflow, create struct, add xmas, operation, next wf string ->xmas

parse parts, move them through the workflow

string process_part(Part p, Workflow wf)
{
    get operation_x
    if[](l_compare, r_compare, operator) -> bool
    {
        switch operator
        case <
        return l_compare < r_compare
    }
    return operation_outcome

}

for(auto part : parts)
{
    if part.accepted
        result + = sum_part_ratings
}

if(a<2006)
    qkq()
else if(m > 2090)
    part.accepted = true;
else
    rfg()

map{qkq, ptr}

func(Workflow wf, x,m,a,s)
{
    if
}

struct Part
{
    int x;
    int m;
    int a;
    int s;
};

struct Workflow
{
    int x;
    int m;
    int a;
    int s;
    string name;
    char operation_x;
    char operation_m;
    char operation_a;
    char operation_s;

    void (*wf_ptr)();
}
*/
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <cmath>

using namespace std;

struct Operation
{
    char name;
    int to_compare;
    char operation;
    string outcome;

    void print()
    {
        cout << "Operation" << endl;
        cout << "Name: " << name << endl;
        cout << "to_compare: " << to_compare << endl;
        cout << "operation: " << operation << endl;
        cout << "outcome: " << outcome << endl;
    }
};   

struct Workflow
{
    vector<Operation> operations;
    string default_outcome;

    void print() const
    {
        for(auto op : operations)
            op.print();
        cout << "default_outcome: " << default_outcome << endl;
    }

};

struct Part 
{
    int x;
    int m;
    int a;
    int s;
    bool accepted;

    void print()
    {
        cout << "Part" << endl;
        cout << "x: " << x << endl;
        cout << "m: " << m << endl;
        cout << "a: " << a << endl;
        cout << "s: " << s << endl;
    }

    int sum_ratings()
    {
        return x+m+a+s;
    }
};

string  process_part(Part part, Workflow wf)
{
    auto compare = [&](int l_compare, int r_compare, char comp_operator)
    {
        if( '<' == comp_operator)
            return l_compare < r_compare;
        else if('>' == comp_operator)
            return l_compare > r_compare;
        else
        { 
            cout << "something is wrong here" << endl;
            return false;
        }
    };

    for(auto op : wf.operations)
    {
        int l_compare = 0;
        if('x' == op.name)
            l_compare = part.x;
        else if('m' == op.name)
            l_compare = part.m;
        else if('a' == op.name)
            l_compare = part.a;
        else if('s' == op.name)
            l_compare = part.s;

        if(compare(l_compare, op.to_compare, op.operation))
            return op.outcome;
    }

    return wf.default_outcome;
}

int main()
{
    ifstream ifs;
    string str;
    map<string,Workflow> workflows;
    vector<Part> parts;

    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day19.txt", ios::in);
    if(ifs)
    {
        bool b_switch_to_parts = false;
        while(!ifs.eof())
        {
            stringstream ss;
            getline(ifs, str);
            if(!str.empty()&&!b_switch_to_parts){
                Workflow wf;
                string wf_name;
                ss << str;
                getline(ss, wf_name,'{');

                while(getline(ss, str,',')){
                    std::size_t found = str.find('}');
                    if (found!=std::string::npos)
                    {
                        str.pop_back();
                        wf.default_outcome = str;
                    }
                    else
                    {
                        Operation op{};
                        stringstream ss2;
                        char c;
                        ss2 << str;
                        ss2 >> c;
                        op.name = c;
                        ss2 >> c;
                        op.operation = c;
                        int num_count = 0;
                        int numbers[4]{0,};
                        ss2 >> c;
                        while(c!=':')
                        {
                            numbers[num_count++] = (int)(c - '0');
                            ss2 >> c;
                        }
                        int idx = num_count;
                        while(idx > 0)
                        {
                            op.to_compare += numbers[idx-1] * pow(10, (num_count - idx));
                            idx--;
                        }
                        while(ss2 >> c)
                        {
                            op.outcome.push_back(c);
                        }
                        
                        wf.operations.push_back(op);
                    }
                    
                }
                workflows.emplace(make_pair(wf_name, wf));

            }
            else
            {
                //{x=787,m=2655,a=1222,s=2876}
                b_switch_to_parts = true;
                if(!str.empty())
                {
                    Part p{};
                    ss << str;
                    //getline(ss, str,'{');

                    while(getline(ss, str,','))
                    {
                        stringstream ss2;
                        char c;
                        std::size_t found = str.find('}');
                        if (found!=std::string::npos)
                        {
                            str.pop_back();

                            int num_count = 0;
                            int numbers[4]{0,};
                            ss2 << str;
                            ss2 >> c;
                            ss2 >> c;
                            while(ss2 >> c)
                            {
                                numbers[num_count++] = (int)(c - '0');
                            }
                            int idx = num_count;
                            while(idx > 0)
                            {
                                p.s += numbers[idx-1] * pow(10, (num_count - idx));
                                idx--;
                            }
                        }
                        else
                        {
                            stringstream ss2;
                            char c;
                            char name;
                            ss2 << str;
                            ss2 >> name;
                            if('{' == name)
                                ss2 >> name;
                            ss2 >> c;

                            int num_count = 0;
                            int numbers[4]{0,};
                            while(ss2 >> c)
                            {
                                numbers[num_count++] = (int)(c - '0');
                            }
                            int idx = num_count;
                            while(idx > 0)
                            {
                                if('x' == name)
                                    p.x += numbers[idx-1] * pow(10, (num_count - idx));
                                else if('m' == name)
                                    p.m += numbers[idx-1] * pow(10, (num_count - idx));
                                if('a' == name)
                                    p.a += numbers[idx-1] * pow(10, (num_count - idx));
                                idx--;
                            }

                        }
                    }
                    p.accepted = false;
                    parts.push_back(p);
                }
                
            }
/*
            ss << str;
            char c = ' ';
            string name;

            while( c!= '}')
            {
                ss>>c;
                //px{a<2006:qkq,m>2090:A,rfg}
                while(c != '{')
                {
                    name+=c;
                    ss>>c;
                }
                ss>>c;

            }
            */
        }
        for (const auto& [key, value] : workflows)
        {
            std::cout << "WF: " << key << endl;
            value.print();
        }

        for(auto& part : parts)
        {
            //part.print();
            auto wf = workflows.find("in");
            bool processing_finished  = false;
            string next = process_part(part, wf->second);
            while(!processing_finished)
            {
                if(("A" == next) || ("R" == next))
                {
                    processing_finished = true;
                    if ("A" == next)
                        part.accepted = true;
                }
                else
                {
                    wf = workflows.find(next);
                    next = process_part(part, wf->second);
                }
            }
        }

        long long result = 0;
        for(auto part : parts)
        {
            if(part.accepted)
            result += part.sum_ratings();
        }

        cout << "Final Result: " << result << endl;
    }

    return 0;
}