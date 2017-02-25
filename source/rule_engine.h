// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

#ifndef RULE_ENGINE_H
#define RULE_ENGINE_H

#include "fact.h"
#include "rule.h"
#include <map>
#include <vector>

using namespace std;

class RuleEngine
{
public:
	RuleEngine();
	RuleEngine(string sri_file);
	~RuleEngine();
	void parseInput();
	void executeRule(Rule& rule);
	void storeRule(string name, Rule rule);
	void storeFact(string name, Fact fact);
	void printKb();
	void printRb();
private:
	void executeOr(Rule& rule);
	void executeAnd(Rule& rule);
	string input;
	map<string, vector<Fact>> kb;
	map<string, vector<Rule>> rb;
};

#endif  // RULE_ENGINE_H