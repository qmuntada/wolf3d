/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:33:28 by qmuntada          #+#    #+#             */
/*   Updated: 2015/10/30 18:04:28 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	fps(t_env *e)
{
	static int		timestamp;
	static int		fps;
	static int		fps_2;

	if (time(NULL) != timestamp)
	{
		fps_2 = fps;
		fps = 0;
		timestamp = (int)time(NULL);
	}
	else
		fps++;
	mlx_string_put(e->mlx, e->win, 10, 15, 0xFFFFFF, "FPS  :");
	mlx_string_put(e->mlx, e->win, 70, 15, 0xFFFFFF, ft_itoa(fps_2));
	mlx_string_put(e->mlx, e->win, 10, 40, 0xFFFFFF, "LIFE :");
	mlx_string_put(e->mlx, e->win, 70, 40, 0xFFFFFF, ft_itoa(e->p.life));
}
