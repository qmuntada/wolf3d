/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:34:21 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/13 18:10:43 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	find_limit(t_env *e, int x, int n)
{
	t_vectlst		*list;
	float			rdist;
	int				i;

	e->bot = -1;
	e->top = -1;
	if (x >= 0 && x < e->img.width)
	{
		rdist = e->slist.s[n].dist * ((cos((e->p.angle - \
							e->slist.s[n].rel_angle) / 180 * M_PI)));
		i = e->line[x].iter;
		list = e->line[x].list;
		while (i-- > 0 && list->next && rdist > list->next->vector.dist)
			list = list->next;
	}
	if (x >= 0 && x < e->img.width && list && i > 0)
	{
		e->bot = list->hf;
		e->top = list->hc;
	}
}

void	display_sprite(t_env *e, int n, float pas)
{
	float	x;
	float	y;

	e->slist.s[n].uvx = 0;
	x = e->slist.s[n].botx - 1;
	e->distt = e->slist.s[n].dist;
	while (++x < e->slist.s[n].topx)
	{
		y = e->slist.s[n].topy - 1;
		e->slist.s[n].uvy = 0;
		find_limit(e, x, n);
		while (++y < e->slist.s[n].boty)
		{
			if (y >= e->top && y <= e->bot && x >= 0 && x < e->img.width \
					&& y >= 0 && y < e->img.height)
				render_points(e, x, y, n);
			e->slist.s[n].uvy += pas;
		}
		e->slist.s[n].uvx += pas;
	}
}

float	get_sprite_coord(t_env *e, int n)
{
	float	ytmp;
	float	xtmp;
	float	pas;

	e->slist.s[n].rel_angle = -(atan2(e->slist.s[n].y - \
				e->p.y, e->slist.s[n].x - e->p.x) * (180 / M_PI));
	e->slist.s[n].rel_angle += (e->slist.s[n].rel_angle < 0 ? 360 : 0);
	ytmp = e->p.angle + 30 - e->slist.s[n].rel_angle;
	if (e->slist.s[n].rel_angle > 270 && e->p.angle < 90)
		ytmp += 360;
	if (e->p.angle > 270 && e->slist.s[n].rel_angle < 90)
		ytmp -= 360;
	xtmp = ytmp * (e->img.width / 60.0);
	e->slist.s[n].boty = (e->img.center + ((e->p.eyes * e->img.dist) / \
			e->slist.s[n].dist) / 2);
	e->slist.s[n].topy = e->slist.s[n].boty - (((e->p.eyes * e->img.dist) / \
			e->slist.s[n].dist) * ((e->slist.s[n].z + 64) / e->p.eyes) / 2);
	e->slist.s[n].boty = e->slist.s[n].boty - (((e->p.eyes * e->img.dist) / \
			e->slist.s[n].dist) * (e->slist.s[n].z / e->p.eyes) / 2);
	e->slist.s[n].botx = xtmp - ((e->slist.s[n].boty - e->slist.s[n].topy) / 2);
	e->slist.s[n].topx = xtmp + ((e->slist.s[n].boty - e->slist.s[n].topy) / 2);
	pas = (float)BLOC / (e->slist.s[n].boty - e->slist.s[n].topy);
	return (pas);
}
