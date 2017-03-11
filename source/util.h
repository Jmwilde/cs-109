#include "util.h"

string findValue(map<string,vector<string>> var_map, string value)
{
    // Finds a specific value in a map that maps
    // strings to vectors of strings

    // NOTE: If there's duplicates of the value,
    // it will only find the first one it reaches

    for(map<string,vector<string>>::iterator it = var_map.begin(); it!=var_map.end(); ++it)
    {
        vector<string> letters = it->second;
        for(int i=0; i<letters.size(); i++)
        {
            if(letters[i] == value)
            {
                return it->first;
            }
        }
    }
    return NULL; // Didn't find it
}
