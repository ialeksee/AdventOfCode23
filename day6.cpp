#include <iostream>

class Race{
    long time, distance;

    Race(){}
    public:
    Race(long time, long distance) : time(time), distance (distance) {}
    int getNumberofWins();
    long findLowestTimeToPress();
};

int Race::getNumberofWins()
{
    return 0;
}
long Race::findLowestTimeToPress()
{
    long result = 0;
    //start from 2
    long time_to_press = 1;
    bool lowestFound = false;

    while(!lowestFound)
    {
        time_to_press++;
        long travelled_distance = (time - time_to_press) * time_to_press; 
        if(distance < travelled_distance)
        {
            lowestFound = true;
            break;
        }
    }

    result = (time-2*time_to_press)+1;

    return result;
}

int main()
{
    Race race1(54708275, 239114212951253);
 //   Race race2(70,1142);
  //  Race race3(82,1295);
  //  Race race4(75,1253);
  //  Race testRace(30,200);

 //   std::cout << testRace.findLowestTimeToPress() << std::endl;

    //std::cout << race1.findLowestTimeToPress() * race2.findLowestTimeToPress() * race3.findLowestTimeToPress() * race4.findLowestTimeToPress() << std::endl;
    std::cout << race1.findLowestTimeToPress() << std::endl;
    return 0;
}