/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:34:26 by qmuntada          #+#    #+#             */
/*   Updated: 2015/08/20 15:46:32 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	sprite_shoot(t_env *e, int mov, int i)
{
	if (mov == 1 && e->slist.s[i].attack > 0 && e->slist.s[i].state == 2)
	{
		e->slist.s[i].state += (((int)e->p.bob % 2) == 1 ? e->delay : 0);
		if (e->slist.s[i].state == 3)
			e->p.life -= (e->delay2 == 0 ? (e->slist.s[i].texture / 5) : 0);
	}
	if (mov == 1 && e->slist.s[i].attack == 0 && e->delay == 0)
	{
		e->slist.s[i].attack = 1;
		e->slist.s[i].state = 2;
	}
	if (e->slist.s[i].attack > 0)
		e->slist.s[i].attack += (e->slist.s[i].attack == 10 ? -10 : 1);
}

int		path_correct(t_env *e, int i, int type)
{
	int		v;

	if (type == 1)
	{
		v = (e->slist.s[i].x > e->p.x ? -3 : 3);
		if (e->map.floor[(int)e->slist.s[i].y / \
				BLOC][(int)(e->slist.s[i].x + v) / BLOC] == \
				e->map.floor[(int)e->slist.s[i].y / \
				BLOC][(int)e->slist.s[i].x / BLOC])
		{
			e->slist.s[i].x += v;
			return (0);
		}
	}
	v = (e->slist.s[i].y > e->p.y ? -3 : 3);
	if (e->map.floor[(int)(e->slist.s[i].y + v) / \
			BLOC][(int)e->slist.s[i].x / BLOC] == \
			e->map.floor[(int)e->slist.s[i].y / \
			BLOC][(int)e->slist.s[i].x / BLOC])
	{
		e->slist.s[i].y += v;
		return (0);
	}
	return (1);
}

int		path_finding(t_env *e, int i)
{
	int		x;
	int		y;

	x = fabsf(e->p.x - e->slist.s[i].x);
	y = fabsf(e->p.y - e->slist.s[i].y);
	if ((e->slist.s[i].texture == 34 && e->slist.s[i].dist > 32) || \
			(e->slist.s[i].texture == 44 && e->slist.s[i].dist > 200))
	{
		if (y < x)
			return (path_correct(e, i, 1));
		else
			return (path_correct(e, i, 2));
		e->slist.s[i].state = (e->slist.s[i].state == 0 ? \
				(int)e->p.bob % 2 : 0);
	}
	return (1);
}

void	sprite_handling(t_env *e)
{
	int		i;

	i = -1;
	while (++i < e->slist.n)
	{
		if (e->slist.s[i].life < 0)
		{
			e->slist.s[i].state += (e->slist.s[i].state == 9 ? 0 : e->delay);
			e->slist.s[i].size = 8;
		}
		else if (e->slist.s[i].attack == 0)
			e->slist.s[i].state = 0;
		if (e->slist.s[i].attitude == 1 && e->slist.s[i].dist < 200 \
				&& e->slist.s[i].life > 0)
		{
			sprite_shoot(e, path_finding(e, i), i);
		}
	}
	if (e->ntouch != -1 && e->slist.s[e->ntouch].life >= 0 \
			&& e->p.wpstate != 0 && e->slist.s[e->ntouch].attitude == 1)
	{
		e->slist.s[e->ntouch].life -= (e->p.wpstate == 1 ? 34 : 0);
		e->slist.s[e->ntouch].state = 4;
	}
}
