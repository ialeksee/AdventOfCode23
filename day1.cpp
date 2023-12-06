#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>


int main()
{
    std::ifstream ifs;
    std::string str;
    

    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day1.txt", std::ios::in);

    if(ifs)
    {
        int final_number = 0;
        while(!ifs.eof())
        {
            char c;
            int firstDigit, lastDigit,number = 0;
            std::stringstream ss;

            std::getline(ifs, str);
            ss << str;
            while(ss>>c)
            {
                if(isdigit(c))
                {
                    if(0 == firstDigit)
                    {
                        firstDigit = (c - '0');
                    }
                    else
                    {
                        lastDigit  = (c - '0');
                    }
                } 
            }
            if(lastDigit == 0)
            {
                number = firstDigit*10+firstDigit;
            }
            else
            {
                number = firstDigit*10 + lastDigit;
            }
            firstDigit = 0; 
            lastDigit = 0;
            
            final_number += number; 
            std::cout << number << std::endl;
        }
        std::cout << final_number << std::endl;
    }
    else
    {
        std::cout << "file error";
    }


    return 0;
}