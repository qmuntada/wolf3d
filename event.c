/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:33:23 by qmuntada          #+#    #+#             */
/*   Updated: 2015/10/30 15:37:20 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	movement(t_env *e)
{
	if (e->p.forward == -1)
		moveback(e);
	else if (e->p.forward == 1)
		movefront(e);
	if (e->p.straff == 1)
		moveleft(e);
	if (e->p.straff == -1)
		moveright(e);
	if (e->p.jump == 1)
		e->p.jump = jump(e);
}

int		key_press(int keycode, t_env *e)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == W || keycode == S)
		e->p.forward = (keycode == S ? -1 : 1);
	else if (keycode == A || keycode == D)
		e->p.straff = (keycode == D ? -1 : 1);
	else if (keycode == SPACE && e->p.jump == 0)
		e->p.jump = 1;
	else if (keycode == C)
		e->p.crouch = 1;
	return (0);
}

int		key_release(int keycode, t_env *e)
{
	if (keycode == W || keycode == S)
		e->p.forward = 0;
	else if (keycode == A || keycode == D)
		e->p.straff = 0;
	else if (keycode == C)
		e->p.crouch = 0;
	return (0);
}
