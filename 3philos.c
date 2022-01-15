#include "philo.h"

#define MAX 10

typedef struct s_mut
{
	pthread_mutex_t fork_mutex[MAX];
	int forks[MAX];
	pthread_mutex_t act_mtx;
	pthread_mutex_t talk_mtx;
	int number;
	int act_count;
} t_mut;

void action(char *message, t_mut *status, int code_number)
{
	pthread_mutex_lock(&status->talk_mtx);
	printf_time();
	if (!ft_strncmp("fork", message, ft_strlen(message)))
	{
		printf("%d has taken a fork\n", code_number);
		pthread_mutex_unlock(&status->talk_mtx);
		return ;
	}
	else if (!ft_strncmp("eat", message, ft_strlen(message)))
	{
		printf("%d is eating\n", code_number);
	}
	else if (!ft_strncmp("sleep", message, ft_strlen(message)))
	{
		printf("%d is sleeping\n", code_number);
	}
	else
	{
		printf("%d is thinking\n", code_number);
	}
	pthread_mutex_unlock(&status->talk_mtx);

	// pthread_mutex_lock(&status->act_mtx);
	// if(status->act_count == 100)
	// {
	// 	printf("its over %d\n", code_number);
	// 	return ;
	// }
	// status->act_count++;
	// pthread_mutex_unlock(&status->act_mtx);
	timer(20);
}

int fork_number(int fork_number)
{
	// printf("fn : %d\n", fork_number);
	if (fork_number == MAX)
		fork_number = 0;
	else if (fork_number == -1)
		fork_number = MAX - 1;
	return (fork_number);
}

void take_a_fork(t_mut *status, int code_number)
{
	// printf_time();
	// printf("code : %d\n", code_number);
	while (1)
	{
		if (code_number % 2)
		{
			if (status->forks[fork_number(code_number)] && 
				status->forks[fork_number(code_number + 1)])
			{
				pthread_mutex_lock(&status->fork_mutex[fork_number(code_number)]);
				pthread_mutex_lock(&status->fork_mutex[fork_number(code_number + 1)]);
				status->forks[fork_number(code_number + 1)] = 0;
				// printf("%d ", fork_number(code_number + 1));
				action("fork", status, code_number);
				status->forks[fork_number(code_number)] = 0;
				// printf("%d ", fork_number(code_number));
				action("fork", status, code_number);
				action("eat", status, code_number);
				status->forks[fork_number(code_number)] = 1;
				status->forks[fork_number(code_number + 1)] = 1;
				pthread_mutex_unlock(&status->fork_mutex[fork_number(code_number)]);
				pthread_mutex_unlock(&status->fork_mutex[fork_number(code_number + 1)]);
				return;
			}
		}
		else
		{
			if (status->forks[fork_number(code_number)] &&
				status->forks[fork_number(code_number + 1)])
			{
				pthread_mutex_lock(&status->fork_mutex[fork_number(code_number)]);
				pthread_mutex_lock(&status->fork_mutex[fork_number(code_number + 1)]);
				status->forks[fork_number(code_number)] = 0;
				// printf("%d ", fork_number(code_number));
				action("fork", status, code_number);
				status->forks[fork_number(code_number + 1)] = 0;
				// printf("%d ", fork_number(code_number + 1));
				action("fork", status, code_number);
				action("eat", status, code_number);
				status->forks[fork_number(code_number)] = 1;
				status->forks[fork_number(code_number + 1)] = 1;
				pthread_mutex_unlock(&status->fork_mutex[fork_number(code_number)]);
				pthread_mutex_unlock(&status->fork_mutex[fork_number(code_number + 1)]);
				return;
			}
		}
	}
}

void *philo_life(void *p)
{
	t_mut *status = p;
	status->number -= 1;
	int code_number = status->number;
	while (1)
	{
		take_a_fork(status, code_number);
		action("sleep", status, code_number);
		action("think", status, code_number);
	}
	return NULL;
}

int main()
{
	//init
	pthread_t *philos;
	philos = (pthread_t *)malloc(sizeof(pthread_t) * MAX);
	t_mut status;
	status.number = MAX;
	for (int i = 0; i < MAX; i++)
		status.forks[i] = 1;
	status.act_count = 0;
	pthread_mutex_init(&status.talk_mtx, NULL);
	pthread_mutex_init(&status.act_mtx, NULL);
	for (int i = 0; i < MAX; i++)
		pthread_mutex_init(&status.fork_mutex[i], NULL);
	//create threads
	for (int i = 0; i < MAX; i++)
	{
		pthread_create(&philos[i], NULL, &philo_life, &status);
		pthread_detach(philos[i]);
		usleep(100);
	}
	//./a.out
	usleep(5000000);
}