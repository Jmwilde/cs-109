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
	if(rb.find(name) != rb.end())
	{
		vector<Rule> temp = rb[name];
		for(vector<Rule>::iterator iter = temp.begin();iter != temp.end(); iter++)
		{
			if(iter->getPredicateVector() == predicates)
			{
				cout << "Input is duplicate" << endl;
				return;
			}
		}
	}
	this->rb[name].push_back(new_rule);
}

void RuleEngine::storeFact(string name, vector<string> predicates)
{
	Fact new_fact(name, predicates);
	if(kb.find(name) != kb.end())
	{
		vector<Fact> temp = kb[name];
		for(vector<Fact>::iterator iter = temp.begin();iter != temp.end(); iter++)
		{
			if(iter->getPredicateVector() == predicates)
			{
				cout << "Input is duplicate" << endl;
				return;
			}
		}
	}
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
	// TODO: Inference needs to properly format the outputs
	// Like if user says INFERENCE Parent($X, $Y)
	// The output should print X: foo Y: bar
	// And num_params == 2 in this case

	cout << "** Called inference() on " << query << " **\n\n";
	searchKnowledgeBase(query, num_params, false, "");
	searchRuleBase(query, num_params, false, "");
}

void RuleEngine::inference(string query, int num_params, string name)
{
	cout << "** Called inference() on " << query << " **\n\n";
	searchKnowledgeBase(query, num_params, true, name);
	searchRuleBase(query, num_params, true, name);
}


void RuleEngine::executeRule(Rule rule, int num_params, bool add, string name)
{
	logical_op_t op = rule.getOp();
	if(op == OR) {
		executeOr(rule, num_params, add, name);
	} else if (op == AND) {
		executeAnd(rule, num_params, add, name);
	}
	else {
		cout << "Invalid rule. Does not have a proper [OR,AND] operation.\n";
	}
	return;
}

void RuleEngine::executeOr(Rule rule, int num_params, bool add, string name)
{
	int num_elems = rule.getNumPredicates();
	cout << "There are " << num_elems << " predicates in "
	<< rule.getName() << ":\n";

	// For each predicate
	for (int i=0; i<num_elems; i++)
	{
		string predicate = rule.getPredicate(i);
		cout << "- Predicate " << i << ": " << predicate << endl;
		searchKnowledgeBase(predicate, num_params, add, name);
		searchRuleBase(predicate, num_params, add, name);
	}
	cout << "Finished executeOr(" << rule.getName() << ")\n";
	return;
}

void RuleEngine::executeAnd(Rule rule, int num_params, bool add, string name)
{
	// Get the first predicate
	string predicate = rule.getPredicate(0);

	// Find query in KB
	auto kb_search = this->kb.find(predicate);
	if(kb_search != kb.end())
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

			// Make sure filters is empty for each filter call
			vector<string> filters;
			vector<string> last_vals;

			// Get the first value
			string first_value = fact_vect[i].firstPredicate();
			cout << "First value: " << first_value << endl;

			// Set the first filter value
			filters.push_back(fact_vect[i].lastPredicate());

			// Call the recursive filter
			cout << "Calling filter() with filter=" << filters.back() << " & value=" << first_value << " from predicate " << rule.getPredicate(pred_index) << endl;
			filter(rule, pred_index + 1, filters, num_params, last_vals);
			cout << "First value:  " << first_value << endl;
			
			for (int i=0; i<last_vals.size(); i++)
			{
				cout << first_value << " : " << last_vals[i] << endl;
				if(add)
				{
					cout << "fact name: " << name << " predicates: " << first_value 
					<< " ... " << last_vals[i] << endl;
					vector<string> temp = {first_value, last_vals[i]};
					storeFact(name, temp);
				}
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

void RuleEngine::filter(Rule rule, int pred_index, vector<string> filters, int num_params, vector<string>& last_values)
{
	// Base case
	cout << pred_index << endl;
	cout << rule.getNumPredicates() << endl;
	if (pred_index == rule.getNumPredicates() )
	{
		// Print out first value
		// And corresponding last values
		cout << "Finished filter execution!\n";
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

			cout << fact_vect[i].firstPredicate() << " = " << filters.back() << "?\n";

			// Collect the filters
			if (fact_vect[i].firstPredicate() == filters.back())
			{
				cout << fact_vect[i].firstPredicate() << " matches " << filters.back() << endl;
				current_filters.push_back(fact_vect[i].lastPredicate());
				cout << "Storing " << fact_vect[i].lastPredicate() << " in last_values.\n";
				//last_vals.push_back(fact_vect[i].lastPredicate());
			}
		}

		last_values = current_filters;

		int next_pred = pred_index+1;

		// For every current_filter value
		for (int i=0; i<current_filters.size(); i++)
		{
			filters.push_back(current_filters[i]);
			filter(rule, next_pred, filters, num_params, current_filters);
		}

	} else {
		cout << rule.getPredicate(pred_index) << " not found in KB!\n";
	}

	// Initial filters call
	cout << "Done with filter execution!\n";
	for (int i=0; i<last_values.size(); i++)
	{
		cout << last_values[i] << endl;
	}
}

void RuleEngine::searchKnowledgeBase(string query, int num_params, bool add, string name)
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
			if(add)
			{
				cout << "fact name: " << name << " predicates: " 
				<< fact_vect[i].firstPredicate() << " ... " 
				<< fact_vect[i].lastPredicate() << endl;
				storeFact(name, fact_vect[i].getPredicateVector());
			}
		}
		cout << endl;
	} else cout << query << " fact not found in KB.\n";
}

void RuleEngine::searchRuleBase(string query, int num_params, bool add, string name)
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
			executeRule(rule_vect[i], num_params, add, name);
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
		cout << "Error: Unable to open file" << endl;
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

void RuleEngine::drop()
{
   string tbd;
   cout << "Name of fact/rule to drop?" <<endl;
   cin >> tbd;
   kb.erase(tbd);
   rb.erase(tbd);
}

void RuleEngine::dump()
{
   string filename;
   cout << "Insert a file name 'filename.sri'" << endl;
   cin >> filename;
   ofstream ofile (filename);
   for(map<string, vector<Fact>>::iterator it = kb.begin(); it!=kb.end(); ++it)//Iterating through KB
   {
      ofile << "FACT " << it->first << "(";
      vector<Fact> facts = kb[it->first];
      for(uint i = 0; i<facts.size();i++)
      {
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
      }
      ofile << endl;
   }
   ofile.close();
}
