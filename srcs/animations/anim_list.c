# include "../../includes/cub3D.h"

// number starts in 1
t_anim_list *load_n_images(t_game *game, char *imagename, int number_of_images)
{
    char filename[100];
    t_imgbuffer frame;
    int i;
    t_anim_list *list;

    list = NULL;
    i = 1;
    while (i <= number_of_images)
    {
        sprintf(filename, "textures/%s%d.xpm", imagename, i);

        frame.img = mlx_xpm_file_to_image(game->mlx, filename, &frame.width, &frame.height);
        if (frame.img == NULL)
        {
            printf("Error\nInvalid texture path\n");
            exit(EXIT_FAILURE);
        }
        frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel, &frame.line_length, &frame.endian);
        insert_frame(&list, frame);
        printf("Loaded frame %d -> %s\n", i, filename);
        i++;
    }
    return (list);
}

t_anim_list *create_frame_node(t_imgbuffer frame)
{
    t_anim_list *new_node = (t_anim_list *)malloc(sizeof(t_anim_list));
    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->img = frame;
    new_node->next = NULL;

    return new_node;
}

// at the end
void insert_frame(t_anim_list **head, t_imgbuffer frame)
{
    t_anim_list *new_node = create_frame_node(frame);

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        t_anim_list *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void free_anim_list(t_game *game, t_anim_list **head)
{
    t_anim_list *current = *head;
    t_anim_list *next;

    while (current != NULL)
    {
        next = current->next;
        mlx_destroy_image(game->mlx, current->img.img);
        free(current);
        current = next;
    }
    *head = NULL;
}

