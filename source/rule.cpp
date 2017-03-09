// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

#include "rule.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;


// Precondition: predicates passed to a Rule MUST be strings
// that exist in KB or RB, otherwise you can get stuck in an infinite loop

Rule::Rule(string name, logical_op_t logical_op, vector<string> predicates, vector<string> values)
{
	this->name = name;
	this->logical_op = logical_op;
	this->predicates = predicates;
	this->num_predicates = predicates.size();
	this->values = values;
	this->num_values = values.size();
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

string Rule::getPredicate(int index)
{
	if (index >= num_predicates)
	{
		cout << "ERROR: Index out of bounds on getValue().\n";
	}
	return this->predicates[index];
}

int Rule::getNumPredicates()
{
	return this->num_predicates;
}

string Rule::getValue(int index)
{
	if (index >= num_values)
	{
		cout << "ERROR: Index out of bounds on getValue().\n";
	}
	return this->values[index];
}

int Rule::getNumValues()
{
	return this->num_values;
}

vector<string> Rule::getValueVector()
{
	return this->values;
}

