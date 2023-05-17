# include "../../includes/menu.h"

void open_select_window(t_menu *menu)
{
    printf("Opening select window...\n");
    menu->mlx = mlx_init();
    if (!menu->mlx)
    {
        printf("Error: could not initialize mlx!\n");
        exit(0);
    }
    menu->win = mlx_new_window(menu->mlx, WINDOWSIZE_X, WINDOWSIZE_Y, "Select map");
    if (!menu->win)
    {
        printf("Error: could not create window!\n");
        mlx_destroy_display(menu->mlx);
        free(menu->mlx);
        exit(0);
    }
    mlx_hook(menu->win, 2, 1L<<0, input_event, menu);
    mlx_hook(menu->win, 17, 1L<<2, x_close, menu);
}

void draw_rectangle(t_menu *menu, int x_one, int x_two, int y_min)
{
    int y_max;
    int left = x_one;

    if (y_min < 90)
    {
        y_max = 90;
    }
    else
    {
        y_max = 130;
    }
    while (y_min < y_max)
    {
        while (left < x_two)
        {
            my_pput(&menu->imgbuffer, left, y_min, PURPLE);
            left++;
        }
        left = x_one;
        y_min++;
    }
}

void draw_rectangle_mouse(t_menu *menu, int x_one, int x_two, int y_min)
{
    int y_max;
    int aux = y_min;
    int left = x_one;

    y_max = 125;
    while (y_min < y_max)
    {
        while (left < x_two)
        {
            if (left == x_one || left == x_two - 1 || y_min == y_max - 1 || y_min == aux)
            {
                my_pput(&menu->imgbuffer, left, y_min, YELLOW);
            }
            else if (menu->mouse_selected == 1)
            {
                my_pput(&menu->imgbuffer, left, y_min, RED);
            }
            left++;
        }
        left = x_one;
        y_min++;
    }
}

void draw_rectangles(t_menu *menu)
{
    // top menu
    if (menu->current == 0)
        draw_rectangle(menu, 15, 30, 65);
    else if (menu->current == 2)
        draw_rectangle(menu, 265, 285, 65);
    else if (menu->current == 1)
        draw_rectangle(menu, 30, 265, 65);
    
    // mouse menu
    else if (menu->current == 3)
        draw_rectangle(menu, 60, 95, 95);
    
    draw_rectangle_mouse(menu, 65, 90, 100);
}

void print_map_list(t_menu *menu, t_map_list *map_list)
{
    clear_img(menu);
    draw_rectangles(menu);
    mlx_put_image_to_window(menu->mlx, menu->win, menu->imgbuffer.img, 0, 0);
    mlx_string_put(menu->mlx, menu->win, 20, 30, YELLOW, "Press arrows and space to move in this menu!");
    mlx_string_put(menu->mlx, menu->win, 20, 100 - 20, YELLOW, "<");
    mlx_string_put(menu->mlx, menu->win, 50, 100 - 20, WHITE, map_list->name);
    mlx_string_put(menu->mlx, menu->win, 275, 100 - 20, YELLOW, ">");
    mlx_string_put(menu->mlx, menu->win, 20, 115, YELLOW, "Mouse: ");
    mlx_string_put(menu->mlx, menu->win, 20, 115 + 25, YELLOW, "(if not selected, only keys will work)");
    mlx_string_put(menu->mlx, menu->win, 20, 170, RED, "Press space on map to start!");
    
}

t_start_values select_map(void)
{
    t_menu menu;
    t_start_values ret;

    ret.map_name = NULL;
    ret.mouse_selected = 0;
    ft_memset(&menu, 0, sizeof(t_menu));
    menu.map_list = get_available_maps();
    if (!menu.map_list)
        return (ret);
    open_select_window(&menu);
    menu.imgbuffer.img = mlx_new_image(menu.mlx, WINDOWSIZE_X, WINDOWSIZE_Y);
    menu.imgbuffer.addr = mlx_get_data_addr(menu.imgbuffer.img, &menu.imgbuffer.bits_per_pixel, &menu.imgbuffer.line_length, &menu.imgbuffer.endian);
    if (!menu.imgbuffer.img)
        return (ret);
    clear_img(&menu);
    menu.current = 1;
    menu.mouse_selected = 0;

    print_map_list(&menu, menu.map_list);
    mlx_loop(menu.mlx);
    ret.map_name = ft_strjoin("./maps/", menu.map_list->name);
    ret.mouse_selected = menu.mouse_selected;
    close_window(&menu);
    printf("Closing select window...\n");
    printf("Select window closed!\n");
    return (ret); // selected map
}
