/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:33:44 by qmuntada          #+#    #+#             */
/*   Updated: 2015/08/20 15:45:24 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		check_map(void)
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

void	gravity(t_env *e)
{
	if (e->map.floor[(int)floor(e->p.y / \
				BLOC)][(int)floor(e->p.x / BLOC)] < e->p.foot)
		e->p.foot -= GRAVITY;
	if (e->map.floor[(int)floor(e->p.y / \
				BLOC)][(int)floor(e->p.x / BLOC)] > e->p.foot)
		e->p.foot = e->map.floor[(int)floor(e->p.y / \
				BLOC)][(int)floor(e->p.x / BLOC)];
	e->p.eyes = e->p.foot + 31 + (cos(e->p.bob += 0.15) * 2) + \
				(e->p.crouch == 1 ? -16 : 0);
}

int		expose_hook(t_env *e)
{
	e->ntouch = -1;
	e->delay = (e->delay == 0 ? 1 : 0);
	e->delay2 = !(e->delay + e->delay2 == 1 ? 1 : 0);
	calc_img(e);
	e->distt = 75 + cos(e->p.bob) * 10;
	weapon_handling(e);
	sprite_handling(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	movement(e);
	gravity(e);
	fps(e);
	cursor_move(e->mlx, e->img.width / 2, e->img.height / 2);
	return (1);
}

int		main(void)
{
	t_env e;

	init_env(&e, check_map());
	init_texture(&e);
	mlx_hook(e.win, 2, (1L<<0), &key_press, &e);
	mlx_hook(e.win, 3, (1L<<1), &key_release, &e);
	mlx_hook(e.win, 6, (1L<<6), &mouse, &e);
	mlx_hook(e.win, 4, (1L<<2), &mouse2, &e);
	mlx_loop_hook(e.mlx, &expose_hook, &e);
	mlx_loop(e.mlx);
	return (1);
}
