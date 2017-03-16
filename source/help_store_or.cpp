#include <vector>
#include <string>
#include "help_store_or.h"

using namespace std;

helpStoreOr::helpStoreOr(RuleEngine* sri, string rule_name, logical_op_t op,
                        vector<string> predicates, string predicate){
                          this->sri = sri;
                          this->rule_name = rule_name;
                          this->op = op;
                          this->predicates = predicates;
                          this->predicate = predicate;
                        }

void * helpStoreOr::threadMainBody(void * arg)
{
   sri->storeValues(rule_name, op, predicates, predicate);
   return NULL;
}

helpStoreOr::~helpStoreOr(){}
