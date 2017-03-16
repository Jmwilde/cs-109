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

// void testStoreAnd()
// {
// 	RuleEngine sri;

// 	// Setup a mapping of each of the rule's predicates
// 	// to it's respective substituion variables
// 	string begin = "A";
// 	string end = "Z";

// 	// This will normally be generated via the parser
// 	// And passed to the storeAnd() function
// 	map<string, vector<string>> variables_map;
// 	variables_map["Apples"] = {"X", "A", "B"};
// 	variables_map["Oranges"] = {"Q", "B", "H"};
// 	variables_map["Bananas"] = {"H", "Z"};

// 	vector<string> str1 = {"Red", "Green", "Pink"};
// 	sri.storeFact("Apples", str1);

// 	vector<string> str2 = {"Orange", "Pink", "Yellow"};
// 	sri.storeFact("Oranges", str2);

// 	vector<string> str3 = {"Yellow", "Green"};
// 	sri.storeFact("Bananas", str3);

// 	vector<string> preds = {"Apples", "Oranges", "Bananas"};
// 	sri.storeRule("Fruits", AND, preds);
// }

void testStoreAnd()
{
	RuleEngine sri;

	// vector<string> str1 = {"Red", "Green", "Pink"};
	// sri.storeFact("Apples", str1);

	// vector<string> str2 = {"Rose", "Green", "Yellow"};
	// sri.storeFact("Apples", str2);

	// vector<string> str3 = {"Pink", "Orange", "Yellow"};
	// sri.storeFact("Oranges", str3);

	// vector<string> str4 = {"Yellow", "Orange", "Green"};
	// sri.storeFact("Oranges", str4);

	// vector<string> str5 = {"Yellow", "Green"};
	// sri.storeFact("Bananas", str5);

	// vector<string> str6 = {"Green", "Gold"};
	// sri.storeFact("Bananas", str6);

	// vector<string> str7 = {"Green", "Gold"};
	// sri.storeFact("Bananas", str7);

	// vector<string> preds = {"Apples", "Oranges", "Bananas"};
	// sri.storeRule("Fruits", AND, preds); // ANDS together 3 facts

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

void testBuildFilterTable()
{
	cout << "Testing BuildFilterTable()\n";
	RuleEngine sri;

	// Setup a mapping of each of the rule's predicates
	// to it's respective substituion variables
	// 	string begin = "A";
	// 	string end = "Z";

	// 	This will normally be generated via the parser
	// 	And passed to the storeAnd() function

	map<string, vector<string>> variables_map;
	variables_map["Apples"] = {"X", "A", "B"};
	variables_map["Oranges"] = {"Q", "B", "H"};
	variables_map["Bananas"] = {"H", "Z"};

	vector<vector<pair<string,int>>> filter_table;
	//filter_table.resize(1);  // Resize allocates space and initializes the space with empty values

	//filter_table.reserve(5);
	//vector<vector<pair<string,int>>> * ptr = filter_table;
	string start = "A";
	string end = "Z";
	sri.buildFilterTable(variables_map, filter_table, start, end);

	// vector<string> str1 = {"Red", "Green", "Pink"};
	// sri.storeFact("Apples", str1);

	// vector<string> str2 = {"Orange", "Pink", "Yellow"};
	// sri.storeFact("Oranges", str2);

	// vector<string> str3 = {"Yellow", "Green"};
	// sri.storeFact("Bananas", str3);

	//vector<string> preds = {"Apples", "Oranges", "Bananas"};
	//sri.storeRule("Fruits", AND, preds);



	return;
}

int main()
{
	cout << "*** Running test file! ***\n";
	testBuildFilterTable();
	//testStoreRule();
	//testStoreAnd();
}
