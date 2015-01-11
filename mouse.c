
#include "wolf.h"

int		mouse(int x, int y, t_env *e)
{
	float	y2;

	if (x != e->img.width / 2)
	{
		e->p.angle += (((float)(e->img.width / 2.0) - x) / RSPEED);
	}
	if (y != e->img.height / 2)
	{
		y2 = (float)(((e->img.height / 2.0) - y) / 2.0) * (RSPEED / 5);
		if (y2 + e->img.center > 0 && y2 + e->img.center < e->img.height)
			e->img.center += y2;
	}
	e->p.angle += (e->p.angle > 360 ? -360 : 0);
	e->p.angle += (e->p.angle < 0 ? 360 : 0);
	return (1);
}

int		mouse2(int button, int x, int y, t_env *e)
{
	if (button == 1 && e->p.shoot == 0)
		e->p.shoot = 1;
	return (1);
}

void	cursor_move(void *mlx_ptr, int x, int y)
{
	t_xvar*		xvar;
	Window		window;

	xvar = (t_xvar *)mlx_ptr;
	window = xvar->win_list->window;
	XWarpPointer(xvar->display, window, window, 0, 0, 0, 0, x, y);
}
