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
#include <fstream>

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

void RuleEngine::inference(string query, int num_params)
{
	//  Look in the KB
	auto kb_search = this->kb.find(query);
	if(kb_search != kb.end())
	{
		// Found in the KB
		cout << "Found " << kb_search->first << " in the KB!\n";
		vector<Fact> fact_vect = kb_search->second;

		// NOTE: Need to check if Fact has proper number of predicates
		// Should match the number of ($X, $Y, etc.) given by user

		// For each Fact in the vector
		for (int i=0; i<fact_vect.size(); i++)
		{
			// Check if the current Fact has the correct number of predicates
			if (fact_vect[i].getNumPredicates() != num_params) continue;

			// Print corresponding list of strings
			int num_elems = fact_vect[i].getNumPredicates();
			for (int j=0; j<num_elems; j++)
    			cout << fact_vect[i].getPredicate(j) << endl;
		}
		cout << endl;
	} else cout << query << " query not found in KB.\n";

	// Look in the RB
	auto rb_search = this->rb.find(query);
	if (rb_search != rb.end())
	{
		// Found in the RB
		cout << "Found " << rb_search->first << " in the RB!\n";

		vector<Rule> rule_vect = rb_search->second;
		// For each Rule in the vector
		for (int i=0; i<rule_vect.size(); i++)
		{
			// Check if the current Rule has the correct number of predicates
			if (rule_vect[i].getNumPredicates() != num_params) continue;

			// Execute the current rule
			executeRule(rule_vect[i], num_params);
		}
	} else cout << query << " query not found in RB.\n";
}

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

void RuleEngine::executeRule(Rule rule, int num_params)
{
	logical_op_t op = rule.getOp();

	// Check whether it is an AND or an OR rule
	if(op == OR) {
		cout << "Executing the OR operation on " << rule.getName() << "!\n";
		this->executeOr(rule, num_params);
	} else if (op == AND) {
		cout << "Executing the AND operation on "<< rule.getName() << "!\n";
		this->executeAnd(rule, num_params);
	}
	else {
		// Print error message
		cout << "Deez nutz!\n";
		cout << rule.getName() << " not an OR or an AND!\n";
	}
	return;
}

void RuleEngine::executeOr(Rule rule, int num_params)
{
	cout << "Called executeOr() method on << " << rule.getName() << "\n";
	int num_elems = rule.getNumPredicates();
	cout << "There are " << num_elems << " predicates in this " << rule.getName() << "\n";

	// For each predicate
	for (int i=0; i<num_elems; i++)
	{
		string predicate = rule.getPredicate(i);
		cout << "Predicate " << i << ": " << predicate << endl;

		// Look in the KB
		auto kb_search = this->kb.find(predicate);
		if( kb_search != kb.end() )
		{

			// Found in the KB
			cout << "Found " << kb_search->first << " in the KB!\n";
			vector<Fact> fact_vect = kb_search->second;

			// For each Fact in the vector
			for (int i=0; i<fact_vect.size(); i++)
			{
				// Check if the current Fact has the correct number of predicates
				if (fact_vect[i].getNumPredicates() != num_params) continue;

				int num_elems = fact_vect[i].getNumPredicates();

				// Print out the values
				for (int j=0; j<num_elems; j++)
    				cout << fact_vect[i].getPredicate(j) << endl;
			}
		} else cout << predicate << " not found in KB.\n";

		// Look in the RB
		auto rb_search = this->rb.find(predicate);
		if (rb_search != rb.end())
		{
			// Found in the RB
			cout << "Found " << rb_search->first << " in the RB!\n";
			vector<Rule> rule_vect = rb_search->second;

			// For each rule in the vector
			for (int i=0; i<rule_vect.size(); i++)
			{
				int num_elems = rule_vect[i].getNumPredicates();
				for (int j=0; j<num_elems; j++)
				{
					cout << "Recursive execution called on: " << rule_vect[i].getName() << endl;
    				executeRule(rule_vect[j], num_params);
    			}
			}
		} else cout << predicate << " not found in RB.\n";
	}
	cout << "Finished executeOr(" << rule.getName() << ")\n";
	return;
}

void RuleEngine::executeAnd(Rule rule, int num_params)
{
	cout << "Called executeAnd() method.\n";
	return;
}

// Store the KB and RB info
// into a text file (.sri)

void RuleEngine::load()
{
	return;
}

void RuleEngine::printKb()
{

}

void RuleEngine::printRb()
{

}
void RuleEngine::dump()
{
   string filename;
   cout << "Insert a file name 'filename.sri'" << endl;
   cin >> filename;
   ofstream ofile (filename);
   for(map<string, vector<Fact>>::iterator it = kb.begin(); it!=kb.end(); ++it)
   {
      ofile << "FACT " << it->first << "(";
      vector<Fact> facts = kb[it->first];
      for(uint y = 0; y<facts.size();y++)
      {
         int preds = facts[y].getNumPredicates();
         for(int z = 0; z<preds;z++)
         {
            if(z + 1 == preds)
            {
               ofile << facts[y].getPredicate(z);
               break;
            }
            ofile << facts[y].getPredicate(z) << ", ";
         }
         ofile << ")" << endl;
      }
   }
   for(map<string, vector<Rule>>::iterator it = rb.begin(); it!= rb.end(); ++it)
   {
      ofile << "RULE " << it->first << "(";
      vector<Rule> rules = rb[it->first];
      for(uint y = 0; y<rules.size();y++)
      {
         int preds = rules[y].getNumPredicates();
         for(int z = 0; z<preds;z++)
         {
            if(z + 1 == preds)
            {
               ofile << rules[y].getPredicate(z);
               break;
            }  
            ofile << rules[y].getPredicate(z) << ", ";
         }
         ofile << ")" << endl;
      }
   }
   ofile.close();
}
