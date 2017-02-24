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

class Rule
{
public:
	Rule(string logical_op, vector<string> predicates);
	~Rule();
	string getOp();
private:
	string logical_op;
	vector<string> predicates;
};

#endif  // RULE_H