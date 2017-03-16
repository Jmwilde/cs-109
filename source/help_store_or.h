#ifndef HELP_STORE_OR_H
#define HELP_STORE_OR_H

#include "rule_engine.h"

using namespace std;

class helpStoreOr: public Thread
{
private:
  RuleEngine* sri;
  string rule_name;
  logical_op_t op;
  vector<string> predicates;
  string predicate;
public:

   helpStoreOr(RuleEngine* sri, string rule_name, logical_op_t op, vector<string> predicates, string predicate);
   ~helpStoreOr();
   void * threadMainBody(void * arg);


};
 #endif  // HELP_STORE_OR_H
