// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

#ifndef RULE_H
#define RULE_H

#include <vector>
#include <string>
#include "command.h"

using namespace std;

enum logical_op_t {OR, AND};

class Rule: public Command
{
public:
	Rule(logical_op_t logical_op, vector<string> predicates);
	Rule(string name, logical_op_t logical_op, vector<string> predicates);
	~Rule();
	logical_op_t getOp();
	string getPredicate(const int index);
	int getNumPredicates();
	string getName();
private:
	string name; //  Helps with testing
	logical_op_t logical_op;
	int num_predicates;
	vector<string> predicates;
};

#endif  // RULE_H
