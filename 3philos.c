#include "philo.h"

#define MAX 5

typedef struct s_mut
{
	int max_number;
	int number;
	int	time_to_eat;
	int	time_to_die;
	int forks[MAX];
	pthread_mutex_t fork_mutex[MAX];
	pthread_mutex_t act_mtx;
	pthread_mutex_t talk_mtx;
} t_mut;

void action(char *message, t_mut *status, int code_number)
{
	code_number += 1;

	pthread_mutex_lock(&status->talk_mtx);
	printf_time();
	if (!ft_strncmp("fork", message, ft_strlen(message)))
	{
		printf("%d has taken a fork\n", code_number);
		pthread_mutex_unlock(&status->talk_mtx);
		return;
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

void take_a_fork(t_mut *stat, int code_number)
{
	// printf_time();
	// printf("code : %d\n", code_number);
	while (1)
	{
		if (stat->forks[fork_number(code_number)] &&
			stat->forks[fork_number(code_number + 1)])
		{
			pthread_mutex_lock(&stat->fork_mutex[fork_number(code_number)]);
			pthread_mutex_lock(&stat->fork_mutex[fork_number(code_number + 1)]);
			stat->forks[fork_number(code_number + 1)] = 0;
			// printf("%d ", fork_number(code_number + 1));
			action("fork", stat, code_number);
			stat->forks[fork_number(code_number)] = 0;
			// printf("%d ", fork_number(code_number));
			action("fork", stat, code_number);
			action("eat", stat, code_number);
			stat->forks[fork_number(code_number)] = 1;
			stat->forks[fork_number(code_number + 1)] = 1;
			pthread_mutex_unlock(&stat->fork_mutex[fork_number(code_number)]);
			pthread_mutex_unlock(&stat->fork_mutex[fork_number(code_number + 1)]);
			return;
		}
	}
}

	void *philo_life(void *p)
	{
		t_mut *stat = p;
		stat->number -= 1;
		int code_number = stat->number;
		while (1)
		{
			take_a_fork(stat, code_number);
			action("sleep", stat, code_number);
			action("think", stat, code_number);
		}
		return (NULL);
	}

	void	init_status(t_mut *stat, char **argv)
	{
		//init
		printf("where %s\n", argv[1]);
		stat->number = ft_atoi(argv[1]);
		printf("where\n");
		stat->max_number = ft_atoi(argv[1]);
		for (int i = 0; i < MAX; i++)
			stat->forks[i] = 1;
		pthread_mutex_init(&stat->talk_mtx, NULL);
		for (int i = 0; i < MAX; i++)
			pthread_mutex_init(&stat->fork_mutex[i], NULL);
		//create threads
	}

	int main(int argc, char **argv)
	{
		pthread_t *philos;
		philos = (pthread_t *)malloc(sizeof(pthread_t) * MAX);
		t_mut stat;
		if(argc != 5 && argc != 6)
			error();
		init_status(&stat, argv);
		for (int i = 0; i < MAX; i++)
		{
			pthread_create(&philos[i], NULL, &philo_life, &stat);
			// pthread_join(philos[i], NULL);
			pthread_detach(philos[i]);
			usleep(100);
		}
		//./a.out
		usleep(500000);
		// usleep(50000);
	}