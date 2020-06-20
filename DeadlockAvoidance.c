/* Cameron Deao */
/* CST-221 */
/* Michael Landreth */
/* 6/20/2020 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

//Global variables.
pthread_mutex_t lock;
int globalCounter;

/*Within this program two threads are competing for access to the globalCounter variable
  and utilize the testingProcess method to increment the counter. Within the method the
  thread is locked allowing for exclusive access to the global variable. After each iteration
  of the critical section the thread is unlocked and the process is put to sleep for one second.
  After the sleep period the next thread takes a turn at incrementing the counter. This continues
  until each thread has incremented the counter five times.  
*/
void *testingProcess(void *param)
{
	//Checking if the thread is locked.
	if(pthread_mutex_lock(&lock) == 0)
	{
		//Displaying which thread is locked.
		printf("Thread locked: %s\n", param);
		//Iterating through a for-loop.
		for(int i = 0; i < 5; i++)
		{
			//Incrementing the global variable.
			globalCounter++;
			printf("Counter: %d\n", globalCounter);
			//Unlocking the thread.
			pthread_mutex_unlock(&lock);
			printf("Thread unlocked: %s\n", param);
			//Sleeping the process for one second.
			sleep(1);
		}
	}
}

int main(int argc, char *argv[])
{
	//Definine the threads.
	pthread_t thread1, thread2;
	//Establishing the names of the threads.
	char *firstName = "Thread 1";
	char *secondName = "Thread 2";
	//Creating the threads and passing the names.
	pthread_create(&thread1, NULL, testingProcess, firstName);
	pthread_create(&thread2, NULL, testingProcess, secondName);
	//Joining the two threads.
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("Both threads executed successfully\n");
	return 0;
}
