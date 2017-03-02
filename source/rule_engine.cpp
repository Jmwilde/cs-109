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

void RuleEngine::parseInput(string commandLine)
{
	string name = "";
	string query = "";
	string stringOp = "";
  string pred = "";
  string sriFile = "";
  string temp = "";
	logical_op_t op;
	vector<string> paramVec;
	vector<string> predVec;
  stringstream iss(commandLine);
  getline(iss, name, ' ');
  if(name == "FACT"){
    try{
      if(commandLine.find('(') == -1) throw 0;
      if(commandLine.find(')') == -1) throw 0;
    }catch(int e){
      cout << "Error: Invalid command line argument" << endl;
    }
    getline(iss, query, '(');
    while(getline(iss, temp, ',')){
      if(temp.back() == ')') temp.pop_back();
      paramVec.push_back(temp);
    }
		this->storeFact(query, paramVec);
  }else if(name == "RULE"){
    try{
      if(commandLine.find(":-") == -1) throw 0;
    }catch(int e){
      cout << "Error: Invalid command line argument" << endl;
    }
    getline(iss, query, '(');
    getline(iss, temp, ' ');
    getline(iss, stringOp, ' ');
    if(stringOp == "OR") op = OR;
		else if(stringOp == "AND") op = AND;
		else cout << "Error: Invalid command line argument" << endl;
    while(getline(iss, pred, '(')){
      predVec.push_back(pred);
      iss.putback('(');
      getline(iss, temp, ' ');
      try{
        if(temp.find('(') == -1 || temp.find(')') == -1) throw 0;
      }catch(int e){
        cout << "Error: Invalid command line argument" << endl;
      }
    }
		this->storeRule(query, op, predVec);
  }else if(name == "INFERENCE"){
    try{
      if(commandLine.find('(') == -1) throw 0;
      if(commandLine.find(')') == -1) throw 0;
    }catch(int e){
      cout << "Error: Invalid command line argument" << endl;
    }
    getline(iss, query, '(');
		this->inference(query, 2);
  }else if(name == "LOAD"){
    getline(iss, sriFile, ' ');
		this->load(sriFile);
  }else if(name == "DUMP"){
    getline(iss, sriFile, ' ');
		this->dump(sriFile);
  }else if(name == "DROP"){
    getline(iss, pred, ' ');
		this->drop(pred);
  }else{
		cout << "\nError: Invalid command line argument" << endl;
	}
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
	cout << pred_index << endl;
	cout << rule.getNumPredicates() << endl;
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

void RuleEngine::load(string testFile)
{
	string line;
	ifstream sriFile(testFile);
	if(sriFile.is_open()){
		while(getline(sriFile, line)){
			parseInput(line);
		}
		sriFile.close();
	}else{
		cout << "\nError: Unable to open file" << endl;
	}
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

void RuleEngine::drop(string input)
{
   string tbd = input;
   //cout << "Name of fact/rule to drop?" <<endl;
   //cin >> tbd;
   kb.erase(tbd);
   rb.erase(tbd);
}

void RuleEngine::dump(string input)
{
   string filename = input;
   string prev;
   //cout << "Insert a file name 'filename.sri'" << endl;
   //cin >> filename;
   ofstream ofile (filename);
   for(map<string, vector<Fact>>::iterator it = kb.begin(); it!=kb.end(); ++it)//Iterating through KB
   {
      vector<Fact> facts = kb[it->first];
      for(uint i = 0; i<facts.size();i++)
      {
         ofile << "FACT " << it->first << "(";
         int preds = facts[i].getNumPredicates();
         for(int j = 0; j<preds;j++)
         {
            if(j + 1 == preds)
            {
               ofile << facts[i].getPredicate(j);
               break;
            }
            ofile << facts[i].getPredicate(j) << ",";
         }
         ofile << ")" << endl;
      }
   }
   for(map<string, vector<Rule>>::iterator it = rb.begin(); it!= rb.end(); ++it) //Iterating through RB
   {
      vector<Rule> rules = rb[it->first];
      for(uint i = 0; i<rules.size();i++)
      {
         if (it->first == prev){//checking for duplicate rule names
            ofile << endl;
         }
         ofile << "RULE " << it->first << "("; //it->first is the key/string vector name
         int preds = rules[i].getNumPredicates();
         string oper;
         int ascii = 65;
         int asciii = 67;

         if( rules[i].getOp() == 0){ //checking for operator enum
            oper = "OR";
            ofile << "$" << (char)ascii << ",$" << (char)(ascii+preds-1) << "):- " << oper << " ";
         }
         else{
            oper = "AND";
            ascii = 65;
            if(preds == 2)
            {
               ofile << "$" << (char)ascii << ",$" << (char)(ascii+preds-1) << "):- " << oper << " ";
            }
            else{
               ofile << "$" << (char)ascii << ",$" << (char)(ascii+preds) << "):- " << oper << " ";
            }
         }
         ascii = 65;
         for(int j = 0; j<preds; j++) //iterating for OR Rules
         {
            if(oper == "OR")
            {
               ofile << rules[i].getPredicate(j)<< "(";
               ascii = 65;
               for(int k = 0; k<preds; k++)
               {
                  if(k + 1 == preds)
                  {
                     ofile << "$" << (char)ascii << ") "; // There is a space "($X) "<here
                     break;
                  }
                  ofile << "$" << (char)ascii <<  ",";
                  ascii++;
               }
            }
            else
            {
               ascii = 65;
               for(int j = 0; j<preds; j++)//iterate for AND Rules
               {
                  ofile << rules[i].getPredicate(j) << "(";
                  ofile << "$" << (char)ascii << ",$" << (char)asciii << ") ";
                  ascii++;
                  j++;
                  if(j == preds)
                  {
                     break;
                  }
                  else
                  {
                     ofile << rules[i].getPredicate(j) << "(";
                     ofile << "$" << (char)asciii << ",$" << (char)ascii << ") ";
                     asciii++;
                  }
               }
               break;
            }
          }
            prev = it->first; //prev storing previous rule name
      }
      ofile << endl;
   }
   ofile.close();
}
