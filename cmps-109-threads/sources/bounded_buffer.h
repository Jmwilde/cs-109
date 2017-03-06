#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include "common.h"
#include "util.h"

#define BUFFER_SIZE 10
#define TRANSACTION_COUNT 20
#define PRODUCER_MAX_ITEM 100
#define PRODUCER_MAX_SLEEP 3
#define CONSUMER_MAX_SLEEP 6

// jmwilde's notes:
// Had to put implementation of templates in the header file
// to avoid linker errors. 

// See http://stackoverflow.com/questions/1639797/template-issue-causes-linker-error-c#1639821
// and https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
// to learn more!

template <typename T> // A template definition for handling any type
class BoundedBuffer
{
private:
	T * buffer; // A pointer to the buffer
	size_t size; // Maximum size of the buffer
	pthread_mutex_t mutex; // A mutex for managing critical section
	pthread_cond_t consume_cond; // A condition for the consumer to wait when buffer is empty 
	pthread_cond_t produce_cond; // A condition for the producer to wiat when buffer is full
	int producer_current; // The index pointer of the producer within the buffer
	int consumer_current; // The index pointer of the consumer within the buffer
	int count; // The current number of item in the buffer
public:
	BoundedBuffer (size_t p_size); // Constructor
	void produce (T p_item,string p_debug_string); // Produce an item and add it to the buffer
	T consume (string p_debug_string); // Consume an item and return it to the caller.
	virtual ~BoundedBuffer (); // Destructor
};

template <typename T>
BoundedBuffer<T>::BoundedBuffer(size_t p_size)
{ // Constructor
	size = p_size; // set size
	buffer = (T *) calloc (size,sizeof(T)); // Allocate buffer
	if ( buffer == NULL ) throw (1); // If allocation failed throw an integer 
	pthread_mutex_init (&mutex,NULL); // Initialize mutex 
	pthread_cond_init (&consume_cond,NULL); // Initialize consumer condition 
	pthread_cond_init (&produce_cond,NULL); // Initialize producer condition
	consumer_current = -1; // Set the consuemr current index to -1
	producer_current = -1; // Set the producer current index to -1
	count = 0; // Set count to 0 : empty buffer
}

template <typename T>
void BoundedBuffer<T>::produce(T p_item,string p_debug_string) // Produce: add item to buffer
{
	pthread_mutex_lock(&mutex); // Lock mutex: critical section

	for ( ;count == size ; )
	{ // While buffer is full
		cout << "Buffer is full. Waiting on the producer's condition variable...\n";
		pthread_cond_wait(&produce_cond,&mutex); // Wait on producer_cond which will release mutex
	} // Upon return from wait via a signal mutex will be re-acquired

	// If we are here and producer index reached the end of the buffer,
	// and buffer is not full then there is definitely empty space in the front.
	// Set producer current index to 0, else increment producer current index
	if ( producer_current == size -1 ) producer_current =0;
	else producer_current ++;
	buffer[producer_current] = p_item; // Assign Item to producer current index
	cout << p_debug_string; // print debug string
	count ++; // increment the number of elements in the buffer 
	pthread_mutex_unlock(&mutex); // unlock the critical section mutex 
	pthread_cond_signal(&consume_cond); // Signal consumer waiting on empty buffer of any.
}

template <typename T>
T BoundedBuffer<T>::consume(string p_debug_string) // Consume: return item to caller
{
	pthread_mutex_lock(&mutex); // Lock mutex: critical section 
	
	for ( ;count == 0 ; ) // while buffer is empty
	{
		cout << "Buffer is empty. Waiting on the consumer's condition variable...\n";
		pthread_cond_wait(&consume_cond,&mutex); // wait on consumer_cond which will release mutex 
		// Upon return from wait via a signal, mutex will be re-acquired
	}

	// If we are here and consumer index reached the end of the buffer, 
	// and buffer is not empty then there is definitely occupied items in the front. 
	// Set consumer current index to 0, else increment consumer current index
	if(consumer_current == size-1) consumer_current=0; 
	else consumer_current++; 

	int item = buffer[consumer_current]; // Extract item at consumer current index
	myreplace(p_debug_string,"[item]",to_string(item));
	cout << p_debug_string; // Print debug string
	count --; // Decrement the number of elements in the buffer 
	pthread_mutex_unlock(&mutex); // Unlock the critical section mutex
	pthread_cond_signal(&produce_cond); // Signal producer waiting on full buffer of any.
	return item; // Return the item
}

template <typename T> BoundedBuffer<T>::~BoundedBuffer() // Destructor
{
	if(buffer != NULL) free(buffer); // Free buffer if not NULL 
	pthread_mutex_destroy(&mutex); // Destroy mutex 
	pthread_cond_destroy(&consume_cond); // Destroy consumer condition 
	pthread_cond_destroy(&produce_cond); // Destroy producer condition
}

#endif // BOUNDED_BUFFER_H