
#include "wolf.h"

void	pixel_put(t_env *e, int x, int y, int color)
{
	int		pos;
	float	div;

	if (x >= 0 && x < e->img.width && y >= 0 && y < e->img.height)
	{
		pos = (x * e->img.bpp / 8) + (y * e->img.sl);
		div = 1 + (float)e->distt / 50;
		e->img.img[pos] = (color % 256) / div;
		e->img.img[pos + 1] = ((color >> 8) % 256) / div;
		e->img.img[pos + 2] = ((color >> 16) % 256) / div;
	}
}

void		render_pointwv(t_env *e, int num, int tex)
{
	int		pos;
	int		color;

	pos = ((e->vy) * e->texture[tex + 1].bpp / 8) + ((int)e->x * e->texture[tex + 1].sl);
	color = e->texture[tex].img[pos] + \
			e->texture[tex].img[pos + 1] * 256 \
			+ e->texture[tex].img[pos + 2] * 65536;
	pixel_put(e, num, e->px, color);
}

void		render_pointwh(t_env *e, int num, int tex)
{
	int		pos;
	int		color;

	pos = ((e->vx) * e->texture[tex + 1].bpp / 8) + ((int)e->x * e->texture[tex + 1].sl);
	color = e->texture[tex].img[pos] + \
			e->texture[tex].img[pos + 1] * 256 \
			+ e->texture[tex].img[pos + 2] * 65536;
	pixel_put(e, num, e->px, color);
}


void		render_pointfc(t_env *e, int num, int tex)
{
	int		pos;
	int		color;

	pos = ((int)e->x * e->texture[tex].bpp / 8) + ((int)e->y * e->texture[tex].sl);
	color = e->texture[tex].img[pos] + \
			e->texture[tex].img[pos + 1] * 256 \
			+ e->texture[tex].img[pos + 2] * 65536;
	pixel_put(e, num, e->px, color);
}

void	render_points(t_env *e, int x, int y, int n)
{
	int		pos;
	int		color;

	pos = ((((int)e->slist.s[n].uvx % 64) * e->texture[e->slist.s[n].texture].bpp) / 8) + (((int)e->slist.s[n].uvy % 64) * e->texture[e->slist.s[n].texture].sl);
	color = e->texture[e->slist.s[n].texture].img[pos] + \
			e->texture[e->slist.s[n].texture].img[pos + 1] * 256 \
			+ e->texture[e->slist.s[n].texture].img[pos + 2] * 65536;
	if (color != 0x980088)
	{
		pixel_put(e, x, y, color);
		if (x == e->img.width / 2 && y == e->img.height / 2)
			e->slist.s[n].onsight = 1;
	}
}
