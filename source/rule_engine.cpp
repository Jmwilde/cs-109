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
#include <sstream>

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

void RuleEngine::storeRule(string name, Rule rule)
{
  this->rb[name].push_back(rule);
}

void RuleEngine::storeFact(string name, Fact fact)
{
	this->kb[name].push_back(fact);
}

void RuleEngine::parseInput(string commandLine, string& name, string& query, string& op, vector<string>& paramVec, vector<string>& predVec)
{
  string pred = "";
  string sriFile = "";
  string temp = "";
  stringstream iss(commandLine);
  getline(iss, name, ' ');
  if(name == "FACT"){
    try{
      if(commandLine.find('(') == -1) throw 0;
      if(commandLine.find(')') == -1) throw 0;
    }catch(int e){
      std::cout << "Invalid command line argument" << std::endl;
    }
    getline(iss, query, '(');
    while(getline(iss, temp, ',')){
      if(temp.back() == ')') temp.pop_back();
      paramVec.push_back(temp);
    }
  }else if(name == "RULE"){
    try{
      if(commandLine.find(":-") == -1) throw 0;
    }catch(int e){
      std::cout << "Invalid command line argument" << std::endl;
    }
    getline(iss, query, ':');
    getline(iss, temp, ' ');
    getline(iss, op, ' ');
    if(op != "OR" && op != "AND") std::cout << "Invalid command line argument" << std::endl;
    while(getline(iss, pred, '(')){
      predVec.push_back(pred);
      iss.putback('(');
      getline(iss, temp, ' ');
      try{
        if(temp.find('(') == -1 || temp.find(')') == -1) throw 0;
      }catch(int e){
        std::cout << "Invalid command line argument" << std::endl;
      }
    }
  }else if(name == "INFERENCE"){
    try{
      if(commandLine.find('(') == -1) throw 0;
      if(commandLine.find(')') == -1) throw 0;
    }catch(int e){
      std::cout << "Invalid command line argument" << std::endl;
    }
    getline(iss, query, '(');
  }else if(name == "LOAD"){
    getline(iss, sriFile);
  }else if(name == "DUMP"){
    getline(iss, sriFile);
  }else if(name == "DROP"){
    getline(iss, pred);
  }
  return;
}

void RuleEngine::inference(string query, int num_params)
{
	// Inference needs to know what parameter letters to print out
	// Like if user says INFERENCE Parent($X, $Y)
	// The output should print X: foo Y: bar
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
	cout << "There are " << num_elems << " predicates in " << rule.getName() << ":\n";

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
	cout << "Called executeAnd() method.\n";

	return;
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
			// Check if the current Fact has the correct number of predicates
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
			// Check if the current Rule has the correct number of predicates
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
