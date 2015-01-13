/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:33:39 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/13 17:14:07 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		draw_wallf(t_env *e, t_vectlst *list, int num)
{
	float	pas;

	pas = ((float)BLOC / ((list->wfloorbot + list->wfloorsv) - \
				(list->wfloortop - list->wfloorev)));
	pas *= ((float)list->wallf / BLOC);
	e->x = (list->wfloorsv * pas);
	e->t = e->map.texture[(int)floor(list->vector.y / \
			BLOC)][(int)floor(list->vector.x / BLOC)] * 4 + 2;
	e->px = list->wfloorbot;
	while (e->px >= list->wfloortop)
	{
		e->x += (e->x > 64.0 ? -64.0 : 0);
		if (e->px < e->img.height && e->px >= 0 && e->x >= 0 && e->x <= 64)
		{
			if (list->side == 'v')
				render_pointwv(e, num, e->t + 1);
			else
				render_pointwh(e, num, e->t);
		}
		e->x += pas;
		e->px -= 1;
	}
}

void		draw_wallc(t_env *e, t_vectlst *list, int num)
{
	float	pas;

	pas = ((float)BLOC / ((list->wceiltop + list->wceilev) - \
				(list->wceilbot - list->wceilsv)));
	pas *= ((512.0 - (float)list->wallc) / BLOC);
	e->x = 64 - (list->wceilsv * pas);
	e->t = e->map.texture[(int)floor(list->vector.y / \
			BLOC)][(int)floor(list->vector.x / BLOC)] * 4 + 2;
	e->px = list->wceilbot;
	while (e->px <= list->wceiltop)
	{
		e->x += (e->x < 0 ? 64 : 0);
		if (e->px < e->img.height && e->px >= 0 && e->x >= 0 && e->x <= 64)
		{
			if (list->side == 'v')
				render_pointwv(e, num, e->t + 1);
			else
				render_pointwh(e, num, e->t);
		}
		e->x -= pas;
		e->px += 1;
	}
}

void		draw_floor(t_env *e, t_vectlst *list, int num)
{
	float	pasx;
	float	pasy;
	float	pas;
	float	pasdist;

	pas = (list->floorbot + list->floorsv) - (list->floortop - list->floorev);
	pasx = (-(e->x - list->vector.uvx)) / pas;
	pasy = (-(e->y - list->vector.uvy)) / pas;
	pasdist = (list->vector.dist - e->distf) / pas;
	e->x += (list->floorsv * pasx);
	e->y += (list->floorsv * pasy);
	e->t = e->map.texture[(int)floor(e->ay / \
			BLOC)][(int)floor(e->ax / BLOC)] * 4 + 1;
	e->px = list->floorbot;
	e->distt = e->distf;
	while (e->px >= list->floortop)
	{
		if (e->px < e->img.height && e->px >= 0 && e->x >= 0 \
				&& e->x <= 64 && e->y >= 0 && e->y <= 64)
			render_pointfc(e, num, e->t);
		e->distt += pasdist;
		e->px -= 1;
		e->x += pasx;
		e->y += pasy;
	}
}

void		draw_ceil(t_env *e, t_vectlst *list, int num)
{
	float	pasx;
	float	pasy;
	float	pas;
	float	pasdist;

	pas = (list->ceiltop + list->ceilev) - (list->ceilbot - list->ceilsv);
	pasx = (-(e->x - list->vector.uvx)) / pas;
	pasy = (-(e->y - list->vector.uvy)) / pas;
	pasdist = (list->vector.dist - e->distc) / pas;
	e->x += (list->ceilsv * pasx);
	e->y += (list->ceilsv * pasy);
	e->t = e->map.texture[(int)floor(e->ay / \
			BLOC)][(int)floor(e->ax / BLOC)] * 4 + 4;
	e->px = list->ceilbot;
	e->distt = e->distc;
	while (e->px <= list->ceiltop)
	{
		if (e->px < e->img.height && e->px >= 0 && e->x >= 0 \
				&& e->x <= 64 && e->y >= 0 && e->y <= 64)
			render_pointfc(e, num, e->t);
		e->px += 1;
		e->distt += pasdist;
		e->x += pasx;
		e->y += pasy;
	}
}

void		display_line(t_env *e, t_vectlst *list, int num)
{
	int		n;

	init_value(e, list->vector.dist);
	n = e->line[num].iter;
	while (list && n-- > 0)
	{
		e->dist = list->vector.dist;
		e->x = e->vx;
		e->y = e->vy;
		draw_floor(e, list, num);
		e->x = e->vx;
		e->y = e->vy;
		draw_ceil(e, list, num);
		e->vx = (int)list->vector.x % 64;
		e->vy = (int)list->vector.y % 64;
		e->distt = list->vector.dist;
		draw_wallf(e, list, num);
		draw_wallc(e, list, num);
		e->ax = list->vector.x;
		e->ay = list->vector.y;
		e->distc = list->vector.dist;
		e->distf = list->vector.dist;
		list = list->next;
	}
}
