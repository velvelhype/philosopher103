#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include "libft/libft.h"
#include <sys/time.h>

typedef struct s_status{
	int		philo_numbers;
	int		time_to_die;
	int		eat_time;
	int		sleep_time;
	int		limit_eat;

	bool	farewell_note;
	pthread_mutex_t	*forks;
} t_status;

void	error();
void	printf_time();
