#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <array>
#include <sstream>



int main()
{
    std::ifstream ifs;
    std::string str;
    std::array<int, 10> winning_numbers;
    std::array<int, 25> card_numbers;
    uint32_t card_score{0};
    uint32_t total_score{0};


    
    //std::string path = std::filesystem::current_path().string();
    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/scratchCardsInput.txt", std::ios::in);
    //std::cout << path << std::endl;

    if(ifs)
    {
        int i = -1;
        int j = 0;
        while(!ifs.eof())
        {
            int temp;
            //std::stringstream str_strm;
            //std::getline(ifs, str);
            ifs >> str;
            if(std::stringstream(str) >> temp)
            {
                if( i < 10)
                {
                    if(i != -1)//skip the first number
                        winning_numbers[i++] = temp;
                    else 
                        i++;
                }
                else
                {
                    if(j < 25)
                    {
                        card_numbers[j++] = temp;
                    }
                    else
                    {
                        //process the score
                        bool b_found = false;
                        std::cout << "winning_numbers" << std::endl;
                        for(auto const& win_nb: winning_numbers )
                        {
                           // std::cout << value << ", ";
                            for(auto const& card_nb: card_numbers )
                            {
                                if(win_nb == card_nb)
                                {
                                    b_found = true;
                                    break;
                                }
                                //std::cout << value << ", ";
                            } 
                            if(b_found)
                            {
                                if(card_score == 0)
                                {
                                    card_score = 1;
                                }
                                else
                                {
                                    card_score *= 2;
                                }
                                b_found = false;
                            }
                        } 

                        std::cout << "card score: " << card_score << std::endl;
                        total_score += card_score;
                        std::cout << "total score: " << total_score << std::endl;
                        card_score = 0;
                        i = 0;
                        j = 0;
                    }
                }
            }


                
            //get winning numbers
            //get card numbers
            //calculate score
            //reset indices
            //str_strm << str;
            //std::string temp_str;
            /*
            while(!str_strm.eof())
            {
                str_strm >> str;
            }
            */
            
        }
        ifs.close();
    }
    else
    {
        std::cout << "file error";
    }
    return 0;
}