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

void testStoreRule()
{
	RuleEngine sri; // Declare a new rule engine

	vector<string> str1 = {"Sally", "Annie"};
	sri.storeFact("Mother", str1);

	vector<string> str2 = {"Joe", "Bob"};
	sri.storeFact("Father", str2);

	vector<string> preds = {"Mother", "Father"};
	sri.storeRule("Parent", OR, preds);

	sri.printRb("Parent");
}

int main()
{
	cout << "*** Running test file! ***\n";
	testStoreRule();
}
