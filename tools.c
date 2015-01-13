/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:34:38 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/13 17:45:11 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		jump(t_env *e)
{
	if (e->p.jump2 < 15 && e->p.eyes <= e->map.ceiling[(int)e->p.y / \
			BLOC][(int)e->p.x / BLOC])
		e->p.foot += GRAVITY + (8 - (e->p.jump2 += 1));
	if (e->p.foot == e->map.floor[(int)(e->p.y / BLOC)][(int)(e->p.x / BLOC)])
	{
		e->p.jump2 = 0;
		return (0);
	}
	return (1);
}

void	init_value(t_env *e, float dist)
{
	e->ax = e->p.x;
	e->ay = e->p.y;
	e->vx = 0;
	e->vy = 0;
	e->distc = dist;
	e->distf = dist;
}
