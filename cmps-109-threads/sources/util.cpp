#include "util.h"

void myreplace(std::string& subject, const std::string& search, const std::string& replace)
{
    size_t pos = 0;
    while((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

int random_number(int min, int max)
{
    int result=0;
    if(min < max) // if min less than max
    {
            srand(time(NULL)); // Randomize using time
            srand(clock());    // Randomize again using CPU clock
            // Generate a random number and mod it by the range and add to it the min and store in result
            result = (rand()%(max-min))+min;
    } // else return the average
    else result = (min+max)/2;
    return result; // return result
}