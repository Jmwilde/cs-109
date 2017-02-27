// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

#include "rule.h"
#include <vector>
#include <string>

using namespace std;


// Precondition: predicates passed to a Rule must be strings
// that exist in KB or RB
Rule::Rule(logical_op_t logical_op, vector<string> predicates) : Command("RULE")
{
	this->logical_op = logical_op;
	this->predicates = predicates;
	this->num_predicates = predicates.size();  // Assumes no nonsense values passed to the rule
}

Rule::Rule(string name, logical_op_t logical_op, vector<string> predicates) : Command("RULE")
{
	this->name = name;
	this->logical_op = logical_op;
	this->predicates = predicates;
	this->num_predicates = predicates.size();
}

Rule::~Rule(){}

logical_op_t Rule::getOp()
{
	return this->logical_op;
}

string Rule::getName()
{
	return this->name;
}

string Rule::getPredicate(const int index)
{
	return this->predicates[index];
}

int Rule::getNumPredicates()
{
	return this->num_predicates;
}



