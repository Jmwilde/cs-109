// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

// The testing file

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "../source/rule_engine.h"
#include "../source/fact.h"
#include "../source/rule.h"

using namespace std;

void testExecAnd()
{
	cout << "Testing AND execution!\n";
	RuleEngine sri;

	/* This test stores 3 types of facts into the KB
	and then calls inference on the Grandfather rule 
	that ANDs the facts together. Notice how this tests 
	whether both whether James and Allen will be the 
	intial LHS values and it tests whether Margret 
	will filter to both Bob and Robert, and all three
	filter down to Angela, Joe, and Jack. I added an
	additinal Child fact that is non-related to make
	sure it was not simply printing all the end results
	of the Child key in the KB. This proves the 
	algorithm for AND on factsworks for Rules with 
	more than two parameters. */ 

	vector<string> str1 = {"James", "John"};
	vector<string> str2 = {"Roger", "Albert"};
	vector<string> str3 = {"Allen", "Margret"};
	vector<string> str4 = {"John", "Richard"};
	vector<string> str5 = {"Marry", "Albert"};
	vector<string> str6 = {"Margret", "Robert"};
	vector<string> str7 = {"Margret", "Bob"};
	vector<string> str8 = {"Bob", "Angela"};
	vector<string> str9 = {"Robert", "Joe"};
	vector<string> str10 = {"Richard", "Jack"};
	vector<string> str11 = {"Kethaniel", "Tako"};
	vector<string> rule_preds = {"Father", "Parent", "Child"};

	sri.storeFact("Father", str1);
	sri.storeFact("Father", str2);
	sri.storeFact("Father", str3);
	sri.storeFact("Parent", str4);
	sri.storeFact("Parent", str5);
	sri.storeFact("Parent", str6);
	sri.storeFact("Parent", str7);
	sri.storeFact("Child", str8);
	sri.storeFact("Child", str9);
	sri.storeFact("Child", str10);
	sri.storeFact("Child", str11);
	sri.storeRule("Grandfather", AND, rule_preds);
	// The value 2 refers to # of predicates to look for
	// in each fact.
	sri.inference("Grandfather", 2);
}

void testExecOr()
{
	/* This is a simple test of the executeOR() function.
	It tests whether the Parent OR rule, not stored as a
	Fact in the KB, but as a Rule in the RB will still
	successfully print out all Facts pointed to by the keys
	"Father" and "Mother". */

	RuleEngine sri;
	cout << "Testing OR execution!\n";
	vector<string> str1 = {"James", "John"};
	vector<string> str2 = {"Roger", "Albert"};
	vector<string> str3 = {"Allen", "Margret"};
	vector<string> str4 = {"Mickey", "John"};
	vector<string> str5 = {"Marry", "Albert"};
	vector<string> str6 = {"Margret", "Robert"};
	vector<string> str7 = {"Margret", "Bob"};
	vector<string> rule_preds = {"Father", "Mother"};
	sri.storeFact("Father", str1);
	sri.storeFact("Father", str2);
	sri.storeFact("Father", str3);
	sri.storeFact("Mother", str4);
	sri.storeFact("Mother", str5);
	sri.storeFact("Mother", str6);
	sri.storeFact("Mother", str7);
	sri.storeRule("Parent", OR, rule_preds);
	sri.inference("Parent", 2);
}

int main()
{
	testExecOr();
	testExecAnd();
	return 0;
}
