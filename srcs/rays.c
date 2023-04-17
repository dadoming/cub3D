# include "../includes/cub3D.h"


void	drawXgridColl(t_game *game)
{
	t_vec2f	rayend;
	float	triangbase;
	char	chk;
	// triangbase = (int)(game->player.pos.x + 1) - game->player.pos.x;

	// rayend.y = game->player.pos.y + tan(game->player.theta) * triangbase;
	// rayend.x = (int)(game->player.pos.x + 1);

	// squarecent_prop(game, rayend, 4, rgbtocolor(128, 0, 128));

	rayend.x = game->player.pos.x;
	rayend.y = game->player.pos.y;

	chk = coordcheck(game, rayend.x, rayend.y);
	while (chk != '1' && chk != 0)
	{
		triangbase = (int)(rayend.x + 1) - rayend.x;

		rayend.y += tan(game->player.theta) * triangbase;
		squarecent_prop(game, rayend, 4, rgbtocolor(128, 0, 128));

		rayend.x = (int)(rayend.x + 1);
		chk = coordcheck(game, rayend.x, rayend.y);
	}

}

int	draw_ray(t_game *game)
{
	drawXgridColl(game);
}