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

Rule::Rule(string logical_op, vector<string> predicates)
{
	this->logical_op = logical_op;
	this->predicates = predicates;
}

Rule::~Rule(){}

string Rule::getOp()
{
	return this->logical_op;
}



