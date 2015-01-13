/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:34:49 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/13 18:07:14 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	display_weapon(t_env *e, int state)
{
	int		pos;
	float	pas;
	float	x;
	float	y;
	float	bob;

	e->y = e->img.height;
	pas = (128.0 / e->img.width) * 3;
	y = 127;
	bob = ((e->p.forward != 0 || e->p.straff != 0) ? cos(e->p.bob) : 0);
	while ((y -= pas) >= 0 && (e->y -= 1) > 0)
	{
		x = 0;
		e->x = e->img.width / 2 - 1;
		while ((x += pas) < 128 && (e->x += 1) < e->img.width)
		{
			pos = ((int)x * e->tex[state].bpp / 8) + \
					((int)y * e->tex[state].sl);
			e->color = e->tex[state].img[pos] + \
					e->tex[state].img[pos + 1] * 256 \
					+ e->tex[state].img[pos + 2] * 65536;
			if (e->color != 0x980088)
				pixel_put(e, e->x + bob * 25, e->y + abs(bob * 75));
		}
	}
}

void	weapon_handling(t_env *e)
{
	if (e->p.shoot == 1)
		e->p.wpstate++;
	if (e->p.wpstate > 4)
	{
		e->p.wpstate = 0;
		e->p.shoot = 0;
	}
	display_weapon(e, e->p.wpstate + 29);
}
