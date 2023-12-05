#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Seed {



    Seed(){};

    public:
    Seed(long start_seed, long range) : start_seed(start_seed), range(range) {}
    void printValues();
    long start_seed;
    long range;
};

void Seed::printValues(){
    cout << "seed: " << start_seed << endl;
    cout << "range: " << range << endl;
}

class Almanac {
    long destination;
    long source;
    long range;

    Almanac(){}
    public:
    Almanac(long destination, long source, long range) : destination(destination), source(source), range(range) { }
    ~Almanac() { }
    long getMappedValue(long source);
    void printValues();
    bool isInRange(long source);
};

long Almanac::getMappedValue(long source)
{
    if((source >= this->source) && (source < this->source + range))
    {
        long matchedPosition = source  - this->source; 
        return destination + matchedPosition;
    }

    return -1;
}

bool Almanac::isInRange(long source)
{
    if((source >= this->source) && (source < this->source + range))
    {
        return true;
    }
    return false;
}
void Almanac::printValues()
{
    cout << "destination: " << destination << endl;
    cout << "source: " << source << endl;
    cout << "range: " << range << endl;
}

long getValueFromAMap(vector<Almanac> *Map, long value)
{
    long returnValue = -1;
    for(auto temp : *Map)
    {
        returnValue = temp.getMappedValue(value);
        if(returnValue != -1)
        break;
    }
    return returnValue;
}

enum class ReadState{seed, soil, fertilizer, water, light, temperature, humidity, location, invalid};

int main()
{
    ifstream ifs;
    string str;
    vector<Seed> seeds;
    vector<Almanac> seed_to_soil;
    vector<Almanac> soil_to_fertilizer;
    vector<Almanac> fertilizer_to_water;
    vector<Almanac> water_to_light;
    vector<Almanac> light_to_temperature;
    vector<Almanac> temperature_to_humidity;
    vector<Almanac> humidity_to_location;
    ReadState state = ReadState::invalid;

    ifs.open( "/Users/ivo/Coding/C++/AdventOfCode23/day5.txt", std::ios::in);

    if(ifs)
    {
        while(!ifs.eof())
        {
            ifs >> str;
            if(str == "seeds:")
            {
                state = ReadState::seed;
            }
            else if(str == "seed-to-soil")
            {
                state = ReadState::soil;
                ifs >> str; // get rid of map:
            }
            else if(str == "soil-to-fertilizer")
            {
                state = ReadState::fertilizer;
                ifs >> str; // get rid of map:
            }
            else if(str == "fertilizer-to-water")
            {
                state = ReadState::water;
                ifs >> str; // get rid of map:
            }
            else if(str == "water-to-light")
            {
                state = ReadState::light;
                ifs >> str; // get rid of map:
            }             
            else if(str == "light-to-temperature")
            {
                state = ReadState::temperature;
                ifs >> str; // get rid of map:
            }             
            else if(str == "temperature-to-humidity")
            {
                state = ReadState::humidity;
                ifs >> str; // get rid of map:
            }             
            else if(str == "humidity-to-location")
            {
                state = ReadState::location;
                ifs >> str; // get rid of map:
            }             
            else
            {
                long t1, t2, t3 = 0;
                if(state != ReadState::seed)
                {
                    t1 = stol(str);
                    ifs >> str;
                    t2 = stol(str);
                    ifs >> str;
                    t3 = stol(str);
                }
                switch (state)
                {
                case ReadState::seed:
                {

                   long initial_seed = stol(str);
                    ifs>>str;
                    long range = stol(str);
                    seeds.emplace_back(Seed(initial_seed, range));
                    break;
                }
                case ReadState::soil:
                    seed_to_soil.emplace_back(Almanac(t1,t2,t3));
                    break;
                case ReadState::fertilizer:
                    soil_to_fertilizer.emplace_back(Almanac(t1,t2,t3));
                    break;
                case ReadState::water:
                    fertilizer_to_water.emplace_back(Almanac(t1,t2,t3));
                    break;
                case ReadState::light:
                    water_to_light.emplace_back(Almanac(t1,t2,t3));
                    break;
                case ReadState::temperature:
                   light_to_temperature.emplace_back(Almanac(t1,t2,t3));
                    break;
                case ReadState::humidity:
                    temperature_to_humidity.emplace_back(Almanac(t1,t2,t3));
                    break;
                case ReadState::location:
                    humidity_to_location.emplace_back(Almanac(t1,t2,t3));
                    break;
                
                default:
                    ifs >> str;
                    cout << "default: " << str << endl;
                    break;
                }
            }
            //cout << str << endl;
        }
       /*
        cout << "Check humidity_to_location: " << endl;
        for ( auto Value : humidity_to_location)
        {
            Value.printValues();
        }
        */
        
    }
    else
    {
        cout << "file error" << endl; 
    }

    long location_number = LONG_MAX;


//19:38
    //for(auto seed : seeds)
    {
   /*     long range = seeds[0].range;
        while(range > 0)
        {
            range--;
            long temp = getValueFromAMap(&seed_to_soil, seeds[0].start_seed + range);
            temp = getValueFromAMap(&soil_to_fertilizer, temp);
            temp = getValueFromAMap(&fertilizer_to_water, temp);
            temp = getValueFromAMap(&water_to_light, temp);
            temp = getValueFromAMap(&light_to_temperature, temp);
            temp = getValueFromAMap(&temperature_to_humidity, temp);
            temp = getValueFromAMap(&humidity_to_location, temp);
            if((temp < location_number) && temp != -1)
                location_number = temp;

        }
        cout << location_number << endl;
        */

       
        //seed.printValues();
        
    }
}
