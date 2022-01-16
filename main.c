#include "philo.h"

void	init_status(int argc, char **argv, t_status *status)
{
	printf_time();
	status->philo_number = ft_atoi(argv[1]);
	status->time_to_die = ft_atoi(argv[2]);
	status->time_to_eat = ft_atoi(argv[3]);
	status->sleep_time = ft_atoi(argv[4]);
	// printf("philo no %d\n", status->philo_number);
	// printf("argc is %d\n", argc);
	// for (int i = 0; i < argc; i++)
	// 	printf("%d\n", ft_atoi(argv[i]));
	if (argc == 6)
	{
		status->limit_number_eat = ft_atoi(argv[5]);
		if (status->limit_number_eat <= 0)
			error_exit();
	}
	status->farewell_note = 0;
	status->mutex_forks = (pthread_mutex_t *)malloc
	(sizeof(pthread_mutex_t) * status->philo_number);
	status->philos = (pthread_t *)malloc
	(sizeof(pthread_t) * status->philo_number);
}
void	*philo_life(void *p)
{
	t_status *status;

	status = p;
	status->philo_number -= 1;
	int	code_number = status->philo_number;
	printf_time();
	while(1)
	{
		printf("Hello from %d\n", code_number);
	}
	return NULL;
}

void	start_philos(t_status status)
{
	printf("in start %d\n", status.philo_number);
	int i  = status.philo_number - 1;
	while(i >= 0)
	{
		printf("%d\n", i);
		pthread_create(&status.philos[i]
		, NULL, &philo_life, &status);
		pthread_detach(status.philos[i]);
		i--;
	}
}

int main(int argc, char **argv)
{
	if(argc != 5 && argc != 6)
		error_exit();
	t_status status;
	init_status(argc, argv, &status);
	start_philos(status);
}