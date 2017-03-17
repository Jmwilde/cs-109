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
	Fact(string name, vector<string> values);
	~Fact();
	int getNumValues();
	string getValue(int index);
	string firstValue();
	string lastValue();
	vector<string> getValueVector();
private:
	string name;
	int num_values;
	vector<string> values;
};

#endif  // FACT_H
