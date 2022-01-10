#include <stdio.h>
#include <unistd.h>
void	*do_something(void *arg)
{
	printf("do\n");
	sleep(10);
	return arg;
}

#include <pthread.h>
int main()
{
	pthread_t thread;
	void *ret;

	if (pthread_create(&thread, NULL, do_something, NULL) != 0)
		return (0);
	pthread_join(thread, &ret);
	pthread_detach(thread);
}