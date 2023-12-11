#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> valueHistory = {10,13,16,21,30,45};
    vector<int> substractionResult;
    vector<int> extrapolationVector;
    vector<int>::iterator iter;

    for(iter = valueHistory.begin(); iter <= valueHistory.end(); iter++)
    {
        if(iter == valueHistory.end())
            break;
        int first = *iter;
        int next = *(iter + 1);

        substractionResult.push_back(next-first);
    }



    
    return 0;
}