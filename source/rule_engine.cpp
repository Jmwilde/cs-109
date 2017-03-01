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
}

RuleEngine::RuleEngine(string sri_file)
{
	// Build the KB and RB from the given .sri file
}

RuleEngine::~RuleEngine(){}

void RuleEngine::storeRule(string name, logical_op_t op, vector<string> predicates)
{
	Rule new_rule(name, op, predicates);
	this->rb[name].push_back(new_rule);
}

void RuleEngine::storeFact(string name, vector<string> predicates)
{
	Fact new_fact(name, predicates);
	this->kb[name].push_back(new_fact);
}

void parseInput()
{
	return;
}

void RuleEngine::inference(string query, int num_params)
{
	// TODO: Inference needs to properly format the outputs
	// Like if user says INFERENCE Parent($X, $Y)
	// The output should print X: foo Y: bar
	// And num_params == 2 in this case

	cout << "** Called inference() on " << query << " **\n\n";
	searchKnowledgeBase(query, num_params);
	searchRuleBase(query, num_params);
}

void RuleEngine::executeRule(Rule rule, int num_params)
{
	logical_op_t op = rule.getOp();
	if(op == OR) {
		this->executeOr(rule, num_params);
	} else if (op == AND) {
		this->executeAnd(rule, num_params);
	}
	else {
		cout << "Ivalid rule. Does not have an OR or an AND operation.\n";
	}
	return;
}

void RuleEngine::executeOr(Rule rule, int num_params)
{
	int num_elems = rule.getNumPredicates();
	cout << "There are " << num_elems << " predicates in " 
	<< rule.getName() << ":\n";

	// For each predicate
	for (int i=0; i<num_elems; i++)
	{
		string predicate = rule.getPredicate(i);
		cout << "- Predicate " << i << ": " << predicate << endl;
		searchKnowledgeBase(predicate, num_params);
		searchRuleBase(predicate, num_params);
	}
	cout << "Finished executeOr(" << rule.getName() << ")\n";
	return;
}

void RuleEngine::executeAnd(Rule rule, int num_params)
{
	// Get the first predicate
	string predicate = rule.getPredicate(0);

	// Find query in KB
	auto kb_search = this->kb.find(predicate);
	if(kb_search != kb.end())
	{
		// Found in the KB
		vector<Fact> fact_vect = kb_search->second;

		int filter_count = 0;
		int pred_index = 1;

		// For each FACT
		for (int i=0; i<fact_vect.size(); i++)
		{
			// Check if the current Fact has the correct # of predicates
			if (fact_vect[i].getNumPredicates() != num_params){
				continue;
			}

			// Make sure output is empty for each filter call
			vector<string> output;

			// Set the first output value
			cout << "First output value: " << fact_vect[i].lastPredicate();
			output.push_back(fact_vect[i].lastPredicate());

			// Call the recursive filter
			cout << "Calling first recursive filter on: " << fact_vect[i].getPredicate(pred_index);
			//filter(rule, pred_index, output, num_params, filter_count);
		}
	}
}

// Filter needs to know the name of the Rule/Fact to be filtered
// As well as the filter value
// And which position that filter is occupying
// Ex: Parent(John, $B).
// Parent is the query
// John is the value
// John is occupying index 0

void RuleEngine::filter(Rule rule, int pred_index, vector<string> output, int num_params, int filter_count)
{
	filter_count++;

	// Base case
	if (filter_count == rule.getNumPredicates() )
	{
		cout << "Finished filter execution!\n";
		return;
	}

	string predicate = rule.getPredicate(pred_index);

	// Search for the predicate in KB
	auto kb_search = this->kb.find(predicate);
	if(kb_search != kb.end())
	{
		// Found in the KB
		vector<Fact> fact_vect = kb_search->second;

		vector<string> filters;

		// For each FACT
		for (int i=0; i<fact_vect.size(); i++)
		{
			// Check if the current Fact has the correct # of predicates
			if (fact_vect[i].getNumPredicates() != num_params) continue;

			// Collect the filters
			if (fact_vect[i].firstPredicate() == output.back())
			{
				filters.push_back(fact_vect[i].lastPredicate());
			}
		}

		int next_pred = pred_index+1;

		// For every filter value
		for (int i=0; i<filters.size(); i++)
		{
			output.push_back(filters[i]);
			filter(rule, next_pred, output, num_params, filter_count);
		}
		
	} else {
		cout << predicate << "Not found in KB!\n";
	}
	//return "Done with filter execution!\n";
}

void RuleEngine::searchKnowledgeBase(string query, int num_params)
{
	//  Look in the KB
	auto kb_search = this->kb.find(query);
	if(kb_search != kb.end())
	{
		// Found in the KB
		cout << "Found " << query << " fact in the KB!\n";
		vector<Fact> fact_vect = kb_search->second;

		// For each Fact in the vector
		for (int i=0; i<fact_vect.size(); i++)
		{
			// Check if the current Fact has the correct # of predicates
			if (fact_vect[i].getNumPredicates() != num_params) continue;

			// Print corresponding list of strings
			int num_elems = fact_vect[i].getNumPredicates();
			for (int j=0; j<num_elems; j++)
    			cout << fact_vect[i].getPredicate(j) << endl;
		}
		cout << endl;
	} else cout << query << " fact not found in KB.\n";
}

void RuleEngine::searchRuleBase(string query, int num_params)
{
	// Look in the RB
	auto rb_search = this->rb.find(query);
	if (rb_search != rb.end())
	{
		// Found in the RB
		cout << "Found " << rb_search->first << " rule in the RB!\n";

		vector<Rule> rule_vect = rb_search->second;
		// For each Rule in the vector
		for (int i=0; i<rule_vect.size(); i++)
		{
			// Check if the current Rule has the correct # of predicates
			if (rule_vect[i].getNumPredicates() != num_params) continue;

			// Execute the current rule
			executeRule(rule_vect[i], num_params);
		}
	} else cout << query << " rule not found in RB.\n";
}

void RuleEngine::dump()
{
	return;
}

void RuleEngine::load()
{
	return;
}

void RuleEngine::printKb()
{
	return;
}

void RuleEngine::printRb()
{
	return;
}