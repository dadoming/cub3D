# include "../includes/cub3D.h"
#include <time.h>

/**
 * Converts clock to microseconds
*/
microseconds	timestamp(struct timespec clock)
{
 	return (clock.tv_sec * 1000000 + clock.tv_nsec / 1000);
}

microseconds	timediff(struct timespec old)
{
	struct timespec	now;

	clock_gettime(CLOCK_MONOTONIC, &now);
	return (timestamp(now) - timestamp(old));
}

microseconds	timestampdiff(struct timespec new, struct timespec old)
{
	return (timestamp(new) - timestamp(old));
}