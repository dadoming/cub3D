# include "../includes/cub3D.h"
#include <time.h>

suseconds_t	timediff(struct timeval old)
{
	struct timeval now;
	// struct timespec	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - old.tv_sec * 1000 + old.tv_usec / 1000);
	// clock_gettime(CLOCK_MONOTONIC, &now);
	// return (now.tv_sec * 1000 + now.tv_nsec / 1000 - old.tv_sec * 1000 + old.tv_usec / 1000);}
}