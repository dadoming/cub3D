# include "../includes/cub3D.h"

double	excenter(double x)
{
	if (x >= 0)
		return (ceil(x));
	else
		return (floor(x));
	
}

void	drawXgridColl(t_game *game)
{
	t_vec2f	rayend;
	float	triangbase;
	char	chk;

	rayend.x = game->player.pos.x;
	rayend.y = game->player.pos.y;

	chk = coordcheck(game, rayend.x, rayend.y); //TODO: it's writing outside the map
	while (chk != '1' && chk != 0)
	{
		triangbase = (int)(rayend.x + 1) - rayend.x;

		rayend.y += tan(game->player.theta) * triangbase * excenter(cos(game->player.theta));
		squarecent_prop(game, rayend, 4, rgbtocolor(128, 0, 128));

		// rayend.x = (int)(rayend.x + 1);
		rayend.x = rayend.x + excenter(cos(game->player.theta));
		chk = coordcheck(game, rayend.x, rayend.y);
	}

}

int	draw_ray(t_game *game)
{
	drawXgridColl(game);
}