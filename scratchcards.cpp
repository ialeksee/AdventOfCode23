#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <array>
#include <sstream>
#include <ranges>



int main()
{
    std::ifstream ifs;
    std::string str;
    std::array<int, 10> winning_numbers;
    std::array<int, 25> card_numbers;
    std::array<int, 201> card_copies ;
    uint32_t number_of_wins{0};
    uint32_t card_score{0};
    uint32_t total_score{0};
    uint32_t card_index{0};

    std::ranges::fill(card_copies, 1);
    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/scratchCardsInput.txt", std::ios::in);

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
                                number_of_wins++;
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
                        if(0 == card_index)
                        {
                            card_copies[0] = 1;
                        }

                        while( number_of_wins > 0)
                        {
                            int temp_index = card_index + number_of_wins;
                            if(temp_index < card_copies.size())
                            {
                                card_copies[temp_index] += card_copies[card_index];
                                number_of_wins--;
                            }
                        }

                        std::cout << "card score: " << card_score << std::endl;
                        total_score += card_score;
                        std::cout << "total score: " << total_score << std::endl;
                        card_score = 0;
                        i = 0;
                        j = 0;
                        //number_of_wins = 0;
                        card_index++;
                    }
                }
            }
        }
        std::cout << "card copies:" << std::endl;
        int end_result{0};
        for(auto value : card_copies)
        {
            end_result += value;
        }
        std::cout << end_result << std::endl;
        ifs.close();
    }
    else
    {
        std::cout << "file error";
    }
    return 0;
}