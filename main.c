#include "philo.h"

void	*philo(void *p)
{
	return (NULL);
}

void	init_status(int argc, char **argv, t_status status)
{
	printf_time();
	status.philo_numbers = ft_atoi(argv[1]);
	status.time_to_die = ft_atoi(argv[2]);
	status.eat_time = ft_atoi(argv[3]);
	status.sleep_time = ft_atoi(argv[4]);
	printf("argc is %d\n", argc);
	for (int i = 0; i < argc; i++)
		printf("%d\n", ft_atoi(argv[i]));
	if (argc == 6)
		status.limit_eat = ft_atoi(argv[5]);
	status.farewell_note = 0;
	status.forks = (pthread_mutex_t *)malloc
	(sizeof(pthread_mutex_t) * status.philo_numbers);
}

void	start_philos(t_status status)
{
	int i  = status.philo_numbers;
	while(i)
	{
		
	}
}

int main(int argc, char **argv)
{
	if(argc != 5 && argc != 6)
		error();
	t_status status;
	init_status(argc, argv, status);
	//start_philos();
}