#include "producer.h"

// Constructor: initializing all data members using attribute list.
// Notice that we have passed the BoundedBuffer Object.
Producer::Producer(int p_sleep_interval_limit,int p_item_limit,
				   int p_items_count,BoundedBuffer <int> * p_boundedBuffer):
				   sleep_interval_limit(p_sleep_interval_limit),item_limit(p_item_limit),
				   items_count(p_items_count),boundedBuffer(p_boundedBuffer){}

void * Producer::threadMainBody(void * arg)
{
	for(int i = 0 ; i < items_count ; i ++)
	{// loop for the items count to produce items_count items
		int item = random_number(1,item_limit); // Generate an item (1-item_limit) using the RNG
		int sleep_interval = random_number(1,sleep_interval_limit); // Generate a sleep random value (1-sleep_interval_limit)
		char debug_str[1024]; // A debug string to store some print info
		memset(debug_str,0,1024); // Initialize the debug string

		// Compose debug string with the all the data generated
		sprintf (debug_str,"Thread # %lu Produced %d and sleeping for %d\n",
		   		 (long)pthread_self(),item,sleep_interval);
		boundedBuffer->produce(item,debug_str); // Inject item into Bounded Buffer sleep(sleep_interval); // Sleep for a while
	}
	return NULL;
}

Producer::~Producer(){}