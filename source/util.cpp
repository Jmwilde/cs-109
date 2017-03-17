#include "util.h"

using namespace std;

// Finds a specific value in a map that maps
// strings to vectors of strings

// NOTE: If there's duplicates of the value,
// it will only find the first one it reaches

string util::findValue(map<string,vector<string>> var_map, string value)
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

bool util::isWhitespace(string str)
{
    return (str.find_first_not_of(" \t\n\v\f\r") == string::npos);
}