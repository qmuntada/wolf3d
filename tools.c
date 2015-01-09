
# include "wolf.h"

int		jump(t_env *e)
{
	if (e->p.jump2 < 15 && e->p.eyes <= e->map.ceiling[(int)e->p.y / BLOC][(int)e->p.x / BLOC])
		e->p.foot += GRAVITY + (8 - (e->p.jump2 += 1));
	if (e->p.foot == e->map.floor[(int)(e->p.y / BLOC)][(int)(e->p.x / BLOC)])
	{
		e->p.jump2 = 0;
		return (0);
	}
	return (1);
}

void	pixel_put(t_env *e, int x, int y, int color)
{
	int		pos;
	float	div;

	if (x >= 0 && x < e->img.width && y >= 0 && y < e->img.height)
	{
		pos = (x * e->img.bpp / 8) + (y * e->img.sl);
		div = 1;
		div += (float)e->dist / 50;
		e->img.img[pos] = (color % 256) / div;
		e->img.img[pos + 1] = ((color >> 8) % 256) / div;
		e->img.img[pos + 2] = ((color >> 16) % 256) / div;
	}
}
