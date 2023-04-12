# include "../includes/cub3D.h"

int check_input(int argc, char **argv)
{
    if (argc == 1)
    {
		fileXtract("maps/test.cub");
        //fileXtract("maps/testempty.cub");
        //fileXtract("maps/test1l.cub");
        //fileXtract("maps/testrandomletter.cub");
        //fileXtract("maps/testnomap.cub");
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
	return (0);
	//TODO: ? run_game(settings);
}