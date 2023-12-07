#include <string>
#include <utility>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <ranges>
#include <string_view>

using namespace std;

//create pairs with numeric weights
pair<char, int> cardValues[13] = { 
make_pair('A', 100),
make_pair('K', 95),
make_pair('Q', 90),
make_pair('J', 35),
make_pair('T', 80),
make_pair('9', 75),
make_pair('8', 70),
make_pair('7', 65),
make_pair('6', 60),
make_pair('5', 55),
make_pair('4', 50),
make_pair('3', 45),
make_pair('2', 40)
};

class Hand
{
    string handValue;
    

    Hand(){}
    int calculateHandValue() const;
    public:
    int bid;
    Hand(string handValue, int bid) : handValue(handValue), bid(bid){  }

    friend bool operator<(const Hand& l, const Hand& r)
    {
        int lScore = l.calculateHandValue();
        int rScore = r.calculateHandValue();

        if(lScore != rScore)
            return lScore < rScore;
        else
            return l.isHandValueSmaller(r.handValue);
    }

    void printBid()
    {
        cout << bid << endl;
    }

    bool isHandValueSmaller(string secondHand) const;
};

int Hand::calculateHandValue() const
{
    int score=1;
    int idx = 0; 

    array<int, 13> occuranceCount{0}; 
    for(char card : handValue)
    {
        idx = 0;
        for(auto value : cardValues)
        {
            if(card == get<0>(value))
            {
        //        score += (pow(get<1>(value), (occuranceCount[idx] + 1))); 
                occuranceCount[idx]++;
                break;
            }
            idx++;
        }        
    }

    int numberOfJokers = occuranceCount[3];
    if(numberOfJokers >= 4)
    {
        return 10;
    }
    occuranceCount[3] = 0;
    bool bPairFound = false;
    bool bThirdfound = false;
    sort(occuranceCount.begin(), occuranceCount.end());
    reverse(occuranceCount.begin(), occuranceCount.end());
    for(int occ : occuranceCount)
    {
        if(5==occ)
        {
            score = 10;
            break;
        }

        if(4==occ)
        {
            if(numberOfJokers != 0)
                score = 10; //automatic five
            else
                score = 9;
            break;
        }

        if(3 == occ)
        {
            if(numberOfJokers != 0)
            {
                score = 8 + numberOfJokers; // automatic 5 or 4
                break; 
            }

            bThirdfound = true;
        }

        if(2 == occ)
        {
            if(numberOfJokers != 0)
            {
                if(numberOfJokers == 1) 
                    bThirdfound = true;
                else
                {
                    score = 7 + numberOfJokers; // automatic 5 or 4
                    break; 
                }
                numberOfJokers = 0;
            }
            else{
                if(bThirdfound)
                {
                    score = 8;
                    break;
                }
                if(bPairFound)
                {
                    score = 6;
                    break;
                }
                bPairFound = true;
            }
        }

        if(1==occ)
        {
            if(1 == numberOfJokers)
            {
                bPairFound = true;
            }
            if(2 == numberOfJokers)
            {
                bThirdfound = true;
            }
            if(3 == numberOfJokers)
            {
                score = 9;                
            }
            break;
        }
    }

    if(score == 1)
    {


        if(bThirdfound && score == 1)
        {
            score = 7;
        }
        if(bPairFound && score == 1)
        {
            score = 5;
        }
    }
    return score;
}

bool Hand::isHandValueSmaller(string secondHand) const
{
    int idx = 0;
    for(char card : handValue)
    {
        if(card != secondHand[idx])
        {
            auto getCardValue = [](auto hand){for (auto value : cardValues) { if(hand == get<0>(value)) return get<1>(value);  }};
            if( getCardValue(card) < getCardValue(secondHand[idx]))
            {
                return true;
            }
            break;
        }
        idx++;
    }

    return false;
}

int main()
{
    std::ifstream ifs;
    std::string str;

    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day7.txt", std::ios::in);
    
    if(ifs)
    {
        vector<Hand> handsVector;
        while(!ifs.eof())
        {
            getline(ifs, str);
            if(!str.empty())
            {
                auto split = str
                        | std::ranges::views::split(' ')
                        | std::ranges::views::transform([](auto&& str) { return std::string_view(&*str.begin(), std::ranges::distance(str)); });

                vector<string> capture;
                for (auto&& word : split)
                {
                    capture.emplace_back(word);
                }
                int bid = stoi(capture.at(1));
                handsVector.emplace_back(capture.at(0), bid);
            }   
        }
/*
         handsVector.emplace_back("32T3K", 765);
         handsVector.emplace_back("T55J5", 684);
         handsVector.emplace_back("KK677", 28);
         handsVector.emplace_back("KTJJT", 220);
         handsVector.emplace_back("QQQJA", 483);


handsVector.emplace_back("2345A", 1 );
handsVector.emplace_back("Q2KJJ", 13);
handsVector.emplace_back("Q2Q2Q", 19);
handsVector.emplace_back("T3T3J", 17);
handsVector.emplace_back("T3Q33", 11);
handsVector.emplace_back("2345J", 3);
handsVector.emplace_back("J345A", 2);
handsVector.emplace_back("32T3K", 5);
handsVector.emplace_back("T55J5", 29);
handsVector.emplace_back("KK677", 7);
handsVector.emplace_back("KTJJT", 34);
handsVector.emplace_back("QQQJA", 31);
handsVector.emplace_back("JJJJJ", 37);
handsVector.emplace_back("JAAAA", 43);
handsVector.emplace_back("AAAAJ", 59);
handsVector.emplace_back("AAAAA", 61);
handsVector.emplace_back("2AAAA", 23);
handsVector.emplace_back("2JJJJ", 53);
handsVector.emplace_back("JJJJ2", 41);
*/
        sort(handsVector.begin(), handsVector.end());

        long score = 0;
        int rank = 1;
        for( Hand h : handsVector)
        {
           // cout << "bid: " << h.bid << endl;
            score += rank*h.bid;
            rank++;
        }

        cout << "Final score: " << score << endl;
    }
}