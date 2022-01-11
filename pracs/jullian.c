#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct s_mut
{
	pthread_mutex_t *mutex;
	int *cnt;
} t_mut;

void *f(void *p)
{
	t_mut *t = p;

	for (int i = 0; i < 10000; ++i)
	{
		++*t->cnt;
	}

	return (NULL);
}

void *e(void *p)
{
	t_mut *t = p;

	pthread_mutex_lock(t->mutex);

	for (int i = 0; i < 10000; ++i)
	{
		++*t->cnt;
	}
	pthread_mutex_unlock(t->mutex);

	return (NULL);
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
	pthread_create(&thread2, NULL, &e, &t);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	// pthread_detach(thread1, NULL);
	// pthread_detach(thread2);
	// pthread_detach(thread2, NULL);

	printf("end :count %d\n", cnt);
}