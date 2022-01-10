#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void *print(char *data)
{

	pthread_detach(pthread_self());
	printf("hello i got %s\n", data);
	*data = 'x';
	while(1)
		scanf("%s", data);
}

int main()
{
	int rc;
	pthread_t thread;
	char *t;
	t = calloc(1000, sizeof(char));
	*t = 'a';
	*(t+1) = 'b';


	rc = pthread_create(&thread, NULL, print, t);
	while(1)
	{
		printf("%s\n", t);
		*(t + 3) = '0';
		sleep(1);
	}

	printf("new thread %d\n", thread);
	pthread_exit(NULL);
	printf("new thread %d\n", thread);

}