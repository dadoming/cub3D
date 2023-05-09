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

void draw_rectangle(t_menu *menu, int x_one, int x_two, int color)
{
    int y = 85;
    int left = x_one;

    while (y < 110)
    {
        while (left < x_two)
        {
            my_pput(&menu->imgbuffer, left, y, color);
            left++;
        }
        left = x_one;
        y++;
    }
}

void draw_rectangles(t_menu *menu, int color)
{
    if (menu->current == 0)
        draw_rectangle(menu, 15, 30, color);
    else if (menu->current == 2)
        draw_rectangle(menu, 265, 285, color);
    else
        draw_rectangle(menu, 30, 265, color);
}

void print_map_list(t_menu *menu, t_map_list *map_list)
{
    clear_img(menu);
    draw_rectangles(menu, 0x00A020F0);
    mlx_put_image_to_window(menu->mlx, menu->win, menu->imgbuffer.img, 0, 0);
    mlx_string_put(menu->mlx, menu->win, 20, 30, 0x00FFFF00, "Press left or right arrow to choose the map:");
    mlx_string_put(menu->mlx, menu->win, 20, 100, 0x00FFFF00, "<");
    mlx_string_put(menu->mlx, menu->win, 50, 100, 0x00FFFFFF, map_list->name);
    mlx_string_put(menu->mlx, menu->win, 275, 100, 0x00FFFF00, ">");
    mlx_string_put(menu->mlx, menu->win, 20, 170, 0x00FF0000, "Press space to select map");
}

char *select_map(void)
{
    t_menu menu;
    char *ret;

    ft_memset(&menu, 0, sizeof(t_menu));
    menu.map_list = get_available_maps();
    if (!menu.map_list)
        return (NULL);
    open_select_window(&menu);
    menu.imgbuffer.img = mlx_new_image(menu.mlx, WINDOWSIZE_X, WINDOWSIZE_Y);
    menu.imgbuffer.addr = mlx_get_data_addr(menu.imgbuffer.img, &menu.imgbuffer.bits_per_pixel, &menu.imgbuffer.line_length, &menu.imgbuffer.endian);
    if (!menu.imgbuffer.img)
        return (NULL);
    clear_img(&menu);
    menu.current = 1;
    
    print_map_list(&menu, menu.map_list);
    mlx_loop(menu.mlx);
    ret = ft_strjoin("./maps/", menu.map_list->name);
    close_window(&menu);
    printf("Closing select window...\n");
    printf("Select window closed!\n");
    return (ret); // selected map
}
