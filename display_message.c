#include "philo.h"

void	error_exit()
{
	write(1, "error\n", 7);
	exit(2);
}

size_t    get_time(void)
{
    struct timeval    tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	printf_time()
{
	struct timeval times;
	if (gettimeofday(&times, NULL))
		error_exit();
	printf("%zu ", get_time());
}

// int main()
// {
// 	printf_time();
// 	int i = 0;
// 	// while(i++ < 100)
// 	// 	usleep(100);
// 	size_t ini = get_time();
// 	while(1)
// 	{
// 		// printf("%lld\n", get_time());
// 		if (get_time() - ini >= 10)
// 			break;
// 	}
// 	printf_time();
// }