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

	vector<string> predicates = {"Apple", "Orange", "Banana"};

	Rule rule(OR, predicates);
	Fact fact(predicates);
	//Fact fact("Apple", "Orange", "Banana");

	sri.storeFact("Fruits", fact);
	sri.storeRule("Fruits", rule);
	//Rule r1(AND, p);
	sri.executeRule(rule);
	//sri.executeRule(r1);


	// user inputs a command, and hits Enter/Return

	// the line of text is passed to the parseInput() method

	// sri.parseInput()

	return 0;
};


