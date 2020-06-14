/* Cameron Deao */
/* CST-221 */
/* Michael Landreth */
/* 6/13/2020 */

/*
  A semaphore is a data handling technique for process synchronization and is very useful
  in situations of multithreading. Within Linux the POSIX semaphore library is used to solve
  the problem for process synchronization. In this example two threads are seeking to access
  an airline seat reservation system. Once the first thread has access to the system, the
  semaphore is locked while the critical section is executed. After completiong the semaphore
  is released allowing the second thread access to the critical section.
*/

//Included libraries
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

//Declaring the semaphore along with 
//global variables to be used for the system.
sem_t mutex;
int airlineNum = 9876;
int availSeats = 9;

void* Reserve(void* arg)
{
	sem_wait(&mutex); //Locking the semaphore.
	printf("\nEntered reservation thread\n\n");
	
	
	sleep(2); //Critical section of the software.
	//Iterating through a for-loop.
	for(int i = 0; i < 5; i++)
	{
		if(airlineNum == 9876 && availSeats > 0)
		{
			printf("Total seats available: %d\n", availSeats);
			availSeats--;
			printf("Remaing seats: %d\n", availSeats);
		}
		else if(availSeats <=0)
		{
			printf("No more seats are available for reservation on flight #%d\n", airlineNum);
		}
	}

	printf("\nExited the reservation thread\n");
	sem_post(&mutex); //Releasing the semaphore.
}

int main()
{
	sem_init(&mutex, 0, 1); //Initialization of the semaphore.
	pthread_t r1, r2;
	pthread_create(&r1,NULL,Reserve,NULL);
	sleep(2);
	pthread_create(&r2,NULL,Reserve,NULL);
	pthread_join(r1,NULL);
	pthread_join(r2,NULL);
	sem_destroy(&mutex);
	printf("Total remaining seats: %d\n\n", availSeats);
	return 0;	
}
