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

// template <typename ...ArgsT>
// Fact::Fact(ArgsT ...strings)
// {
//     Fact({strings...});
// }

Fact::Fact(vector<string> predicates) : Command("FACT")
{
	this->num_predicates = predicates.size();
	this->predicates = predicates; // copy by value??
}

int Fact::getNumPredicates()
{
	return this->num_predicates;
}

string Fact::getPredicate(const int index)
{
    return this->predicates[index];
}

Fact::~Fact(){}