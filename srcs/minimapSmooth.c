# include "../includes/cub3D.h"

void    minimap_background(t_game *game)
{
    pixsquare(game, vec2i(0,0), 5*MinimapSquarePixelSize, rgbtocolor(255,0,0));
}

void    minimap_show(t_game *game)
{
    float y;
    float x;
    int pixeldrawx;
    int pixeldrawy;

    pixeldrawy = 0;
    y = py - MinimapTopBotSquares;
    while (y < py + MinimapTopBotSquares + 1)
    {
        pixeldrawx = 0;
        x = px - MinimapLeftRightSquares;
        while (x < px + MinimapLeftRightSquares + 1)
        {
            if (pixeldrawx == MinimapLeftRightSquares * MinimapSquarePixelSize && pixeldrawy == MinimapTopBotSquares * MinimapSquarePixelSize)
                pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MinimapSquarePixelSize, 0);
            else if (coordcheck(game, x, y) == 'N')
                pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MinimapSquarePixelSize, rgbtocolor(0,255,255));
            else if (coordcheck(game,x,y) == WALL)
                pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MinimapSquarePixelSize, 0x00D27D2D);
            else if (coordcheck(game,x,y) == DOOR)
                pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MinimapSquarePixelSize, 0x00FFD700);
            else
                pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MinimapSquarePixelSize, rgbtocolor(255,0,0));
            

            horline(game, vec2i(pixeldrawx, pixeldrawy), MinimapSquarePixelSize, 0);
            verline(game, vec2i(pixeldrawx, pixeldrawy), MinimapSquarePixelSize, 0);
            x += 1;
            pixeldrawx += MinimapSquarePixelSize;
        }
        y += 1;
        pixeldrawy += MinimapSquarePixelSize;
    }
    horline(game, vec2i(0, pixeldrawy), MinimapSquarePixelSize*5, 0);
    // verline(game, vec2i(pixeldrawx, pixeldrawy), MinimapSquarePixelSize, 0);

}


void draw_minimapSmooth(t_game *game)
{
    t_vec2i vec;
    
    // vec.y = (int)(py/64);
    // vec.x = (int)(px/64);
    //TODO(arc): will remove this when ppos is correct
    vec.x = px;
    vec.y = py;
    px = px/64;
    py = py/64;
    // px = 404.903931;
    // py = 392.975464;
    // minimap_background(game);
    minimap_show(game);
    px = vec.x;
    py = vec.y;
}

