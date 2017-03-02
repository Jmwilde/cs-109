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

void testEdgeCases();

int main(int argc, char const *argv[])
{
	//RuleEngine sri; // Declare a new rule engine

	cout << "Welcome to the Simple Rule Inference Engine!\n";
	cout << "Please input a command.\n\n";

	testEdgeCases();

	// user inputs a command, and hits Enter/Return

	// the line of text is passed to the parseInput() method

	// sri.parseInput()

	return 0;
};

void testEdgeCases(){

	RuleEngine sri;
	cout << "Testing edge cases" << endl;

	sri.load("testcase1.sri");
	sri.inference("GrandFather", 2, "GF");
	//sri.printKb();
	//sri.printRb();
	sri.dump();
}
