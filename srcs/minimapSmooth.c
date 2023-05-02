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
    y = py - 3.5;
    while (y < py + 3.5)
    {
        pixeldrawx = 0;
        x = px - 3.5;
        while (x < px + 3.5)
        {
            // if (pixeldrawx == MinimapLeftRightSquares * MinimapSquarePixelSize && pixeldrawy == MinimapTopBotSquares * MinimapSquarePixelSize)
            //     pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MinimapSquarePixelSize, 0);
            if (coordcheck(game, x, y) == 'N')
                pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MinimapSquarePixelSize/2, rgbtocolor(0,255,255));
            else if (coordcheck(game,x,y) == WALL)
                pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MinimapSquarePixelSize/2, 0x00D27D2D);
            else if (coordcheck(game,x,y) == DOOR)
                pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MinimapSquarePixelSize/2, 0x00FFD700);
            else
                pixsquare(game, vec2i(pixeldrawx,pixeldrawy), MinimapSquarePixelSize/2, rgbtocolor(255,0,0));
            

            x += 0.5;
            pixeldrawx += MinimapSquarePixelSize/2;
        }
        y += 0.5;
        pixeldrawy += MinimapSquarePixelSize/2;
    }
    draw_checkerboard(game, vec2i(-MinimapSquarePixelSize/2,-MinimapSquarePixelSize/2), 8, MinimapSquarePixelSize);
    pixsquarecent(game, vec2f(MinimapSquarePixelSize*3.5,MinimapSquarePixelSize*3.5), MinimapSquarePixelSize/2, 0);

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

