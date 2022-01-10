#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct s_mut
{
	pthread_mutex_t *mutex;
	int *cnt;
} t_mut;

void *f(void *p)
{
	t_mut *t;
	t = p;

	for (int i = 0; i < 50000; ++i)
	{
		pthread_mutex_lock(t->mutex);
		++*t->cnt;
		pthread_mutex_unlock(t->mutex);
	}
	return NULL;
}

int main()
{
	int cnt = 0;
	pthread_t thread1;
	pthread_t thread2;
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);

	t_mut t;
	t.mutex = &mutex;
	t.cnt = &cnt;

	pthread_create(&thread1, NULL, &f, &t);
	pthread_create(&thread2, NULL, &f, &t);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("%d\n", *t.cnt);
}