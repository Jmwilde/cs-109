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
	void parseInput(string commandLine);
	void inference(string query, int num_predicates);
	void inference(string query, int num_predicates, string name);
	void storeRule(string name, logical_op_t op, vector<string> predicates);
	void storeFact(string name, vector<string> predicates);
	void dump(string input);
	void load(string testFile);
   void drop(string input);
	void printKb();
	void printRb();
	void filter(Rule rule, int pred_index, vector<string> output, int num_params, vector<string>& last_values);
private:
	void searchKnowledgeBase(string query, int num_params, bool add, string name);
	void searchRuleBase(string query, int num_params, bool add, string name);
	void executeRule(Rule rule, int num_params, bool add, string name);
	void executeOr(Rule rule, int num_params, bool add, string name);
	void executeAnd(Rule rule, int num_params, bool add, string name);
	string input;
	map<string, vector<Fact>> kb;
	map<string, vector<Rule>> rb;
};

#endif  // RULE_ENGINE_H
