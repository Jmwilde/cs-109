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
	cout << "Numner of predicates to look for: " << num_params << endl;


	// Get the first predicate
	string predicate = rule.getPredicate(0);

	// Find query in KB
	auto kb_search = this->kb.find(predicate);
	if(kb_search != kb.end())
	{
		// Found in the KB
		cout << predicate << " found in KB!\n";
		vector<Fact> fact_vect = kb_search->second;

		int pred_index = 0;

		// For each FACT
		for (int i=0; i<fact_vect.size(); i++)
		{
			// Check if the current Fact has the correct # of predicates
			if (fact_vect[i].getNumPredicates() != num_params){
				continue;
			}

			// Make sure filters is empty for each filter call
			vector<string> filters;
			vector<string> last_vals;

			// Get the first value
			string first_value = fact_vect[i].firstPredicate();
			//cout << "First value: " << first_value << endl;

			// Set the first filter value
			filters.push_back(fact_vect[i].lastPredicate());

			// Call the recursive filter
			//cout << "Calling filter() with filter=" << filters.back() << " & value=" << first_value << " from predicate " << rule.getPredicate(pred_index) << endl;
			filter(rule, pred_index+1, filters, num_params, last_vals);
			//cout << "First value:  " << first_value << endl;m

			// May want to move this inside of filter
			// Unless last_vals is always zero if filter didn't find anything?
			for (int i=0; i<last_vals.size(); i++)
			{
				cout << first_value << " : " << last_vals[i] << endl;
			}
		}
	}
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
	} else {
		cout << predicate << " not found in RB!\n";
	}
	cout << "End of executeAnd()" << endl;

}

// Filter needs to know the name of the Rule/Fact to be filtered
// As well as the filter value
// And which position that filter is occupying
// Ex: Parent(John, $B).
// Parent is the query
// John is the value
// John is occupying index 0

void RuleEngine::filter(Rule rule, int pred_index, vector<string> filters, int num_params, vector<string>& last_values)
{
	cout << "Predicate index: " << pred_index << endl;
	cout << rule.getNumPredicates() << endl;
	// Base case
	if (pred_index == rule.getNumPredicates() )
	{
		cout << "Base case!" << endl;
		cout << pred_index << endl;
		return;
	}

	// Search for the predicate in KB
	auto kb_search = this->kb.find(rule.getPredicate(pred_index));
	if(kb_search != kb.end())
	{
		// Found in the KB
		vector<Fact> fact_vect = kb_search->second;
		vector<string> current_filters;
		//vector<string> last_vals;

		// For each FACT
		for (int i=0; i<fact_vect.size(); i++)
		{
			// Check if the current Fact has the correct # of predicates
			if (fact_vect[i].getNumPredicates() != num_params) continue;

			//cout << fact_vect[i].firstPredicate() << " = " << filters.back() << "?\n";

			cout << "The current filter is: " << filters.back() << endl;
			// Collect the filters
			if (fact_vect[i].firstPredicate() == filters.back())
			{
				//cout << fact_vect[i].firstPredicate() << " matches " << filters.back() << endl;
				current_filters.push_back(fact_vect[i].lastPredicate());
				//cout << "Storing " << fact_vect[i].lastPredicate() << " in last_values.\n";
				//last_vals.push_back(fact_vect[i].lastPredicate());
			}
		}

		last_values = current_filters;

		//int next_pred = pred_index+1;

		// For every current_filter value
		for (int i=0; i<current_filters.size(); i++)
		{
			filters.push_back(current_filters[i]);
			filter(rule, pred_index+1, filters, num_params, current_filters);
		}

		// If current_filters is empty
		// It will skip the next recursion
		return;
		
	} else {
		cout << rule.getPredicate(pred_index) << " not found in KB!\n";
	}
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

			int param_var = int('A');

			// Print corresponding list of strings
			int num_elems = fact_vect[i].getNumPredicates();
			for (int j=0; j<num_elems; j++)
			{
				cout << char(param_var) << ": " << fact_vect[i].getPredicate(j) << " ";
				param_var++;
			}
			cout << endl;
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
			//if (rule_vect[i].getNumPredicates() != num_params) continue;

			// Execute the current rule
			cout << "Called execRule\n";
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