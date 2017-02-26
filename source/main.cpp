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
	cout << "Please input a command.\n";

	vector<string> fruits = {"Apple", "Orange", "Banana"};
	vector<string> meats = {"Steak", "Chicken", "Pork", "Lizard"};
	vector<string> foods = {"Fruits", "Meats"};
	vector<string> food_and_drink {"Food", "Drinks"};

	//  User creats & stores some Facts
	Fact fact1("Fruits", fruits);
	Fact fact2("Meats", meats);
	sri.storeFact("Fruits", fact1);
	sri.storeFact("Meats", fact2);

	//  Then makes a Rule and stores it
	Rule rule1("Food", OR, foods);
	sri.storeRule("Food", rule1);

	//  Then Infers the rule!
	sri.executeRule(rule1);

	vector<string> drinks = {"Pepsi", "Mtn Dew", "Coke"};
	Fact fact3("Drinks", drinks);
	sri.storeFact("Drinks", fact3);

	cout << "\nBeginning 2nd Test!\n\n";

	Rule rule2("Food and Drink", OR, food_and_drink);
	sri.storeRule("Food and Drink", rule2);
	
	sri.executeRule(rule2);

	// user inputs a command, and hits Enter/Return

	// the line of text is passed to the parseInput() method

	// sri.parseInput()

	return 0;
};
