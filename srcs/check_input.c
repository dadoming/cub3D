# include "../includes/cub3D.h"

int check_input(int argc, char **argv)
{
	t_settings	settings;

    if (argc == 1)
    {
		fileXtract("maps/test.cub");
    }
	else if (argc == 2)
	{
		fileXtract(argv[1]);
	}
	else
	{
		printf("Wrong number of args");
		exit(0);
	}
	//TODO: ? run_game(settings);
}