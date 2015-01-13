/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:34:06 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/13 17:29:07 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	pixel_put(t_env *e, int x, int y)
{
	int		pos;
	float	div;

	if (x >= 0 && x < e->img.width && y >= 0 && y < e->img.height)
	{
		pos = (x * e->img.bpp / 8) + (y * e->img.sl);
		div = 1 + (e->distt / 100.0);
		e->img.img[pos] = (e->color % 256) / div;
		e->img.img[pos + 1] = ((e->color >> 8) % 256) / div;
		e->img.img[pos + 2] = ((e->color >> 16) % 256) / div;
	}
}

void	render_pointwv(t_env *e, int num, int tex)
{
	int		pos;

	pos = ((e->vy) * e->tex[tex + 1].bpp / 8) + \
			((int)e->x * e->tex[tex + 1].sl);
	e->color = e->tex[tex].img[pos] + \
				e->tex[tex].img[pos + 1] * 256 \
				+ e->tex[tex].img[pos + 2] * 65536;
	pixel_put(e, num, e->px);
}

void	render_pointwh(t_env *e, int num, int tex)
{
	int		pos;

	pos = ((e->vx) * e->tex[tex + 1].bpp / 8) + \
			((int)e->x * e->tex[tex + 1].sl);
	e->color = e->tex[tex].img[pos] + \
				e->tex[tex].img[pos + 1] * 256 \
				+ e->tex[tex].img[pos + 2] * 65536;
	pixel_put(e, num, e->px);
}

void	render_pointfc(t_env *e, int num, int tex)
{
	int		pos;

	pos = ((int)e->x * e->tex[tex].bpp / 8) + ((int)e->y * e->tex[tex].sl);
	e->color = e->tex[tex].img[pos] + \
				e->tex[tex].img[pos + 1] * 256 \
				+ e->tex[tex].img[pos + 2] * 65536;
	pixel_put(e, num, e->px);
}

void	render_points(t_env *e, int x, int y, int n)
{
	int		pos;

	pos = ((((int)e->slist.s[n].uvx) * e->tex[e->slist.s[n].texture \
		+ e->slist.s[n].state].bpp) / 8) + (((int)e->slist.s[n].uvy) * \
		e->tex[e->slist.s[n].texture + e->slist.s[n].state].sl);
	e->color = e->tex[e->slist.s[n].texture + e->slist.s[n].state].img[pos] + \
				e->tex[e->slist.s[n].texture + \
				e->slist.s[n].state].img[pos + 1] * 256 \
				+ e->tex[e->slist.s[n].texture + \
				e->slist.s[n].state].img[pos + 2] * 65536;
	if (e->color != 0x980088)
	{
		pixel_put(e, x, y);
		if (x == e->img.width / 2 && y == e->img.height / 2)
			e->ntouch = n;
	}
}
