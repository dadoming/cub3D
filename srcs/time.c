# include "../includes/cub3D.h"

suseconds_t	timediff(struct timeval old)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - old.tv_sec * 1000 + old.tv_usec / 1000);
}
