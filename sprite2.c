/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 17:01:50 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/07 18:30:51 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	find_limit(t_env *e, int x, int *top, int *bot, int n)
{
	t_vectlst		*list;
	float			rdist;
	int				i;

	*bot = -1;
	*top = -1;
	if (x >= 0 && x < e->img.width)
	{
		rdist = e->slist.s[n].dist * ((cos((e->p.angle - e->slist.s[n].rel_angle) / 180 * M_PI)));
		i = e->line[x].iter;
		list = e->line[x].list;
		while (i-- > 0 && list->next && rdist > list->next->vector.dist)
			list = list->next;
	}
	if (x >= 0 && x < e->img.width && list && i > 0)
	{
		*bot = list->hf;
		*top = list->hc;
	}
}

void	display_sprite(t_env *e, int n, float pas)
{
	float	x;
	float	y;
	int		toplimit;
	int		botlimit;
	int		pos;
	int		color;

	e->slist.s[n].uvx = 0;
	x = e->slist.s[n].botx - 1;
	e->dist = e->slist.s[n].dist;
	while (++x < e->slist.s[n].topx)
	{
		y = e->slist.s[n].topy - 1;
		e->slist.s[n].uvy = 0;
		botlimit = e->img.height;
		toplimit = 0;
		if (e->slist.s[n].dist > 24)
			find_limit(e, x, &toplimit, &botlimit, n);
		while (++y < e->slist.s[n].boty)
		{
			if (y >= toplimit && y <= botlimit && x >= 0 && x < e->img.width && y >= 0 && y < e->img.height)
			{
				pos = ((((int)e->slist.s[n].uvx % 64) * e->texture[e->slist.s[n].texture].bpp) / 8) + (((int)e->slist.s[n].uvy % 64) * e->texture[e->slist.s[n].texture].sl);
				color = e->texture[e->slist.s[n].texture].img[pos] + \
						e->texture[e->slist.s[n].texture].img[pos + 1] * 256 \
						+ e->texture[e->slist.s[n].texture].img[pos + 2] * 65536;
				if (color != 0x980088)
				{
					pixel_put(e, x, y, color);
					if (x == e->img.width / 2 && y == e->img.height / 2)
						e->slist.s[n].onsight = 1;
				}
			}
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

	e->slist.s[n].rel_angle = -(atan2(e->slist.s[n].y - e->p.y, e->slist.s[n].x - e->p.x) * (180 / M_PI));
	e->slist.s[n].rel_angle += (e->slist.s[n].rel_angle < 0 ? 360 : 0);
	ytmp = e->p.angle + 30 - e->slist.s[n].rel_angle;
	if (e->slist.s[n].rel_angle > 270 && e->p.angle < 90)
		ytmp += 360;
	if (e->p.angle > 270 && e->slist.s[n].rel_angle < 90)
		ytmp -= 360;
	xtmp = ytmp * (e->img.width / 60.0);
	e->slist.s[n].boty = (e->img.center + ((e->p.eyes * e->img.dist) / e->slist.s[n].dist) / 2);
	e->slist.s[n].topy = e->slist.s[n].boty - (((e->p.eyes * e->img.dist) / e->slist.s[n].dist) * ((e->slist.s[n].z + 64) / e->p.eyes) / 2);
	e->slist.s[n].boty = e->slist.s[n].boty - (((e->p.eyes * e->img.dist) / e->slist.s[n].dist) * (e->slist.s[n].z / e->p.eyes) / 2);
	e->slist.s[n].botx = xtmp - ((e->slist.s[n].boty - e->slist.s[n].topy) / 2);
	e->slist.s[n].topx = xtmp + ((e->slist.s[n].boty - e->slist.s[n].topy) / 2);
	pas = (float)BLOC / (e->slist.s[n].boty - e->slist.s[n].topy);
	return (pas);
}
