/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:33:48 by qmuntada          #+#    #+#             */
/*   Updated: 2015/10/30 15:30:41 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		mouse(int x, int y, t_env *e)
{
	float	y2;

	if (x != e->mouseX)
	{
		e->p.angle += (e->mouseX - x) * 0.2 * RSPEED;
		e->mouseX = x;
	}
	if (y != e->mouseY)
	{
		e->img.center += (e->mouseY - y) * RSPEED;
		//y2 = (float)(y * (RSPEED / 5));
		//if (y2 + e->img.center > 0 && y2 + e->img.center < e->img.height)
		//	e->img.center += y2;
		e->mouseY = y;
	}
	e->p.angle += (e->p.angle > 360 ? -360 : 0);
	e->p.angle += (e->p.angle < 0 ? 360 : 0);
	return (1);
}

int		mouse2(int button, int x, int y, t_env *e)
{
	x = y;
	y = x;
	if (button == 1 && e->p.shoot == 0)
		e->p.shoot = 1;
	return (1);
}

void	cursor_move(void *mlx_ptr, int x, int y)
{
	/*
	t_xvar		*xvar;
	Window		window;

	xvar = (t_xvar *)mlx_ptr;
	window = xvar->win_list->window;
	XWarpPointer(xvar->display, window, window, 0, 0, 0, 0, x, y);*/
}
