# include "../includes/cub3D.h"
#include <time.h>

microSeconds	timestamp(struct timespec clock)
{
 	return (clock.tv_sec * 1000000 + clock.tv_nsec / 1000);
}

microSeconds	timediff(struct timespec old)
{
	struct timespec	now;

	clock_gettime(CLOCK_MONOTONIC, &now);
	return (timestamp(now) - timestamp(old));
}
