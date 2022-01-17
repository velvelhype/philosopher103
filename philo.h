#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include "libft/libft.h"
#include <sys/time.h>

typedef struct s_status{
	int		philo_number;
	int		time_to_die;
	int		time_to_eat;
	int		sleep_time;
	int		limit_number_eat;

	bool	farewell_note;
	int		*forks;
	pthread_mutex_t	*mutex_forks;
	pthread_t *philos;
} t_status;

void	error_exit();
void	printf_time();
size_t	get_time();