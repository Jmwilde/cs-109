#include "consumer.h"

// Constructor: initializing all data members using attribute list.
// Notice that we have passed the BoundedBuffer Object.
Consumer::Consumer(int p_sleep_interval_limit, int p_items_count,
				   BoundedBuffer <int> * p_boundedBuffer):
				   sleep_interval_limit(p_sleep_interval_limit), 
				   items_count(p_items_count),boundedBuffer(p_boundedBuffer){}

void * Consumer::threadMainBody(void * arg) // Consume function
{
	for(int i=0; i < items_count; i++)
	{
		int sleep_interval = random_number(1,sleep_interval_limit); // Generate a sleep random value (1-sleep_interval_limit)
		char debug_str[1024]; // A debug string to store some print info
		memset (debug_str,0,1024); // Initialize the debug string

		// Compose debug string with the all the data generated. 
		// Notice the "[item]" place holder.
		sprintf (debug_str,"Thread # %lu Consumed [item] and sleeping for %d\n",
				 (long)pthread_self(),sleep_interval);
		int item = boundedBuffer->consume(debug_str); // Extract item from buffer 
		sleep(sleep_interval); // Sleep for a while
	}
	return NULL;
}

Consumer::~Consumer(){}