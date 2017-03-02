// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

#include <vector>
#include <string>
#include <iostream>
#include "fact.h"

using namespace std;

// Default constructor copies the predicates into an array
// Takes an array of predicates and stores them
// This is better than making the constructor variadic

// template <typename ...ArgsT>
// Fact::Fact(ArgsT ...strings)
// {
//     Fact({strings...});
// }

Fact::Fact(string name, vector<string> predicates)
{
	this->name = name;
	this->num_predicates = predicates.size();
	this->predicates = predicates; // copy by value??
}

int Fact::getNumPredicates()
{
	return this->num_predicates;
}

string Fact::getPredicate(int index)
{
	if (index >= num_predicates)
	{
		cout << "ERROR: Index out of bounds on getPredicate().\n";
	}
    return this->predicates[index];
}

string Fact::firstPredicate()
{
	return this->predicates[0];
}

string Fact::lastPredicate()
{
	return this->predicates[num_predicates-1];
}

vector<string> Fact::getPredicateVector()
{
	return this->predicates;
}


Fact::~Fact(){}
