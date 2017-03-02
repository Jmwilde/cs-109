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

	//  User creates & stores some Facts
  sri.parseInput("FACT Fruits(Apple,Orange)");
  sri.parseInput("FACT Meats(Steak,Chicken)");

  //  Then makes a Rule and stores it
  sri.parseInput("RULE Food($X,$Y):- AND Fruits($X,$Y) Meats($X,$Y) Drinks($X,$Y)");

	//  Then Infers the rule!
	sri.inference("Food", 2);

  sri.parseInput("FACT Drinks(Pepsi,MtnDew)");
  sri.parseInput("RULE Food_And_Drink($X,$Y):- OR Food($X,$Y) Drinks($X,$Y)");

	sri.inference("Fruits", 3);

   //sri.dump();
  //  sri.drop();
   sri.dump();

	// Fact fact3("Drinks", drinks);
	// sri.storeFact("Drinks", fact3);

	sri.inference("Food_And_Drink", 2);

  // user inputs a command, and hits Enter/Return

	return 0;
};
