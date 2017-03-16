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

int main()
{
  RuleEngine sri; // Declare a new rule engine
  string commandLine;

	cout << "\nWelcome to the Simple Rule Inference Engine!\n";

  // user inputs a command, and hits Enter/Return
  // terminates when user inputs 'x'

  while(commandLine != "x"){
    cout << "\nInput any of the following commands:" << endl;
    cout << "- LOAD 'filename.sri'" << endl;
    cout << "- DUMP 'filename.sri'" << endl;
    cout << "- FACT 'FactName(A,B)'" << endl;
    cout << "- RULE 'RuleName($A,$B)'" << endl;
    cout << "- INFERENCE 'Query($A,$B)'" << endl;
    cout << "- DROP 'Query'" << endl;
    cout << "- Enter 'x' to terminate\n" << endl;
    getline(cin, commandLine);
    if(commandLine == "x") break;
    sri.parseInput(commandLine);
  }

  cout << "\nBye!" << endl;

	return 0;
}
