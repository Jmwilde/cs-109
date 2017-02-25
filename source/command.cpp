// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano

// Implementation of Command class
#include "command.h"
#include <string>

Command::Command()
{// default constructor 
	this->command_type = "";
}// End constructor 

Command::Command(std::string command_type)
{// secondary constructor that takes in a command_type string 
	this->command_type = command_type;
}// End constructor 

Command::~Command()
{// destructor 
	
}// End destructor 

std::string Command::get_command_type()
{// returns the command type 
	return this->command_type;
}// End get_command_type 

