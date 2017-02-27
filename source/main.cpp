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
	Fact fact1("Fruits", fruits);
	Fact fact2("Meats", meats);
	sri.storeFact("Fruits", fact1);
	sri.storeFact("Meats", fact2);

  //  Then makes a Rule and stores it
  Rule rule1("Food", AND, foods);
  sri.storeRule("Food", rule1);

	//  Then Infers the rule!
	sri.inference("Food", 2);

  Fact fact3("Drinks", drinks);
  sri.storeFact("Drinks", fact3);

	Rule rule2("Food and Drink", AND, food_and_drink);
	sri.storeRule("Food and Drink", rule2);

	sri.inference("Food and Drink", 2);

  sri.parseInput("RULE Parent:- OR Father(x,y) Mother(x,y)");
  sri.parseInput("FACT Father(John,Bob)");

  // user inputs a command, and hits Enter/Return

  // the line of text is passed to the parseInput() method

  // sri.parseInput()

  return 0;
};
