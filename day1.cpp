#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <array>


int main()
{
    std::ifstream ifs;
    std::string str;
    std::array<std::string, 9> number_strings = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    
    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day1.txt", std::ios::in);

    if(ifs)
    {
        int final_number = 0;
        while(!ifs.eof())
        {
            char c;
            int firstDigit, lastDigit,number,firstNumberOccurence, lastNumberOccurence = 0;
            std::stringstream ss;

            std::getline(ifs, str);
    /*      for(auto numStr : number_strings)
            {
                textNumberOccurence = str.find(numStr);
            }
    */
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