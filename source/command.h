// CMPS 109
// Winter 2017

// John Wilde - jmwilde
// Nathaniel Suriawijaya - nsuriawi
// Tako Takeda - katakeda
// Noriaki Nakano - nnakano


#ifndef COMMAND_H 
#define COMMAND_H

#include <string>


class Command
{// Command class - declaration of Command class to wrap all the "commands" togethor as one datatype 
	public:
		Command(); // default constructor 
		Command(std::string command_type);
		~Command(); // destructor 
		std::string get_command_type(); // returns command type 
	
	private:
		std::string command_type;
		
}; 

#endif 


