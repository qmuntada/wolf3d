/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:33:58 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/13 17:25:47 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	cast_hori(t_precomp *prec, t_vector *r)
{
	if (prec->angle >= 180 && prec->angle < 360)
	{
		r->y += BLOC;
		r->x -= (BLOC / prec->td_angle);
		r->uvy = 64;
	}
	else
	{
		r->y -= BLOC;
		r->x += (BLOC / prec->td_angle);
		r->uvy = 0;
	}
	r->uvx = (int)r->x % 64;
	r->dist = ((sqrt(pow((prec->playx - r->x), 2.0) + \
					pow((prec->playy - r->y), 2.0))) * prec->fisheye)\
					/ ((float)BLOC / 64);
}

void	cast_vert(t_precomp *prec, t_vector *r)
{
	if (prec->angle >= 90 && prec->angle < 270)
	{
		r->x -= BLOC;
		r->y += (BLOC * prec->td_angle);
		r->uvx = 0;
	}
	else
	{
		r->x += BLOC;
		r->y -= (BLOC * prec->td_angle);
		r->uvx = 64;
	}
	r->uvy = (int)r->y % 64;
	r->dist = ((sqrt(pow((prec->playx - r->x), 2.0) + \
					pow((prec->playy - r->y), 2.0))) * prec->fisheye)\
					/ ((float)BLOC / 64);
}

void	cast_ray(t_precomp *prec, t_map *map, t_vectlst **list)
{
	t_vector	rh;
	t_vector	rv;

	init_vector_vert(prec, &rv);
	while ((rv.x >= 0 && rv.x < prec->mwidth && rv.y >= 0 && rv.y <
				prec->mheight) && map->floor[(int)(rv.y / BLOC)][(int)(rv.x /
				BLOC)] < map->ceiling[(int)(rv.y / BLOC)][(int)(rv.x / BLOC)])
	{
		vect_addsort(*&list, &rv, 'v');
		cast_vert(prec, &rv);
	}
	init_vector_hori(prec, &rh);
	while ((rh.x >= 0 && rh.x < prec->mwidth && rh.y >= 0 && rh.y <
				prec->mheight) && map->floor[(int)(rh.y / BLOC)][(int)(rh.x /
				BLOC)] < map->ceiling[(int)(rh.y / BLOC)][(int)(rh.x / BLOC)])
	{
		vect_addsort(*&list, &rh, 'h');
		cast_hori(prec, &rh);
	}
	if (rh.dist > rv.dist && rv.x >= 0 && rv.x < prec->mwidth && \
			rv.y >= 0 && rv.y < prec->mheight)
		vect_addsort(*&list, &rv, 'v');
	else if (rh.dist < rv.dist && rh.x >= 0 && rh.x < prec->mwidth && \
			rh.y >= 0 && rh.y < prec->mheight)
		vect_addsort(*&list, &rh, 'h');
}

void	calc_img(t_env *e)
{
	int		scanline;
	float	ray_ang;

	scanline = -1;
	ray_ang = e->p.angle + 30.0;
	while (++scanline < e->img.width)
	{
		pre_comput(e, ray_ang);
		cast_ray(&e->precomp, &e->map, &e->line[scanline].list);
		line_cleaner(e, e->line[scanline].list, scanline);
		ray_ang -= e->img.angle_w;
	}
	sprite_display(e);
	scanline = -1;
	while (++scanline < e->img.width)
		vect_clear(&e->line[scanline].list);
}
