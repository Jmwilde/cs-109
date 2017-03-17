// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

namespace util
{
	string findValue(map<string,vector<string>> var_map, string value);
	bool isWhitespace(string str);
}

#endif  // UTIL_H