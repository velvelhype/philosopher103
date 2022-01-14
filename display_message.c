#include "philo.h"

void	error()
{
	write(1, "error\n", 7);
	exit(2);
}

void	printf_time()
{
	struct timeval times;
	if (gettimeofday(&times, NULL))
		error();
	printf("%ld%03d ",times.tv_sec, times.tv_usec / 1000);
}