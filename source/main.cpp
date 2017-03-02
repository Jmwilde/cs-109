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
  string commandLine;

	cout << "Welcome to the Simple Rule Inference Engine!\n";
	cout << "Please input a command.\n\n";

  // user inputs a command, and hits Enter/Return
  // terminates when user inputs 'x'


  while(commandLine != "x"){
    cin >> commandLine;
    sri.parseInput(commandLine);
  }

	return 0;
};
