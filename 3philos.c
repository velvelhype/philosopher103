#include "philo.h"

typedef struct s_mut
{
	int max_number;
	int number;
	int	time_to_die;
	size_t	*last_meal_time;
	int	eat_time;
	int sleep_time;
	int	eat_limit;
	int *forks;
	int farewell_note;
	pthread_mutex_t *fork_mutex;
	pthread_mutex_t act_mtx;
	pthread_mutex_t talk_mtx;
} t_mut;

void	timer(int time)
{
	size_t ini;

	if (time == 0)
		return ;
	ini = get_time();
	while(1)
	{
		if (get_time() - ini >= time)
			break;
		usleep(100);
	}
}

void action(char *message, t_mut *status, int code_number, int time)
{
	pthread_mutex_lock(&status->talk_mtx);
	printf_time();
	if (!ft_strncmp("fork", message, ft_strlen(message)))
		printf("%d has taken a fork\n", code_number + 1);
	if (!ft_strncmp("eat", message, ft_strlen(message)))
	{
		printf("%d is eating\n", code_number + 1);
		status->last_meal_time[code_number] = get_time();
	}
	if (!ft_strncmp("sleep", message, ft_strlen(message)))
		printf("%d is sleeping\n", code_number + 1);
	if (!ft_strncmp("think", message, ft_strlen(message)))
		printf("%d is thinking\n", code_number + 1);
	pthread_mutex_unlock(&status->talk_mtx);
	timer(time);
}

int fork_number(int fork_number, int max_number)
{
	// printf("fn : %d\n", fork_number);
	if (fork_number == max_number)
		fork_number = 0;
	else if (fork_number == -1)
		fork_number = max_number - 1;
	return (fork_number);
}

void take_a_fork(t_mut *stat, int code_number)
{
	// printf_time();
	// printf("code : %d\n", code_number);
	while (1)
	{
		if (stat->forks[fork_number(code_number, stat->max_number)] &&
			stat->forks[fork_number(code_number + 1, stat->max_number)])
		{
			pthread_mutex_lock(&stat->fork_mutex[fork_number(code_number, stat->max_number)]);
			pthread_mutex_lock(&stat->fork_mutex[fork_number(code_number + 1, stat->max_number)]);
			stat->forks[fork_number(code_number + 1, stat->max_number)] = 0;
			// printf("%d ", fork_number(code_number + 1));
			action("fork", stat, code_number, 0);
			stat->forks[fork_number(code_number, stat->max_number)] = 0;
			// printf("%d ", fork_number(code_number));
			action("fork", stat, code_number, 0);
			action("eat", stat, code_number, stat->eat_time);
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
	int	eat_count;
	eat_count = 0;
	t_mut *stat = p;
	stat->number -= 1;
	int code_number = stat->number;
	stat->last_meal_time[code_number] = get_time();
	while (1)
	{
		take_a_fork(stat, code_number);
		eat_count++;
		if(stat->eat_limit && eat_count == stat->eat_limit)
			stat->farewell_note++;
		action("sleep", stat, code_number, stat->sleep_time);
		action("think", stat, code_number, 0);
	}
	return (NULL);
}

void	init_status(t_mut *stat, int argc, char **argv)
{
	//init
	stat->max_number = ft_atoi(argv[1]);
	stat->number = ft_atoi(argv[1]);
	stat->time_to_die = ft_atoi(argv[2]);
	stat->last_meal_time = (size_t *)malloc(sizeof(size_t) * stat->max_number);
	stat->eat_time = ft_atoi(argv[3]);
	stat->sleep_time = ft_atoi(argv[4]);
	stat->farewell_note = 0;
	if (argc == 6)
	{
		stat->eat_limit = ft_atoi(argv[5]);
		if (stat->eat_limit <= 0)
			error_exit();
	}
	else
		stat->eat_limit = 0;
	stat->forks = (int *)malloc(sizeof(int) * stat->max_number);
	stat->fork_mutex = (pthread_mutex_t *)malloc
	(sizeof(pthread_mutex_t) * stat->max_number);
	for (int i = 0; i < stat->max_number; i++)
		stat->forks[i] = 1;
	pthread_mutex_init(&stat->talk_mtx, NULL);
	for (int i = 0; i < stat->max_number; i++)
		pthread_mutex_init(&stat->fork_mutex[i], NULL);
	//create threads
}

void	are_philos_starving(t_mut *stat)
{
	size_t now;

	now = get_time();
	for (int i = 0; i < stat->max_number; i++)
	{
		if (stat->last_meal_time[i] + stat->time_to_die <= now)
		{
			printf_time();
			printf("%d died\n", i + 1);
			stat->farewell_note++;
			return ;
		}
	}
}

int main(int argc, char **argv)
{
	t_mut stat;
	if(argc != 5 && argc != 6)
		error_exit();
	init_status(&stat, argc, argv);
	pthread_t *philos;
	philos = (pthread_t *)malloc(sizeof(pthread_t) * stat.max_number);
	for (int i = 0; i < stat.max_number; i++)
	{
		pthread_create(&philos[i], NULL, &philo_life, &stat);
		// pthread_join(philos[i], NULL);
		pthread_detach(philos[i]);
		usleep(100);
	}
	//everybody dies
	while(1)
	{
		are_philos_starving(&stat);
		if(stat.farewell_note)
			exit(1);
	}
	// usleep(900000);
}