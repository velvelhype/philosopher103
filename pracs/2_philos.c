#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>


void *philo(void *p)
{

}

int main()
{
	pthread_t philo1;
	pthread_t philo2;
	bool fork[2] = {1, 1};
	printf("%d %d\n", fork[0], fork[1]);
	fork[0] = 0;
	printf("%d %d\n", fork[0], fork[1]);
	
}