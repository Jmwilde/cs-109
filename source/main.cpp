// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "rule_engine.h"
#include "fact.h"
#include "rule.h"

using namespace std;

int main(int argc, char const *argv[])
{
	RuleEngine sri; // Declare a new rule engine

	cout << "Welcome to the Simple Rule Inference Engine!\n";
	cout << "Please input a command.\n\n";
	vector<string> fruits = {"Apple", "Orange"};
	vector<string> meats = {"Steak", "Chicken"};
	vector<string> foods = {"Fruits", "Meats"};
	vector<string> drinks = {"Pepsi", "Mtn Dew"};
	vector<string> food_and_drink {"Food", "Drinks"};

	//  User creates & stores some Facts
	sri.storeFact("Fruits", fruits);
	sri.storeFact("Meats", meats);

	//  Then makes a Rule and stores it
	sri.storeRule("Food", OR, foods);

	//  Then Infers the rule!
	sri.inference("Food", 2);

	sri.storeFact("Drinks", drinks);

	cout << "\nBeginning 2nd Test!\n\n";

	sri.storeRule("Food and Drink", OR, food_and_drink);

	sri.inference("Food and Drink", 2);

	// user inputs a command, and hits Enter/Return

	// the line of text is passed to the parseInput() method

	return 0;
}
