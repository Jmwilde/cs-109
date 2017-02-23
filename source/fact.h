// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

#ifndef FACT_H
#define FACT_H

#include <vector>
#include <string>

using namespace std;

// Each fact holds a vector of its predicates that it relates to

// Construct a Fact by passing a vector holding its predicates

class Fact
{
public:
	Fact(vector<string> predicates);
	~Fact();
private:
	int num_predicates;
	vector<string> predicates;
};

#endif  // FACT_H
