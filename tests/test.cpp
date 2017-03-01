// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

// A test file 

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "../source/rule_engine.h"
#include "../source/fact.h"
#include "../source/rule.h"

using namespace std;

void testExecAnd()
{

	RuleEngine sri;
	cout << "Testing AND execution!\n";

	vector<string> str1 = {"James", "John"};
	vector<string> str2 = {"Roger", "Albert"};
	vector<string> str3 = {"Allen", "Margret"};

	vector<string> str4 = {"Mickey", "John"};
	vector<string> str5 = {"Marry", "Albert"};
	vector<string> str6 = {"Margret", "Robert"};
	vector<string> str7 = {"Margret", "Bob"};

	vector<string> rule_preds = {"Father", "Parent"};

	sri.storeFact("Father", str1);
	sri.storeFact("Father", str2);
	sri.storeFact("Father", str3);
	sri.storeFact("Parent", str4);
	sri.storeFact("Parent", str5);
	sri.storeFact("Parent", str6);
	sri.storeFact("Parent", str7);
	sri.storeRule("Grandfather", AND, rule_preds);

	sri.inference("Grandfather", 2);
}

void testExecOr()
{
	RuleEngine sri;
	cout << "Testing AND execution!\n";

	vector<string> str1 = {"James", "John"};
	vector<string> str2 = {"Roger", "Albert"};
	vector<string> str3 = {"Allen", "Margret"};

	vector<string> str4 = {"Mickey", "John"};
	vector<string> str5 = {"Marry", "Albert"};
	vector<string> str6 = {"Margret", "Robert"};
	vector<string> str7 = {"Margret", "Bob"};

	vector<string> rule_preds = {"Father", "Mother"};

	sri.storeFact("Father", str1);
	sri.storeFact("Father", str2);
	sri.storeFact("Father", str3);
	sri.storeFact("Mother", str4);
	sri.storeFact("Mother", str5);
	sri.storeFact("Mother", str6);
	sri.storeFact("Mother", str7);
	sri.storeRule("Parent", OR, rule_preds);

	sri.inference("Parent", 2);
}

int main(int argc, char const *argv[])
{
	//RuleEngine sri; // Declare a new rule engine

	cout << "Welcome to the Simple Rule Inference Engine!\n";
	cout << "Please input a command.\n\n";

	testExecOr();
	//testExecAnd();
	
	// vector<string> fruits = {"Apple", "Orange"};
	// vector<string> meats = {"Steak", "Chicken"};
	// vector<string> foods = {"Fruits", "Meats"};
	// vector<string> drinks = {"Pepsi", "Mtn Dew"};
	// vector<string> food_and_drink {"Food", "Drinks"};

	// //  User creates & stores some Facts
	// Fact fact1("Fruits", fruits);
	// Fact fact2("Meats", meats);
	// sri.storeFact("Fruits", fact1);
	// sri.storeFact("Meats", fact2);

	// //  Then makes a Rule and stores it
	// Rule rule1("Food", OR, foods);
	// sri.storeRule("Food", rule1);

	// //  Then Infers the rule!
	// sri.inference("Food", 2);

	// Fact fact3("Drinks", drinks);
	// sri.storeFact("Drinks", fact3);

	// cout << "\nBeginning 2nd Test!\n\n";

	// Rule rule2("Food and Drink", OR, food_and_drink);
	// sri.storeRule("Food and Drink", rule2);

	// sri.inference("Food and Drink", 2);


	// vector<string> string1 = {"Frog", "Green"};
	// vector<string> string2 = {"Tiger", "Yellow"};
	// sri.storeFact("Animals", string1);
	// sri.storeFact("Animals", string2);

	// vector<string> string3 = {"Green", "Turtle"};
	// vector<string> string4 = {"Yellow", "Lion"};
	// sri.storeFact("Colors", string3);
	// sri.storeFact("Colors", string4);


	// vector<string> rule_preds = {"Animals", "Colors"};
	// sri.storeRule("Animals_And_Colors", AND, rule_preds);

	// sri.inference("Animals_And_Colors", 2);



	// user inputs a command, and hits Enter/Return

	// the line of text is passed to the parseInput() method

	// sri.parseInput()

	return 0;
};