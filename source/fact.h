<<<<<<< HEAD
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
#include "command.h"

using namespace std;

// Each fact holds a vector of its predicates that it relates to

// Construct a Fact by passing a vector holding its predicates
//template <typename ...ArgsT>
class Fact: public Command
{
public:
	//template <typename ...ArgsT>
	//Fact(ArgsT ...strings);
	Fact(vector<string> predicates);
	~Fact();
	int getNumPredicates();
	string getPredicate(const int index);
private:
	Fact(initializer_list<string> strings);
	int num_predicates;
	vector<string> predicates;
};

#endif  // FACT_H
=======
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
	string getPredicate(const int index);
private:
	string name;
	int num_predicates;
	vector<string> predicates;
};

#endif  // FACT_H
>>>>>>> origin/john
