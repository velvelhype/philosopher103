#include "philo.h"

typedef struct s_mut
{
	pthread_mutex_t for_mutex[3];
	pthread_mutex_t act_mtx;
	pthread_mutex_t talk_mtx;
	pthread_mutex_t a_fork_mtx;
	// int	forks[3];
	int	fork;
	int number;
	int act_count;
} t_mut;

void	action(char *message, t_mut *status, int code_number)
{
	pthread_mutex_lock(&status->talk_mtx);
	printf_time();
	if (!ft_strncmp("eat", message, ft_strlen(message)))
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
	usleep(40000);
}

void take_a_fork(t_mut *status, int code_number)
{
	pthread_mutex_lock(&status->a_fork_mtx);
	while(1)
	{
		if (status->fork)
		{
			status->fork = 0;
			action("eat", status, code_number);
			status->fork = 1;
			break;
		}
		else
			usleep(100);
	}
	pthread_mutex_unlock(&status->a_fork_mtx);
}

void	*philo_life(void *p)
{
	t_mut *status = p;
	status->number -= 1;
	int	code_number = status->number;
	while(1)
	{
		take_a_fork(status, code_number);
		// action("eat", status, code_number);
		action("sleep", status, code_number);
		action("think", status, code_number);

	}
	return NULL;
}

int main()
{
	pthread_t philo1;
	pthread_t philo2;
	pthread_t philo3;

	t_mut status;
	//init
	status.number = 3;
	status.fork = 1;
	// status.forks[0] = 0;
	// status.forks[1] = 0;
	// status.forks[2] = 0;
	status.act_count = 0;
	pthread_mutex_init(&status.talk_mtx, NULL);
	pthread_mutex_init(&status.act_mtx, NULL);
	pthread_mutex_init(&status.a_fork_mtx, NULL);
		pthread_create(&philo1
		, NULL, &philo_life, &status);
		pthread_detach(philo1);
		usleep(100);
		pthread_create(&philo2
		, NULL, &philo_life, &status);
		pthread_detach(philo2);
		usleep(100);

		pthread_create(&philo3
		, NULL, &philo_life, &status);
		pthread_detach(philo3);
	//
	usleep(100000);
	// printf("acted %d\n", status.act_count);
}