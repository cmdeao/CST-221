/* Cameron Deao */
/* CST-221 */
/* Michael Landreth */
/* 6/13/2020 */

/*Monitors are an abstract data type that share contained variables and procedures.
  Monitors are not a built in class within C, but the process can be achieved through
  the use of mutex object and conditions to access and lock the buffer.
  In this example we're looking at a flight reservation system where two threads are
  seeking access to reserving seats on an airline.*/

//Included libraries
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mon_lock;
int airlineNum = 9876;
int availSeats = 9;

void *ReserveOne()
{
	//Iterated through a for-loop.
	for(int i = 0; i < 5; i++)
	{
		//Conditional statement to avoid reserving seats for the wrong flight,
		//or if no seats remain on the correct flight.
		if(airlineNum == 9876 && availSeats > 0)
		{
			pthread_mutex_lock(&mon_lock); //Getting exclusive access to the buffer.
			printf("First reservation thread: Total seats available: %d\n", availSeats);
			availSeats--; //Iterating down the seat total.
			printf("Total seats remaing: %d\n", availSeats);			
			pthread_mutex_unlock(&mon_lock); //Releasing exclusive access of the buffer.
		}
		else
		{
			printf("Flight #%d is out of seats or the flight number is incorrect.\n", airlineNum);
		}
	}
	pthread_exit(0);
}

void *ReserveTwo()
{
	//Iterated through a for-loop.
	for(int i = 0; i < 5; i++)
	{
		//Conditional statement to avoid reserving seats for the wrong flight,
		//or if no seats remain on the correct flight.
		if(airlineNum == 9876 && availSeats > 0)
		{
			pthread_mutex_lock(&mon_lock); //Getting exclusive access to the buffer.
			printf("Second reservation thread: Total seats available: %d\n", availSeats);
			availSeats--; //Iterating down the seat total.
			printf("Total seats remaining: %d\n", availSeats);
			pthread_mutex_unlock(&mon_lock); //Releasing exclusive access to the buffer.
		}
		else
		{
			printf("Flight #%d is out of seats or the flight number is incorrect.\n", airlineNum);
		}
	}
	pthread_exit(0);
}

int main()
{
	pthread_t res1, res2;
	pthread_mutex_init(&mon_lock, 0);
	pthread_create(&res1, 0, ReserveOne, 0);
	pthread_create(&res2, 0, ReserveTwo, 0);
	
	printf("Starting seating reservation with 2 threads.\n");
	pthread_join(res1, 0);
	pthread_join(res2, 0);
	
	pthread_mutex_destroy(&mon_lock);
	printf("After these threads, the remaining seats total is %d for flight #%d\n", availSeats, airlineNum);
	return 0;
}

