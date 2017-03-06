#include "bounded_buffer.h"
#include "consumer.h"
#include "producer.h"
#include "thread.h"
#include "thread_manager.h"

#define PROD_CONS_COUNT 10

int main()
{
	BoundedBuffer <int> * boundedBuffer; // Declare an integer Bound Buffer

	try{ // try just in case we cannot allocate buffer
		boundedBuffer = new BoundedBuffer <int>(BUFFER_SIZE); // instantiate bounded buffer
		ThreadManager * threadManager = new ThreadManager(); // instantiate a thread manager

		// Create producers
		cout << "Creating producers!\n";
		for(int i=0; i < PROD_CONS_COUNT; i++)
			threadManager->addThread(new Producer(PRODUCER_MAX_SLEEP,
			PRODUCER_MAX_ITEM, TRANSACTION_COUNT, boundedBuffer));

		cout << "Creating consumers!\n";
		// Create consumers
		for(int i=0; i < PROD_CONS_COUNT; i++)
			threadManager->addThread(new Consumer(CONSUMER_MAX_SLEEP,
			TRANSACTION_COUNT, boundedBuffer));

		threadManager->start(); // Start all threads
		threadManager->barrier(); // Block on barrier until all threads terminate 
		delete (threadManager); // Delete thread manager
		
	} catch (int){ // If exception caught
		cout << "Exception caught here\n"; // Print message 
		boundedBuffer=NULL; //set boundedBuffer to NULL to avoid destruction
	}

	// Destruct boundedBuffer if instantiated
	if(boundedBuffer != NULL) delete(boundedBuffer);
	return 0;
}