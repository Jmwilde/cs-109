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

#include "../headers/rule_engine.h"
#include "../headers/fact.h"
#include "../headers/rule.h"

using namespace std;

int main()
{
  RuleEngine sri; // Declare a new rule engine
  string commandLine;

	cout << "\nWelcome to the Simple Rule Inference Engine!\n";

  // user inputs a command, and hits Enter/Return
  // terminates when user inputs 'x'

  // while(commandLine != "x"){
  //   cout << "\nInput any of the following commands:" << endl;
  //   cout << "- LOAD 'filename.sri'" << endl;
  //   cout << "- DUMP 'filename.sri'" << endl;
  //   cout << "- FACT 'FactName(A,B)'" << endl;
  //   cout << "- RULE 'RuleName($A,$B)'" << endl;
  //   cout << "- INFERENCE 'Query($A,$B)'" << endl;
  //   cout << "- DROP 'Query'" << endl;
  //   cout << "- Enter 'x' to terminate\n" << endl;
  //   getline(cin, commandLine);
  //   if (commandLine == "")
  //   {
  //     continue;
  //   }
  //   if(commandLine == "x") break;
  //   sri.parseInput(commandLine);
  // }

  commandLine = "LOAD test.sri";
  sri.parseInput(commandLine);

  commandLine = "INFERENCE STAR($X,$Y)";
  sri.parseInput(commandLine);
  cout << endl;

  commandLine = "INFERENCE STAAR($X,$Y)";
  sri.parseInput(commandLine);
  cout << endl;

  cout << "\nBye!" << endl;

	return 0;
}
