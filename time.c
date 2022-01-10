#include <stdio.h>
#include <sys/time.h>

int main()
{
	struct timeval time;
	printf("%d\n", gettimeofday(&time, NULL));
	printf("%ld\n", time.tv_sec);
}