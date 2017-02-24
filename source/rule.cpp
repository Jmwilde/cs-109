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

Rule::Rule(logical_op_t logical_op, vector<string> predicates)
{
	this->logical_op = logical_op;
	this->predicates = predicates;
}

Rule::~Rule(){}

logical_op_t Rule::getOp()
{
	return this->logical_op;
}

string Rule::getPredicate(const int index)
{
	return this->predicates[index];
}

int Rule::getNumPredicates()
{
	return this->num_predicates;
}



