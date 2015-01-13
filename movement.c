/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:41:13 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/13 17:20:49 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	movefront(t_env *e)
{
	float	x;
	float	y;
	float	dist;

	x = e->p.x + MSPEED * cos(e->p.angle / 180 * M_PI);
	dist = ((sqrt(pow((x - e->slist.s[e->slist.n - 1].x), 2.0) + \
					pow((e->p.y - e->slist.s[e->slist.n - 1].y), 2.0)))) / \
					((float)BLOC / 64);
	if (e->map.floor[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
		e->p.x += MSPEED * cos(e->p.angle / 180 * M_PI);
	y = e->p.y - MSPEED * sin(e->p.angle / 180 * M_PI);
	dist = ((sqrt(pow((e->p.x - e->slist.s[e->slist.n - 1].x), 2.0) + \
					pow((y - e->slist.s[e->slist.n - 1].y), 2.0)))) \
					/ ((float)BLOC / 64);
	if (e->map.floor[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
		e->p.y -= MSPEED * sin(e->p.angle / 180 * M_PI);
}

void	moveback(t_env *e)
{
	float	x;
	float	y;
	float	dist;

	x = e->p.x - MSPEED * cos(e->p.angle / 180 * M_PI);
	dist = ((sqrt(pow((x - e->slist.s[e->slist.n - 1].x), 2.0) + \
					pow((e->p.y - e->slist.s[e->slist.n - 1].y), 2.0)))) \
					/ ((float)BLOC / 64);
	if (e->map.floor[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
		e->p.x -= MSPEED * cos(e->p.angle / 180 * M_PI);
	y = e->p.y + MSPEED * sin(e->p.angle / 180 * M_PI);
	dist = ((sqrt(pow((e->p.x - e->slist.s[e->slist.n - 1].x), 2.0) + \
					pow((y - e->slist.s[e->slist.n - 1].y), 2.0)))) \
					/ ((float)BLOC / 64);
	if (e->map.floor[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
		e->p.y += MSPEED * sin(e->p.angle / 180 * M_PI);
}

void	moveright(t_env *e)
{
	float	x;
	float	y;
	float	dist;

	x = e->p.x + MSPEED * sin(e->p.angle / 180 * M_PI);
	dist = ((sqrt(pow((x - e->slist.s[e->slist.n - 1].x), 2.0) + \
					pow((e->p.y - e->slist.s[e->slist.n - 1].y), 2.0)))) / \
					((float)BLOC / 64);
	if (e->map.floor[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
		e->p.x += MSPEED * sin(e->p.angle / 180 * M_PI);
	y = e->p.y + MSPEED * cos(e->p.angle / 180 * M_PI);
	dist = ((sqrt(pow((e->p.x - e->slist.s[e->slist.n - 1].x), 2.0) + \
					pow((y - e->slist.s[e->slist.n - 1].y), 2.0)))) \
					/ ((float)BLOC / 64);
	if (e->map.floor[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
		e->p.y += MSPEED * cos(e->p.angle / 180 * M_PI);
}

void	moveleft(t_env *e)
{
	float	x;
	float	y;
	float	dist;

	x = e->p.x - MSPEED * sin(e->p.angle / 180 * M_PI);
	dist = ((sqrt(pow((x - e->slist.s[e->slist.n - 1].x), 2.0) + \
					pow((e->p.y - e->slist.s[e->slist.n - 1].y), 2.0)))) \
					/ ((float)BLOC / 64);
	if (e->map.floor[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
		e->p.x -= MSPEED * sin(e->p.angle / 180 * M_PI);
	y = e->p.y - MSPEED * cos(e->p.angle / 180 * M_PI);
	dist = ((sqrt(pow((e->p.x - e->slist.s[e->slist.n - 1].x), 2.0) + \
					pow((y - e->slist.s[e->slist.n - 1].y), 2.0)))) \
					/ ((float)BLOC / 64);
	if (e->map.floor[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
		e->p.y -= MSPEED * cos(e->p.angle / 180 * M_PI);
}
