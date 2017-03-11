#ifndef HELPSTOREOR_H
#define HELPSTOREOR_H

#include "rule.h"
#include "thread.h"
#include "util.h"
#include <vector>
#include <string>

using namespace std;

class helpStoreOr: public Thread
{
public:

   helpStoreOr(string rule_name,logical_op_t OR, vector<string> predicates, int i);
   
//private:
 
};
 #endif  // 

