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

void testStoreAnd()
{
	RuleEngine sri;

	// Setup a mapping of each of the rule's predicates
	// to it's respective substituion variables
	string begin = "A";
	string end = "Z";

	// This will normally be generated via the parser
	// And passed to the storeAnd() function
	map<string, vector<string>> variables_map;
	variables_map["Apples"] = {"X", "A", "B"};
	variables_map["Oranges"] = {"Q", "B", "H"};
	variables_map["Bananas"] = {"H", "Z"};

	vector<string> str1 = {"Red", "Green", "Pink"};
	sri.storeFact("Apples", str1);

	vector<string> str2 = {"Orange", "Pink", "Yellow"};
	sri.storeFact("Oranges", str2);

	vector<string> str3 = {"Yellow", "Green"};
	sri.storeFact("Bananas", str3);

	vector<string> preds = {"Apples", "Oranges", "Bananas"};
	sri.storeRule("Fruits", AND, preds);
}

int main()
{
	cout << "*** Running test file! ***\n";
	testStoreRule();
}
