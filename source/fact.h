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

class Fact
{
public:
	Fact(string name, vector<string> predicates);
	~Fact();
	int getNumPredicates();
	string getPredicate(int index);
	string firstPredicate();
	string lastPredicate();
	vector<string> getAllPredicates();
private:
	string name;
	int num_predicates;
	vector<string> predicates;
};

#endif  // FACT_H
