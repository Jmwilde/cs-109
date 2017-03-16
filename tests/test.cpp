// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

// The testing file

#include "../source/rule_engine.h"

#include <vector>
#include <string>
#include <iostream>
#include <map>

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

	vector<string> str8 = {"John", "Joe", "Margret"};
	sri.storeFact("Father", str8);

	vector<string> str9 = {"Jim", "Jeff", "George"};
	sri.storeFact("Father", str9);

	vector<string> str10 = {"George", "Kim", "Joanne"};
	sri.storeFact("Mother", str10);

	vector<string> str11 = {"Margret", "Marry", "Julia"};
	sri.storeFact("Mother", str11);

	vector<string> str12 = {"Margret", "Marry", "Bob"};
	sri.storeFact("Mother", str12);

	vector<string> str13 = {"Julia", "Marry", "Smith"};
	sri.storeFact("Child", str13);

	vector<string> str14 = {"Bob", "Marry", "Beastmode!"};
	sri.storeFact("Child", str14);

	vector<string> str15 = {"Father", "Mother"};
	sri.storeRule("Parent", OR, str15);

	vector<string> preds2 = {"Father", "Parent", "Child"};
	sri.storeRule("Grandfather", AND, preds2); // ANDS together 3 facts

}

int main()
{
	cout << "*** Running test file! ***\n";
	//testStoreRule();
	//testStoreAnd();
}
