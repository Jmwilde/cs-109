#include <vector>
#include <string>
#include "helpStoreOr.h"

using namespace std;

helpStoreOr::helpStoreOr(string rule_name, logical_op_t OR, 
                        vector<string> predicates, int i){}

void * helpStoreOr::threadMainBody(void * arg)
{
   storeValues(rule_name, OR, predicates, predicates[i]);
}

   return NULL;

helpStoreOr::~helpStoreOr(){}
