# include "../includes/cub3D.h"

void    minimap_background(t_game *game)
{
    pixsquare(game, vec2i(0,0), 5*MINIMAPSCALE, rgbtocolor(255,0,0));
}

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
            else
                pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MINIMAPSCALE, rgbtocolor(255,0,0));
            x += 0.1;
            pixeldrawx += MINIMAPSCALE;
        }
        y += 0.1;
        pixeldrawy += MINIMAPSCALE;
    }
}


void draw_minimapSmooth(t_game *game)
{
    t_vec2i vec;
    
    // vec.y = (int)(py/64);
    // vec.x = (int)(px/64);
    //TODO(arc): will remove this when ppos is correct
    vec.x = px;
    vec.y = py;
    // px = 404.903931;
    // py = 392.975464;
    // minimap_background(game);
    minimap_show(game);
    pixsquare(game, vec2i(35*MINIMAPSCALE, 35*MINIMAPSCALE), 5, 0);
    // draw_checkerboard(game, vec2i(-MINIMAPSCALE,-MINIMAPSCALE), 8, 10);
    px = vec.x;
    py = vec.y;
}

