#ifndef HELPSTOREOR_H
#define HELPSTOREOR_H


#include "rule.h"
#include "rule_engine.h"
#include "thread.h"
#include <vector>
#include <string>

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

   helpStoreOr(RuleEngine* sri, string rule_name,logical_op_t OR, vector<string> predicates, string predicate);
   ~helpStoreOr();
   void * threadMainBody(void * arg);


};
 #endif  //
