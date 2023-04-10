# include "../includes/cub3D.h"

int main(int argc, char **argv)
{
    if (check_input(argc, argv) != 0)
        return (0);
    
    //if (check_map(argv[1]) == 0)
    //    return (0);
    
    run_game(argv[1]);
    
    return (0);
}
