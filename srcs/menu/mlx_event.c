# include "../../includes/menu.h"

void close_window(t_menu *menu)
{
    printf("Closing select window...\n");
    mlx_destroy_window(menu->mlx, menu->win);
    mlx_destroy_image(menu->mlx, menu->imgbuffer.img);
    mlx_destroy_display(menu->mlx);
    free(menu->mlx);
    delete_circular_list(&menu->map_list);
    printf("Select window closed!\n");
}

void navigate_top_layer(int keycode, t_menu *menu)
{
    if (keycode == LEFT)
    {
        if (menu->current == 2)
            menu->current = 1;
        else if (menu->current == 0)
            menu->map_list = menu->map_list->prev;
        else
            menu->current--;
        print_map_list(menu, menu->map_list);
    }
    else if (keycode == RIGHT)
    {
        if (menu->current == 0)
            menu->current = 1;
        else if (menu->current == 2)
            menu->map_list = menu->map_list->next;
        else
            menu->current++;
        print_map_list(menu, menu->map_list);
    }
    else if (keycode == DOWN)
    {
        menu->current = 3;
        print_map_list(menu, menu->map_list);
    }
}

void navigate_bottom_layer(int keycode, t_menu *menu)
{
    if (keycode == UP)
    {
        menu->current = 1;
        print_map_list(menu, menu->map_list);
    }
}

int input_event(int keycode, t_menu *menu)
{
    printf("%d\n", menu->current);
    if (keycode == 65307)
    {
        close_window(menu);
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
        else if (menu->current == 3)
        {
            menu->current = 3;
            menu->mouse_selected = !menu->mouse_selected;
            printf("Mouse selected: %d\n", menu->mouse_selected);
            print_map_list(menu, menu->map_list);
        }
        else
        {
            printf("Selected map: %s\n", menu->map_list->name);
            mlx_loop_end(menu->mlx);
            return (1);
        }
    }
    if (menu->current < 3)
        navigate_top_layer(keycode, menu);
    else if (menu->current >= 3)
        navigate_bottom_layer(keycode, menu);

    return (0);
}

int x_close(t_menu *menu)
{
    close_window(menu);
    exit(0);
}