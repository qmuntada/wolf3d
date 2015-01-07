#include "wolf.h"

static int		check_map()
{
	int		fd;

	fd = open("map", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Wolf3d: Error: File not found !\n", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void		gravity(t_env *e)
{
	if (e->map.floor[(int)floor(e->p.y / BLOC)][(int)floor(e->p.x / BLOC)] < e->p.foot)
		e->p.foot -= GRAVITY;
	if (e->map.floor[(int)floor(e->p.y / BLOC)][(int)floor(e->p.x / BLOC)] > e->p.foot)
		e->p.foot = e->map.floor[(int)floor(e->p.y / BLOC)][(int)floor(e->p.x / BLOC)];
	e->p.eyes = e->p.foot + 31 + (cos(e->p.bobbing += 0.15) * 2) + (e->p.crouch == 1 ? -16 : 0);
}

static int		expose_hook(t_env *e)
{
	calc_img(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	movement(e);
	gravity(e);
	fps(e);
	cursor_move(e->mlx, e->img.width / 2, e->img.height / 2);
	return (1);
}

int				main(int ac, char **av)
{
	t_env e;

	init_env(&e, check_map());
	init_texture(&e);
	mlx_hook(e.win, KeyPress, KeyPressMask, &key_press, &e);
	mlx_hook(e.win, KeyRelease, KeyReleaseMask, &key_release, &e);
	mlx_hook(e.win, MotionNotify, PointerMotionMask, &mouse, &e);
	mlx_loop_hook(e.mlx, &expose_hook, &e);
	mlx_loop(e.mlx);
	return (1);
}
