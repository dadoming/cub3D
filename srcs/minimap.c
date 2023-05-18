# include "../includes/cub3D.h"

void    minimap_show(t_game *game)
{
    float y;
    float x;
    int pixeldrawx;
    int pixeldrawy;

    pixeldrawy = 0;
    y = py - 3.5;
    while (y < py + 3.5)
    {
        pixeldrawx = 0;
        x = px - 3.5;
        while (x < px + 3.5)
        {
            if (coordcheck(game, x, y) == 'N')
                pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MINIMAPSCALE, rgbtocolor(0,255,255));
            else if (coordcheck(game,x,y) == WALL)
                pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MINIMAPSCALE, 0x00D27D2D);
            else if (coordcheck(game,x,y) == DOOR)
                pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MINIMAPSCALE, 0x00FFD700);
            else if (coordcheck(game,x,y) == STATICENEMY)
                pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MINIMAPSCALE, 0x00AAD300);
            else
                pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MINIMAPSCALE, rgbtocolor(255,0,0));
            x += 0.1;
            pixeldrawx += MINIMAPSCALE;
        }
        y += 0.1;
        pixeldrawy += MINIMAPSCALE;
    }
}


void draw_minimap(t_game *game)
{
    t_vec2i vec;
    
    vec.x = px;
    vec.y = py;
    minimap_show(game);
    pixsquare(game, vec2i(35*MINIMAPSCALE, 35*MINIMAPSCALE), 5, 0);
    px = vec.x;
    py = vec.y;
}

