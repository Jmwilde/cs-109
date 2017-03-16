#include "util.h"

// Finds a specific value in a map that maps
// strings to vectors of strings

// NOTE: If there's duplicates of the value,
// it will only find the first one it reaches
namespace util
{
    using namespace std;
    
    string findValue(map<string,vector<string>> var_map, string value)
    {
        string find = "";

        for(map<string,vector<string>>::iterator it = var_map.begin(); it!=var_map.end(); ++it)
        {
            vector<string> letters = it->second;
            for(int i=0; i<letters.size(); i++)
            {
                if(letters[i] == value)
                {
                    find = it->first;
                }
            }
        }
        return find;
    }
}