// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

#ifndef RULE_ENGINE_H
#define RULE_ENGINE_H

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
	void executeRule();
private:
	map<string, string> fact_map;
	map<string, string> rule_map;
};

#endif  // RULE_ENGINE_H