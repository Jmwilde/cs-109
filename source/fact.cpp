// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

#include <vector>
#include <string>
#include <iostream>
#include "../headers/fact.h"

using namespace std;

Fact::Fact(string name, vector<string> values)
{
	this->name = name;
	this->num_values = values.size();
	this->values = values;
}

int Fact::getNumValues()
{
	return this->num_values;
}

string Fact::getValue(int index)
{
	if (index >= num_values)
	{
		cout << "ERROR: Index out of bounds on getValue().\n";
	}
    return this->values[index];
}

string Fact::firstValue()
{
	return this->values[0];
}

string Fact::lastValue()
{
	return this->values[num_values-1];
}

vector<string> Fact::getValueVector()
{
	return this->values;
}

Fact::~Fact(){}
