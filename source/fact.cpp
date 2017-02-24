// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

#include <vector>
#include <string>
#include "fact.h"

using namespace std;

// Default constructor copies the predicates into an array
// Takes an array of predicates and stores them
// This is better than making the constructor variadic

Fact::Fact(vector<string> predicates)
{
	this->num_predicates = predicates.size();
	this->predicates = predicates; // copy by value??
}

Fact::~Fact(){}