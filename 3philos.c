#include "philo.h"

void	timer(int time)
{
	size_t ini;

	if (time == 0)
		return ;
	ini = get_time();
	while(1)
	{
		if (get_time() - ini >= time)
			return ;
		usleep(100);
	}
}

void	action(char *message, t_status *stat, int code_number, int time)
{
	pthread_mutex_lock(&stat->talk_mtx);
	printf_time();
	if (!ft_strncmp("fork", message, ft_strlen(message)))
		printf("%d has taken a fork\n", code_number + 1);
	if (!ft_strncmp("eat", message, ft_strlen(message)))
	{
		printf("%d is eating\n", code_number + 1);
		stat->last_meal_times[code_number] = get_time();
	}
	if (!ft_strncmp("sleep", message, ft_strlen(message)))
		printf("%d is sleeping\n", code_number + 1);
	if (!ft_strncmp("think", message, ft_strlen(message)))
		printf("%d is thinking\n", code_number + 1);
	pthread_mutex_unlock(&stat->talk_mtx);
	timer(time);
}

int fork_number(int fork_number, int max_number)
{
	if (fork_number == max_number)
		fork_number = 0;
	else if (fork_number == -1)
		fork_number = max_number - 1;
	return (fork_number);
}

void take_a_fork(t_status *stat, int code_number)
{
	while (1)
	{
		if (stat->forks[fork_number(code_number, stat->max_number)] &&
			stat->forks[fork_number(code_number + 1, stat->max_number)])
		{
			pthread_mutex_lock(&stat->fork_mutex[fork_number(code_number, stat->max_number)]);
			pthread_mutex_lock(&stat->fork_mutex[fork_number(code_number + 1, stat->max_number)]);
			stat->forks[fork_number(code_number + 1, stat->max_number)] = 0;
			action("fork", stat, code_number, 0);
			stat->forks[fork_number(code_number, stat->max_number)] = 0;
			action("fork", stat, code_number, 0);
			action("eat", stat, code_number, stat->eat_time);
			(stat->eat_counts[code_number])++;
			stat->forks[fork_number(code_number, stat->max_number)] = 1;
			stat->forks[fork_number(code_number + 1, stat->max_number)] = 1;
			pthread_mutex_unlock(&stat->fork_mutex[fork_number(code_number, stat->max_number)]);
			pthread_mutex_unlock(&stat->fork_mutex[fork_number(code_number + 1, stat->max_number)]);
			return;
		}
	}
}

void *philo_life(void *p)
{
	t_status *stat = p;
	stat->number -= 1;
	int code_number = stat->number;
	stat->last_meal_times[code_number] = get_time();
	while (1)
	{
		take_a_fork(stat, code_number);
		action("sleep", stat, code_number, stat->sleep_time);
		action("think", stat, code_number, 0);
	}
	return (NULL);
}

void	init_status(t_status *stat, int argc, char **argv)
{
	stat->max_number = ft_atoi(argv[1]);
	stat->number = ft_atoi(argv[1]);
	stat->time_to_die = ft_atoi(argv[2]);
	stat->last_meal_times = (size_t *)malloc(sizeof(size_t) * stat->max_number);
	stat->eat_time = ft_atoi(argv[3]);
	stat->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
	{
		stat->eat_limit = ft_atoi(argv[5]);
		if (stat->eat_limit <= 0)
			error_exit();
	}
	else
		stat->eat_limit = 0;
	stat->eat_counts = (size_t *)malloc(sizeof(size_t) * stat->max_number);
	stat->forks = (int *)malloc(sizeof(int) * stat->max_number);
	stat->fork_mutex = (pthread_mutex_t *)malloc
	(sizeof(pthread_mutex_t) * stat->max_number);
	for (int i = 0; i < stat->max_number; i++)
		stat->forks[i] = 1;
	pthread_mutex_init(&stat->talk_mtx, NULL);
	for (int i = 0; i < stat->max_number; i++)
		pthread_mutex_init(&stat->fork_mutex[i], NULL);
}

void	are_philos_full(t_status *stat)
{
	if (stat->eat_limit)
	{
		for (int i = 0; i < stat->max_number; i++)
		{
			if (stat->eat_counts[i] < stat->eat_limit)
				return ;
		}
	}
	exit(1);
}

void	are_philos_starved(t_status *stat)
{
	size_t now;

	now = get_time();
	for (int i = 0; i < stat->max_number; i++)
	{
		if (stat->last_meal_times[i] + stat->time_to_die <= now)
		{
			printf_time();
			printf("%d died\n", i + 1);
			exit(1);
		}
	}
}

int main(int argc, char **argv)
{
	t_status stat;
	if (argc != 5 && argc != 6)
		error_exit();
	init_status(&stat, argc, argv);
	pthread_t *philos;
	philos = (pthread_t *)malloc(sizeof(pthread_t) * stat.max_number);
	for (int i = 0; i < stat.max_number; i++)
	{
		pthread_create(&philos[i], NULL, &philo_life, &stat);
		pthread_detach(philos[i]);
		usleep(100);
	}
	while (1)
	{
		are_philos_starved(&stat);
		are_philos_full(&stat);
	}
}