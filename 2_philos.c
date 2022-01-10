#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

int main()
{
	pthread_t philo1;
	pthread_t philo2;
	bool fork[2] = {1, 0};
	printf("%d\n", fork[0], fork[1]);
}