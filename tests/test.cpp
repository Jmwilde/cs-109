// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

// A test file 

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

	vector<string> str1 = {"James", "John"};
	vector<string> str2 = {"Roger", "Albert"};
	vector<string> str3 = {"Allen", "Margret"};

	vector<string> str4 = {"John", "Robert"};
	vector<string> str5 = {"Marry", "Albert"};
	vector<string> str6 = {"Margret", "Robert"};
	vector<string> str7 = {"Margret", "Bob"};

	vector<string> str8 = {"Bob", "Angela"};
	vector<string> str9 = {"Bob", "Joe"};
	vector<string> str10 = {"Robert", "Jack"};

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
	sri.storeRule("Grandfather", AND, rule_preds);

	sri.inference("Grandfather", 2); // The value 2 refers to # of predicates to look for
}

void testExecOr()
{
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

int main(int argc, char const *argv[])
{
	testExecOr();
	testExecAnd();
	return 0;
};