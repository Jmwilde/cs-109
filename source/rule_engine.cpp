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

void printResults(vector<string> results)
{
	char letter = 'A';
	for (int i=0; i<results.size(); i++)
	{
		cout << char(letter) << ":" << results[i];
		if (i+1 != results.size()) cout << ", ";
		letter++;
	}
	cout << endl;
}

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

	//cout << "** Called inference() on " << query << " **\n\n";
	searchKnowledgeBase(query, num_params);
	searchRuleBase(query, num_params);
}

void RuleEngine::executeRule(Rule rule, int num_params)
{
	logical_op_t op = rule.getOp();
	if(op == OR) {
		executeOr(rule, num_params);
	} else if (op == AND) {
		executeAnd(rule, num_params);
	}
	else {
		cout << "Invalid rule. Does not have a proper [OR,AND] operation.\n";
	}
	return;
}

void RuleEngine::executeOr(Rule rule, int num_params)
{
	int num_elems = rule.getNumPredicates();
	//cout << "There are " << num_elems << " predicates in " 
	//<< rule.getName() << ":\n";

	// For each predicate
	for (int i=0; i<num_elems; i++)
	{
		string predicate = rule.getPredicate(i);
		//cout << "- Predicate " << i << ": " << predicate << endl;
		searchKnowledgeBase(predicate, num_params);
		searchRuleBase(predicate, num_params);
	}
	//cout << "Finished executeOr(" << rule.getName() << ")\n";
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

		// Declare variables for filter function
		int pred_index = 0;
		string first_value;
		string filter_value;
		vector<string> next_values;

		// For each FACT
		for (int i=0; i<fact_vect.size(); i++)
		{
			// Check if the current Fact has the correct # of predicates
			if (fact_vect[i].getNumPredicates() != num_params){
				continue;
			}
			// Get intial value
			first_value = fact_vect[i].firstPredicate();
			// Set intial filter value
			filter_value = fact_vect[i].lastPredicate();

			// Call the recursive filter
			vector<string> output;
			filter(rule, pred_index+1, filter_value, num_params, next_values, output);
			// Print out the final results
			char letter = 'A';
			for (int i=0; i<output.size(); i++)
			{
				cout << char(letter) << ":" << first_value << ", " << char(letter+1) << ":" << output[i] << endl;
			}
		}
	}

	// TODO: Get And working for rules!!
	auto rb_search = this->rb.find(predicate);
	if(rb_search != rb.end())
	{
		// Found in the KB
		vector<Fact> fact_vect = kb_search->second;

		int pred_index = 0;

		// For each FACT
		for (int i=0; i<fact_vect.size(); i++)
		{
			// Check if the current Fact has the correct # of predicates
			if (fact_vect[i].getNumPredicates() != num_params){
				continue;
			}
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

void RuleEngine::filter(Rule rule, int pred_index, string filter_value, int num_params, vector<string>& next_values, vector<string>& output)
{
	// Base case
	if (pred_index == rule.getNumPredicates() )
	{
		for (int i=0; i<next_values.size(); i++)
		{
			// Search the output to avoid duplicates
			if (find(output.begin(), output.end(), next_values[i]) != output.end()) continue;
			output.push_back(next_values[i]);
		}
		return;
	}

	// Search for the predicate in KB
	auto kb_search = this->kb.find(rule.getPredicate(pred_index));
	if(kb_search != kb.end())
	{
		// Found in the KB
		vector<Fact> fact_vect = kb_search->second;
		vector<string> current_filters;

		// For each FACT
		for (int i=0; i<fact_vect.size(); i++)
		{
			// Check if the current Fact has the correct # of predicates
			if (fact_vect[i].getNumPredicates() != num_params) continue;

			// Collect the filters for the next round
			if (fact_vect[i].firstPredicate() == filter_value)
			{
				current_filters.push_back(fact_vect[i].lastPredicate());
			}
		}

		// For every current_filter value
		for (int i=0; i<current_filters.size(); i++)
		{
			next_values = current_filters;
			filter(rule, pred_index+1, current_filters[i], num_params, next_values, output);
		}
		return;
	}
}

void RuleEngine::searchKnowledgeBase(string query, int num_params)
{
	//  Look in the KB
	auto kb_search = this->kb.find(query);
	if(kb_search != kb.end())
	{
		// Found in the KB
		vector<Fact> fact_vect = kb_search->second;

		// For each Fact in the vector
		for (int i=0; i<fact_vect.size(); i++)
		{
			// Check if the current Fact has the correct # of predicates
			if (fact_vect[i].getNumPredicates() != num_params) continue;

			// Print corresponding list of strings
			printResults(fact_vect[i].getAllPredicates());
		}
	}
}

void RuleEngine::searchRuleBase(string query, int num_params)
{
	// Look in the RB
	auto rb_search = this->rb.find(query);
	if (rb_search != rb.end())
	{
		// Found in the RB
		vector<Rule> rule_vect = rb_search->second;

		// For each Rule in the vector
		for (int i=0; i<rule_vect.size(); i++)
			executeRule(rule_vect[i], num_params);
	}
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