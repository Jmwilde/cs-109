#ifndef CONSUMER_H
#define CONSUMER_H

// A class that represents an integer consumer
class Consumer : public Thread
{
private:
	int sleep_interval_limit; // Time to sleep between consumption attempts
	int items_count; // Number of consumptions to perform
	BoundedBuffer <int> * boundedBuffer;// The bounded buffer object to be used
public:
	// Constructor: initializing all data members using attribute list.
	// Notice that we have passed the BoundedBuffer Object.
	Consumer(int p_sleep_interval_limit,int p_items_count, 
			 BoundedBuffer <int> * p_boundedBuffer);
	virtual void * threadMainBody(void * arg); // Consume function
	~Consumer();
};

#endif // CONSUMER_H