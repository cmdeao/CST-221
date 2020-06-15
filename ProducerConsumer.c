/* Cameron Deao */
/* CST-221 */
/* Michael Landreth */
/* 6/14/2020 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//Establishing the buffer size as 5
#define BUFFER_SIZE 5

//Threads
pthread_mutex_t buffAccess;
pthread_cond_t cons;
pthread_cond_t prod;

//Global variables
static int buffer[BUFFER_SIZE];
int count;
int theProduct;

/*Within the 'put' method the buffer thread is locked and given exclusive access.
  If the global variable of count is equal to the BUFFER_SIZE, the produce thread
  is put to sleep to avoid additional additions.
  The value is placed within the buffer, and the global counter variable is incremented
  up. If the the global variable is higher than 0, the consume thread is woken up.
  Finally the buffer thread is unlocked for access. */
int put(int i)
{	
	pthread_mutex_lock(&buffAccess);
	if(count == BUFFER_SIZE)
	{
		pthread_cond_wait(&prod, &buffAccess);
	}
	buffer[count] = i;
	count++;
	if(count > 0)
	{
		pthread_cond_signal(&cons);
	}
	pthread_mutex_unlock(&buffAccess);
}

/*Within the 'get' method the the buffer thread is locked and given exclusive access.
  If the global count is equal to 0, the consume thread is put to sleep. A temporary
  integer variable is created and set to the current buffer index. The global counter 
  is incremented down. The producer thread is awoken if necessary, and the buffer
  thread is unlocked for access. The one problem I can't understand, is why I'm occassionally
  getting a zero within the consumed output of the program.
 */
int get()
{
	pthread_mutex_lock(&buffAccess);
	if(count == 0)
	{
		pthread_cond_wait(&cons, &buffAccess);
	}
	int removeTemp = buffer[count];
	count--;
	if(count == BUFFER_SIZE - 1)
	{
		pthread_cond_signal(&prod);
	}
	pthread_mutex_unlock(&buffAccess);
	return removeTemp;
}

int produce()
{
	printf("Produced: %i\n ", theProduct + 1);
	return theProduct++;
}

void consume(int i)
{
	printf("Consumed: %i\n ", i);
}

void *producer()
{
	int i;
	while(1)
	{
		i = produce();
		put(i);
	}
}

void *consumer()
{
	int i;
	while(1)
	{
		i = get();
		consume(i);
	}
}

int main()
{
	pthread_t con, pro;
	pthread_mutex_init(&buffAccess, 0);
	pthread_cond_init(&cons, 0);
	pthread_cond_init(&prod, 0);
	pthread_create(&con, 0, consumer, 0);
	pthread_create(&pro, 0, producer, 0);
	pthread_join(pro, 0);
	pthread_join(con, 0);
	return 0;
}
