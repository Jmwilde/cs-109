// void RuleEngine::executeAnd(Rule rule, int num_params, bool add, string name)
// {
// 	// Get the first predicate
// 	string predicate = rule.getValue(0);

// 	// Find query in KB
// 	auto kb_search = this->kb.find(predicate);
// 	if(kb_search != kb.end())
// 	{
// 		// Found in the KB
// 		vector<Fact> fact_vect = kb_search->second;

// 		// Declare variables for filter function
// 		int pred_index = 0;
// 		string first_value;
// 		string filter_value;
// 		vector<string> next_values;

// 		// For each FACT
// 		for (int i=0; i<fact_vect.size(); i++)
// 		{
// 			// Check if the current Fact has the correct # of predicates
// 			if (fact_vect[i].getNumPredicates() != num_params){
// 				continue;
// 			}
// 			// Get intial value
// 			first_value = fact_vect[i].firstPredicate();
// 			// Set intial filter value
// 			filter_value = fact_vect[i].lastPredicate();

// 			// Call the recursive filter
// 			vector<string> output;
// 			filter(rule, pred_index+1, filter_value, num_params, next_values, output);
// 			// Print out the final results
// 			char letter = 'A';
// 			for (int i=0; i<output.size(); i++)
// 			{
// 				cout << char(letter) << ":" << first_value << ", " << char(letter+1) << ":" << output[i] << endl;
// 				if(add)
// 				{
// 					vector<string> temp = {first_value, output[i]};
// 					storeFact(name, temp);
// 				}
// 			}
// 		}
// 	}

// 	// TODO: Get And working for rules!!
// 	auto rb_search = this->rb.find(predicate);
// 	if(rb_search != rb.end())
// 	{
// 		// Found in the KB
// 		vector<Fact> fact_vect = kb_search->second;

// 		// int pred_index = 0;

// 		// For each FACT
// 		for (int i=0; i<fact_vect.size(); i++)
// 		{
// 			// Check if the current Fact has the correct # of predicates
// 			if (fact_vect[i].getNumPredicates() != num_params){
// 				continue;
// 			}
// 		}
// 	}
// }

// Filter needs to know the name of the Rule/Fact to be filtered
// As well as the filter value
// And which position that filter is occupying
// Ex: Parent(John, $B).
// Parent is the query
// John is the value
// John is occupying index 0

// void RuleEngine::filter(Rule rule, int pred_index, string filter_value, int num_params, vector<string>& next_values, vector<string>& output)
// {
// 	// Base case
// 	if (pred_index == rule.getNumPredicates() )
// 	{
// 		for (int i=0; i<next_values.size(); i++)
// 		{
// 			// Search the output to avoid duplicates
// 			if (find(output.begin(), output.end(), next_values[i]) != output.end()) continue;
// 			output.push_back(next_values[i]);
// 		}
// 		return;
// 	}

// 	// Search for the predicate in KB
// 	auto kb_search = this->kb.find(rule.getPredicate(pred_index));
// 	if(kb_search != kb.end())
// 	{
// 		// Found in the KB
// 		vector<Fact> fact_vect = kb_search->second;
// 		vector<string> current_filters;

// 		// For each FACT
// 		for (int i=0; i<fact_vect.size(); i++)
// 		{
// 			// Check if the current Fact has the correct # of predicates
// 			if (fact_vect[i].getNumPredicates() != num_params) continue;

// 			// Collect the filters for the next round
// 			if (fact_vect[i].firstPredicate() == filter_value)
// 			{
// 				current_filters.push_back(fact_vect[i].lastPredicate());
// 			}
// 		}

// 		// For every current_filter value
// 		for (int i=0; i<current_filters.size(); i++)
// 		{
// 			next_values = current_filters;
// 			filter(rule, pred_index+1, current_filters[i], num_params, next_values, output);
// 		}
// 		return;
// 	}
// }

// void RuleEngine::load(string testFile)
// {
// 	string line;
// 	ifstream sriFile(testFile);
// 	if(sriFile.is_open()){
// 		while(getline(sriFile, line)){
// 				parseInput(line);
// 		}
// 		sriFile.close();
// 	}else{
// 		cout << "\nError: Unable to open file" << endl;
// 	}
//   	return;
// }