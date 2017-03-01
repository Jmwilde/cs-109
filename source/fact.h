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

{
public:
	~Fact();
	int getNumPredicates();
	string getPredicate(const int index);
private:
	int num_predicates;
	vector<string> predicates;
};

#endif  // FACT_H
