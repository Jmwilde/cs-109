#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <fstream>
#include <string>
#include <strings.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <typeinfo>
#include <cstdint>
#include <array>
#include <iterator>
#include <map>
#include <sstream>
#include <cstdlib>
#include <sstream>

using namespace std;

struct ignorecase { 
    bool operator() (const std::string& lhs, const std::string& rhs) const {
        return strcasecmp(lhs.c_str(), rhs.c_str()) < 0;
    }
};

#endif // COMMON_H
