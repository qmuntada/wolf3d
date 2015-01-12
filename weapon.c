
#include "wolf.h"

void	display_weapon(t_env *e, int state)
{
	int		pos;
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
			pos = ((int)x * e->tex[state].bpp / 8) + ((int)y * e->tex[state].sl);
			e->color = e->tex[state].img[pos] + \
					e->tex[state].img[pos + 1] * 256 \
					+ e->tex[state].img[pos + 2] * 65536;
			if (e->color != 0x980088)
				pixel_put(e, e->x + (bob * 25), e->y + abs(bob * 75));
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
