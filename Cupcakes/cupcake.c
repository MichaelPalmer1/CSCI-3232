/*
Once compiled the program will continue to run until you close the terminal.
The program starts with 5 cupcakes with a max of 10. 
Eventually the consumer thread will have to wait for a new cupcake to be produced.
Every two seconds a new cupcakes is produced by producer_thread.
Every one second a cupcake will be consumed by consumer_thread.
*/

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

int MAX_CUPCAKES = 10;
int total_cupcakes = 5;

pthread_mutex_t cupcake_lock = PTHREAD_MUTEX_INITIALIZER;

void *bakery();
void *producer();
void *consumer();
bool check = true;

int main()
{	
	pthread_t bakery_thread;

	pthread_create(&bakery_thread, NULL, bakery, NULL);

	pthread_join(bakery_thread, NULL);

	return 0;
}

void *bakery()
{
	pthread_t consumer_thread, producer_thread;

	pthread_create(&producer_thread, NULL, producer, NULL);
	pthread_create(&consumer_thread, NULL, consumer, NULL);

	pthread_join(producer_thread, NULL);
	pthread_join(consumer_thread, NULL);

	printf("Bakery is out of cupcakes.\n");

	return NULL;
}

void *producer()
{
	while(check)
	{
		while(total_cupcakes == MAX_CUPCAKES);

		pthread_mutex_lock(&cupcake_lock);

		total_cupcakes++;
		
		printf("Cupcake produced, total cupcakes is: %d, next cupcake produced in 2 seconds.\n", total_cupcakes);

		pthread_mutex_unlock(&cupcake_lock);

		sleep(2);
	}
	
	return NULL;
}

void *consumer()
{
	while(check)
	{
		while(total_cupcakes == 0);

		pthread_mutex_lock(&cupcake_lock);

		total_cupcakes--;

		printf("Cupcake consumed, total cupcakes is: %d, next cupcakes consumed in 1 second.\n", total_cupcakes);

		pthread_mutex_unlock(&cupcake_lock);

		sleep(1);
	}

	return NULL;
}
