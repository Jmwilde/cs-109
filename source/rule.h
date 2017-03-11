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

using namespace std;

enum logical_op_t {OR, AND};

class Rule
{
public:
	Rule(string name, logical_op_t logical_op, vector<string> predicates, vector<string> values);
	~Rule();
	string getName();
	logical_op_t getOp();
	vector<string> getValueVector();
	string getValue(int index);
	string firstValue();
	string lastValue();
	int getNumValues();
	string getPredicate(int index);
	int getNumPredicates();
private:
	string name; //  Helps with testing
	logical_op_t logical_op;
	vector<string> values;
	int num_values;
	vector<string> predicates;
	int num_predicates;
};

#endif  // RULE_H
