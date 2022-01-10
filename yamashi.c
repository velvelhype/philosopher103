#include <stdio.h>
#include <pthread.h>

void *f(void *p)
{
	int *cnt;

	cnt = p;
	for (int i = 0; i < 10000; ++i)
		++(*cnt);
	return (NULL);
}

int main()
{
	int cnt = 0;
	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, &f, &cnt);
	pthread_create(&thread2, NULL, &f, &cnt);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("end :count %d\n", cnt);
}