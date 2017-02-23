// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

#include "fact.h"
#include "rule.h"
#include "rule_engine.h"
#include <map>

using namespace std;

RuleEngine::RuleEngine()
{
	// Initializes an empty rule engine
	// Map the name of fact objects to their values
	map<string, string> fact_map;
	map<string, string> rule_map;
}

RuleEngine::RuleEngine(string sri_file)
{
	// Build the KB and RB from the given .sri file
}

RuleEngine::~RuleEngine(){}

