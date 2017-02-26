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
#include <vector>
#include <iostream>

using namespace std;

RuleEngine::RuleEngine()
{
	// Initializes an empty rule engine
	// Map the name of fact objects to their values
	map<string, vector<Fact>> kb; // Knowledge Base
	map<string, vector<Rule>> rb; // Rule Base

	// Could set a size for the kb and rb here!
}

RuleEngine::RuleEngine(string sri_file)
{
	// Build the KB and RB from the given .sri file
}

RuleEngine::~RuleEngine(){}

void RuleEngine::storeRule(string name, Rule rule)
{
	this->rb[name].push_back(rule);
}

void RuleEngine::storeFact(string name, Fact fact)
{
	this->kb[name].push_back(fact);
}

void parseInput()
{
	return;
}

void RuleEngine::executeRule(Rule& rule)
{
	// Check whether it is an AND or an OR operation
	logical_op_t op = rule.getOp();

	if(op == OR) {
		cout << "Executing the OR operation!\n";
		this->executeOr(rule);
	} else if (op == AND) {
		cout << "Executing the AND operation!\n";
		this->executeAnd(rule);
	}
	else
		// Print error message
		cout << "Deez nutz!\n";
	return;
}

// TODO: implement executeAnd
// TODO: test functionality of executeOr

void RuleEngine::executeOr(Rule& rule)
{
	cout << "Called executeOr() method.\n";
	int num_elems = rule.getNumPredicates();

	cout << "There are " << num_elems << " predicates in this rule.\n";

	for (int i=0; i<num_elems; i++)  // Examine each predicate
	{
		string predicate = rule.getPredicate(i);
		cout << "Predicate " << i << ": " << predicate << endl;

		// Look in the KB, then in the RB
		auto kb_search = this->kb.find(predicate);
		cout << kb_search->first;
		if( kb_search != kb.end() )
		{
			// Found in the KB
			cout << "Found " << kb_search->first << " in the KB!\n";
			vector<Fact> v = kb_search->second;

			// NOTE: Need to check if Fact has proper number of predicates
			// Should match the number of ($X, $Y, etc.) given by user

			// For each Fact in the vector
			// Print corresponding list of strings

			for (int i=0; i<v.size(); i++)
			{
				int num_elems = v[i].getNumPredicates();
				for (int j=0; j<num_elems; j++)
    				cout << v[i].getPredicate(j) << endl;
			}
		} else cout << kb_search->first << " not found in KB.\n";

		auto rb_search = this->rb.find(predicate);
		if (rb_search != rb.end())
		{
			// Found in the RB
			cout << "Found " << rb_search->first << " in the RB!\n";
			vector<Rule> v = rb_search->second;

			// For each associated Rule,
			// call executeRule on each of the associated predicates

			// Will this iterate past the desired elements??
			// I think it might
			for (int i=0; i<v.size(); i++)
			{
				int num_elems = v[i].getNumPredicates();
				for (int j=0; j<num_elems; j++)
    				executeRule(v[j]);
			}
		} else cout << predicate << " not found in RB.\n";
	}
	return;
}

void RuleEngine::executeAnd(Rule& rule)
{
	cout << "Called executeAnd() method.\n";

	return;
}

void RuleEngine::printKb()
{

}

void RuleEngine::printRb()
{

}
