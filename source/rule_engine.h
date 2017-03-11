// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

#ifndef RULE_ENGINE_H
#define RULE_ENGINE_H

#include "helpStoreOr.h"
#include "fact.h"
#include "rule.h"
#include "thread.h"
#include <map>
#include <vector>

using namespace std;

class RuleEngine
{
public:
	RuleEngine();
	RuleEngine(string sri_file);
	~RuleEngine();
	void printRb(string name);
	bool inKB(string name);
	bool inRB(string name);
	void storeOr(string rule_name, vector<string> predicates);
	//void storeAnd(string rule_name, logical_op_t op, vector<string> predicates);
	void parseInput(string commandLine);
	void inference(string query, int num_predicates);
	void inference(string query, int num_predicates, string name);
	void storeRule(string rule_name, logical_op_t op, vector<string> predicates);
	void storeValues(string rule_name, logical_op_t op, vector<string> predicate_names, string predicate);
	void storeFact(string name, vector<string> predicates);
	void dump(string input);
	void load(string testFile);
   	void drop(string input);
	void printKb();
	void printRb();
	void printResults(vector<string> results);
	void filter(Rule rule, int pred_index, string filter_value, int num_params, vector<string>& last_values, vector<string>& output);
private:
	void searchKnowledgeBase(string query, int num_params, bool add, string name);
	void searchRuleBase(string query, int num_params, bool add, string name);
   void storeHelper(string rule_name, vector<string> predicates);
	//void executeRule(Rule rule, int num_params, bool add, string name);
	//void executeOr(Rule rule, int num_params, bool add, string name);
	//void executeAnd(Rule rule, int num_params, bool add, string name);
	map<string, vector<Fact>> kb;
	map<string, vector<Rule>> rb;
};

#endif  // RULE_ENGINE_H
