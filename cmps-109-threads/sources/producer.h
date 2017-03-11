#ifndef PRODUCER_H
#define PRODUCER_H

#include "thread.h"
#include "bounded_buffer.h"
#include "util.h"

// A class that represents an integer producer
class Producer : public Thread
{
private:
	int sleep_interval_limit; // Time to sleep between production of items
	int item_limit; // Maximum value of an item
	int items_count;// Number of items to generate
	BoundedBuffer <int> * boundedBuffer; // The bounded buffer object to be used
public:
	// Constructor: initializing all data members using attribute list.
	// Notice that we have passed the BoundedBuffer Object.
	Producer(int p_sleep_interval_limit, int p_item_limit, int p_items_count,
			 BoundedBuffer <int> * p_boundedBuffer);
	virtual void * threadMainBody(void * arg);
	~Producer(); // Destructor
};

#endif // PRODUCER_H
