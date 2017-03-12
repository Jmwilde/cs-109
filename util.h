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

namespace util
{
	string findValue(std::map<std::string,std::vector<std::string>> var_map, std::string value);
}

#endif  // UTIL_H