# include "../../includes/menu.h"

int input_event(int keycode, t_menu *menu)
{
    if (keycode == 65307)
    {
        printf("Closing select window...\n");
        mlx_destroy_window(menu->mlx, menu->win);
        mlx_destroy_display(menu->mlx);
        free(menu->mlx);
        delete_circular_list(&menu->map_list);
        printf("Select window closed!\n");
        exit(0);
    }
    else if (keycode == SPACE)
    {
        if (menu->current == 2)
        {
            menu->map_list = menu->map_list->next;
            print_map_list(menu, menu->map_list);
        }
        else if (menu->current == 0)
        {
            menu->map_list = menu->map_list->prev;
            print_map_list(menu, menu->map_list);
        }
        else
        {
            printf("Selected map: %s\n", menu->map_list->name);
            mlx_loop_end(menu->mlx);
            return (1);
        }
    }
    else if (keycode == LEFT)
    {
        if (menu->current == 2)
            menu->current = 1;
        else if (menu->current == 0)
        {
            menu->map_list = menu->map_list->prev;
        }
        else
            menu->current--;
        print_map_list(menu, menu->map_list);
    }
    else if (keycode == RIGHT)
    {
        if (menu->current == 0)
            menu->current = 1;
        else if (menu->current == 2)
        {
            menu->map_list = menu->map_list->next;
        }
        else
            menu->current++;
        print_map_list(menu, menu->map_list);
    }
    return (0);
}

int x_close(t_menu *menu)
{
    printf("Closing select window...\n");
    mlx_destroy_window(menu->mlx, menu->win);
    mlx_destroy_image(menu->mlx, menu->imgbuffer.img);
    mlx_destroy_display(menu->mlx);
    free(menu->mlx);
    delete_circular_list(&menu->map_list);
    printf("Select window closed!\n");
    exit(0);
}