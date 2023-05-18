# include "../includes/cub3D.h"

int main(int argc, char **argv)
{
    t_start_values ret;
	
	if (argc == 1)
	{
        fileXtract(select_map());
    }
    else if (argc == 2)
	{
		ret.map_name = ft_strdup(argv[1]);
		ret.mouse_selected = 0;
		fileXtract(ret);
	}
	else
		printf("Wrong number of args");
    return (0);
}
