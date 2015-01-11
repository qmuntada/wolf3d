
#include "wolf.h"

void	display_weapon(t_env *e, int state)
{
	int		pos;
	int		color;
	float	pas;
	float	x;
	float	y;
	float	bob;

	y = 127;
	bob = 0;
	if (e->p.forward || e->p.straff)
		bob = cos(e->p.bobbing);
	e->y = e->img.height;
	pas = (128.0 / e->img.width) * 3;
	while (y >= 0)
	{
		x = 0;
		e->x = e->img.width / 2;
		while (x < 128)
		{
			pos = ((int)x * e->texture[state].bpp / 8) + ((int)y * e->texture[state].sl);
			color = e->texture[state].img[pos] + \
					e->texture[state].img[pos + 1] * 256 \
					+ e->texture[state].img[pos + 2] * 65536;
			if (color != 0x980088)
				pixel_put(e, e->x + (bob * 25), e->y + abs(bob * 75), color);
			e->x += 1;
			x += pas;
		}
		y -= pas;
		e->y -= 1;
	}
}

void	weapon_handling(t_env *e)
{
	if (e->p.shoot == 1)
		e->p.wpstate++;
	if (e->p.wpstate > 4)
	{
		e->p.wpstate = 0;
		e->p.shoot = 0;
	}
	display_weapon(e, e->p.wpstate + 29);
}
