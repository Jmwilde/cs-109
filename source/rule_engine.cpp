// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

#include "rule_engine.h"
#include "help_store_or.h"
//#include "util.h"

using namespace std;
bool created = 0;
const char* prep = "tbd.temp";
ofstream ofile (prep);


RuleEngine::RuleEngine()
{
    map<string, vector<Fact>> kb; // Knowledge Base
    map<string, vector<Rule>> rb; // Rule Base
}

RuleEngine::~RuleEngine(){}

void RuleEngine::printResults(vector<string> results)
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

void RuleEngine::printRb(string name)
{
    vector<Rule> v = this->rb[name];
    for(int i=0; i<v.size(); i++)
    {
        vector<string> vect = v[i].getValueVector();
        for(int j=0; j<vect.size(); j++) cout << vect.at(j) << endl;
    }
}

bool RuleEngine::inKB(string name)
{
    if(kb.find(name) != kb.end()) return true;
    else return false;
}

bool RuleEngine::inRB(string name)
{
    if(rb.find(name) != rb.end()) return true;
    else return false;
}

void RuleEngine::storeFact(string name, vector<string> values)
{
    Fact new_fact(name, values);
    if(kb.find(name) != kb.end())
    {
        vector<Fact> temp = kb[name];
        for(vector<Fact>::iterator iter = temp.begin();iter != temp.end(); iter++)
        {
            if(iter->getValueVector() == values)
            {
                return;
            }
        }
    }
    this->kb[name].push_back(new_fact);
}

void RuleEngine::storeRule(string rule_name, logical_op_t op, vector<string> predicates)
{
    // Store rule now depends on the operator
    if(op == OR)
    {
        cout << "Beginning OR storeRule\n";
        storeOr(rule_name, op, predicates);
    }else if(op == AND){
        cout << "Beginning AND storeRule\n";
        storeAnd(predicates);
    }else
        cout << "Error: No operator given!\n";
}

void RuleEngine::storeAnd(vector<string> predicates)
{
    cout << "Calling store AND\n";

    // Get the first predicate
    string predicate = predicates[0];

    // Find query in KB
    if(inKB(predicate))
    {
        cout << "Found " << predicate << " in the KB!\n";

        // Found in the KB
        vector<Fact> fact_vect = kb[predicate];

        // Declare variables for filter function
        int pred_index = 0;
        string first_value;
        string filter_value;
        vector<string> next_values;

        // For each FACT
        for (int i=0; i<fact_vect.size(); i++)
        {

            cout << "Looking at FACT " << i << endl;
            // Get intial value
            first_value = fact_vect[i].firstValue();
            // Set intial filter value
            filter_value = fact_vect[i].lastValue();

            // Call the recursive filter
            vector<string> output;
            filter(predicates, pred_index+1, filter_value, next_values, output);

            // Print out the final results
            char letter = 'A';
            for (int i=0; i<output.size(); i++)
            {
                cout << char(letter) << ":" << first_value << ", " << char(letter+1) << ":" << output[i] << endl;
            }
        }
    }

    // Find query in RB
    if(inRB(predicate))
    {
        cout << "Found " << predicate << " in the RB!\n";
        
        // Found in the RB
        vector<Rule> rule_vect = rb[predicate];

        // Declare variables for filter function
        int pred_index = 0;
        string first_value;
        string filter_value;
        vector<string> next_values;

        // For each RULE
        for (int i=0; i<rule_vect.size(); i++)
        {
            // Get intial value
            first_value = rule_vect[i].firstValue();
            // Set intial filter value
            filter_value = rule_vect[i].lastValue();

            // Call the recursive filter
            vector<string> output;
            filter(predicates, pred_index+1, filter_value, next_values, output);

            // Print out the final results
            char letter = 'A';
            for (int i=0; i<output.size(); i++)
            {
                cout << char(letter) << ":" << first_value << ", " << char(letter+1) << ":" << output[i] << endl;
            }
        }
    }
}

void RuleEngine::filter(vector<string> predicates, int pred_index, string filter_value, vector<string>& next_values, vector<string>& output)
{
    //string predicate = predicates[pred_index];
    //cout << "Calling filter on " << predicate << endl;

    // Base case
    if (pred_index == predicates.size() )
    {
        cout << "Reached the Base Case with predicates.size() == " << predicates.size() << endl;
        for (int i=0; i<next_values.size(); i++)
        {
            // Search the output to avoid duplicates
            if (find(output.begin(), output.end(), next_values[i]) != output.end()) continue;
            output.push_back(next_values[i]);
        }
        return;
    }
    string predicate = predicates[pred_index];
    cout << "Calling filter on " << predicate << endl;


    // Search for the predicate in KB
    if(inKB(predicate))
    {
        // Found in the KB
        cout << "Found " << predicate << " in the KB!\n";
        vector<Fact> fact_vect = kb[predicate];
        vector<string> current_filters;

        // For each FACT
        for (int i=0; i<fact_vect.size(); i++)
        {
            // Collect the filters for the next round
            if (fact_vect[i].firstValue() == filter_value)
            {
                current_filters.push_back(fact_vect[i].lastValue());
            }
        }

        // For every current_filter value
        for (int i=0; i<current_filters.size(); i++)
        {
            next_values = current_filters;
            filter(predicates, pred_index+1, current_filters[i], next_values, output);
        }
    }

    // Search for the predicate in RB
    if(inRB(predicate))
    {
        // Found in the RB
        cout << "Found " << predicate << " in the RB!\n";
        vector<Rule> rule_vect = rb[predicate];
        vector<string> current_filters;

        // For each RULE
        for (int i=0; i<rule_vect.size(); i++)
        {
            // Check if the current Fact has the correct # of predicates
            //if (fact_vect[i].getNumPredicates() != num_params) continue;

            // Collect the filters for the next round
            if (rule_vect[i].firstValue() == filter_value)
            {
                current_filters.push_back(rule_vect[i].lastValue());
            }
        }

        // For every current_filter value
        for (int i=0; i<current_filters.size(); i++)
        {
            next_values = current_filters;
            filter(predicates, pred_index+1, current_filters[i], next_values, output);
        }
    }

    cout << "Did not find " << predicate << " in KB or RB!\n";
    return;
}

void RuleEngine::storeOr(string rule_name, logical_op_t op, vector<string> predicates)
{
    storeHelper(rule_name, op, predicates);
}

void RuleEngine::storeHelper(string rule_name, logical_op_t op, vector<string> predicates){
   ThreadManager * threadManager = new ThreadManager();
 for(int i = 0; i < predicates.size(); i++){
  cout << "Adding thread " << i << endl;
  threadManager->addThread(new helpStoreOr(this, rule_name, op, predicates, predicates[i]));
 }
   threadManager->start();
   threadManager->barrier();
   delete(threadManager);
}

// NOTE: Does not check for # of parameters when storing
// storeValues finds predicates in KB, RB or both
// and stores their values under the given rule_name in the RB

void RuleEngine::storeValues(string rule_name, logical_op_t op, vector<string> predicate_names, string predicate)
{
    if(inRB(predicate))
    {
        // Get the vector of RULES associated with the predicate/key
        vector<Rule> rule_vect = rb[predicate];

        // For each RULE
        for (int i=0; i<rule_vect.size(); i++)
        {
            // Create a new rule using the current rule's values
            Rule new_rule(rule_name, op, predicate_names, rule_vect[i].getValueVector());

            // Store it in the RB
            rb[rule_name].push_back(new_rule);
        }
    }

    if(inKB(predicate))
    {
        vector<Fact> fact_vect = kb[predicate];

        // For each FACT
        for (int i=0; i<fact_vect.size(); i++)
        {
            Rule new_rule(rule_name, op, predicate_names, fact_vect[i].getValueVector());  // Create a new rule
            rb[rule_name].push_back(new_rule);  // Store it in the RB
        }
    }
}

void RuleEngine::parseInput(string commandLine)
{
    string name = "";
    string query = "";
    string stringOp = "";
    string pred = "";
    string sriFile = "";
    string temp = "";
    int count = 1;
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
        cout << "Error: Invalid command line argument4" << endl;
        }
        getline(iss, query, '(');
        while(getline(iss, temp, ',')){
        if(temp.back() == ')') temp.pop_back();
        paramVec.push_back(temp);
        }
      dumpprep(commandLine);
      this->storeFact(query, paramVec);

    }
    else if(name == "RULE"){
        try{
            if(commandLine.find(":-") == -1) throw 0;
        }catch(int e){
            cout << "Error: Invalid command line argument3" << endl;
        }
        getline(iss, query, '(');
        getline(iss, temp, ' ');
        getline(iss, stringOp, ' ');

        if(stringOp == "OR") op = OR;
        else if(stringOp == "AND") op = AND;
        else cout << "Error: Invalid command line argument2" << endl;

        while(getline(iss, pred, '(')){
            if(pred == " ") break;
            predVec.push_back(pred);
            iss.putback('(');
            getline(iss, temp, ' ');
            try{
                if(temp.find('(') == -1 || temp.find(')') == -1) throw 0;
            }catch(int e){
                cout << "Error: Invalid command line argument1" << endl;
            }
        }
        dumpprep(commandLine);
        this->storeRule(query, op, predVec);
  }else if(name == "INFERENCE"){
    try{
      if(commandLine.find('(') == -1) throw 0;
      if(commandLine.find(')') == -1) throw 0;
    }catch(int e){
      cout << "Error: Invalid command line argument6" << endl;
    }
    getline(iss, query, '(');
        getline(iss, temp, ')');
        for(int i=0; i<temp.size(); i++){
            if(temp.at(i) == ',') count++;
        }
        //getline(iss, temp, ' ');
        getline(iss, pred);
        if(pred != ""){
            this->inference(query, count, pred);
        }
        else{
            this->inference(query, count);
        }
  }else if(name == "LOAD"){
    cout << "Called LOAD!\n";
    getline(iss, sriFile);
        this->load(sriFile);
  }else if(name == "DUMP"){
      getline(iss, sriFile);
      const char *fileName = sriFile.c_str();
      this->dump(fileName);
    //getline(iss, sriFile);
    //    this->dump(sriFile);
  }else if(name == "DROP"){
    getline(iss, pred);
        this->drop(pred);
    }else{
        cout << "Error: Invalid command line argument7" << endl;
    }
    return;
}

void RuleEngine::inference(string query, int num_sub_vars, string name)
{
    searchKnowledgeBase(query, num_sub_vars, true, name);
    searchRuleBase(query, num_sub_vars, true, name);
}

void RuleEngine::inference(string query, int num_sub_vars)
{
    cout << "Callling second inference" << endl;
    searchKnowledgeBase(query, num_sub_vars, false, "");
    searchRuleBase(query, num_sub_vars, false, "");
}

void RuleEngine::searchKnowledgeBase(string query, int num_values, bool add, string name)
{
    //  Look in the KB
    auto kb_search = this->kb.find(query);
    if(kb_search != kb.end())
    {
        // Found in the KB
        vector<Fact> fact_vect = kb[query];
        // For each Fact in the vector
        for (int i=0; i<fact_vect.size(); i++)
        {
            // Check if the current Fact has the correct # of values
            if (fact_vect[i].getNumValues() != num_values) continue;

            // Print corresponding list of strings
            vector<string> results = fact_vect[i].getValueVector();
            printResults(results);

            if(add)
            {
                lineConstructor(name, results);
                storeFact(name, results);
            }
        }
    }
}

void RuleEngine::searchRuleBase(string query, int num_values, bool add, string name)
{
    //  Look in the RB
    if(inRB(query))
    {
        // Found in the RB
        vector<Rule> rule_vect = rb[query];

        // For each Rule in the vector
        for (int i=0; i<rule_vect.size(); i++)
        {
            // Check if the current Rule has the correct # of values
            if (rule_vect[i].getNumValues() != num_values) continue;

            // Print corresponding list of strings
            vector<string> results = rule_vect[i].getValueVector();
            printResults(results);

            if(add){
              lineConstructor(name, results);  
              storeFact(name, results);
            }
        }
    }
}

void RuleEngine::drop(string input)
{
    if(!inKB(input) && !inRB(input))
    {
        cout << input << " does not exist!\n";
        return;
    }
    if(inKB(input)) kb.erase(input);
    if(inRB(input)) rb.erase(input);
}

void RuleEngine::load(string testFile)
{
 string line;
 ifstream sriFile(testFile);
 if(sriFile.is_open()){
   while(getline(sriFile, line)){
       if(line.empty() || util::isWhitespace(line))
       {
          cout << "Warning: empty line inserted" << endl;
       }
       parseInput(line);
       cout << "Success: line being parsed" << endl;
   }
   sriFile.close();
 }else{
   cout << "\nError: Unable to open file" << endl;
 }
   return;
}

void RuleEngine::dump(const char* newname)
{
  ofile.close();
  rename(prep,newname);
}

void RuleEngine::lineConstructor(string name, vector<string> results)
{
  string line = "FACT " + name + "(";
  for(int i = 0; i<results.size();i++){              
    line += results[i];
    if (i+1 != results.size()) line+= ",";
    if (i==results.size()-1) line+= ")";
  }
  dumpprep(line);
}

void RuleEngine::dumpprep(string line)
{
  ofile << line << endl;
}

/*void RuleEngine::dump(string input)
{
   string filename = input;
   string prev;
   ofstream ofile (filename);

   for(map<string, vector<Fact>>::iterator it = kb.begin(); it!=kb.end(); ++it)//Iterating through KB
   {
      vector<Fact> facts = kb[it->first];
      for(uint i = 0; i<facts.size();i++)
      {
         ofile << "FACT " << it->first << "(";
         int preds = facts[i].getNumValues();
         for(int j = 0; j<preds;j++)
         {
            if(j + 1 == preds)
            {
               ofile << facts[i].getValue(j);
               break;
            }
            ofile << facts[i].getValue(j) << ",";
         }
         ofile << ")" << endl;
      }
   }

   for(map<string, vector<Rule>>::iterator it = rb.begin(); it!= rb.end(); ++it) //Iterating through RB
   {
      vector<Rule> rules = rb[it->first];
      cout << "current rule size" << rules.size() << endl;
      for(uint i = 0; i<=rules.size();i++)
      {
        
         int preds = rules[i].getNumPredicates();

         if (it->first == prev)                                  //checking for duplicate rule names
         {
            //cout<< "last vector: " << prev << endl;
            cout<< " current vector: " << it->first << " current index i = " << i << endl;
            //cout << it->first << " " << prev << endl;
            if(rules[i-1].getNumPredicates() == preds){        //checking if duplicate name has same predicates
                //cout<< rules[i-1].getNumPredicates() << " " << preds << endl;
                break;
            }
            else{
              continue;
            }
         }
         string oper;
         int ascii = 65;
         int asciii = 67;
         ofile << "RULE " << it->first << "("; //it->first is the key/string vector name

         if( rules[i].getOp() == 0){ //checking for operator enum
            oper = "OR";
            ofile << "$" << (char)ascii << ",$" << (char)(ascii+preds-1) << "):- " << oper << " ";
         }
         else{
            oper = "AND";
            ascii = 65;
            if(rules[i].getNumValues() == 2)
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
               for(int k = 0; k<rules[i].getNumValues(); k++)
               {
                  if(k + 1 == rules[i].getNumValues())
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
            cout << "last vector name: "<< prev << "current index i = " << i << endl;
      }
      ofile << endl;
   }
   ofile.close();
}*/
