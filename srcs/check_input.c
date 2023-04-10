# include "../includes/cub3D.h"

int check_input(int argc, char **argv)
{
    (void) argv;
    if (argc != 2)
    {
        printf("Wrong number of arguments\n");
        return (1);
    }

    return (0);
}