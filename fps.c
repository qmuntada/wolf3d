
#include "wolf.h"

void	fps(t_env *e)
{
	static int		timestamp;
	static int		fps;
	static int		fps_2;

	if (time(NULL) != timestamp)
	{
		fps_2 = fps;
		fps = 0;
		timestamp = (int)time(NULL);
	}
	else
		fps++;
	mlx_string_put(e->mlx, e->win, 5, 12, 0x000000, ft_itoa(fps_2));
}
