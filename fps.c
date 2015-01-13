/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:33:28 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/13 16:33:30 by qmuntada         ###   ########.fr       */
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
	mlx_string_put(e->mlx, e->win, 5, 12, 0xFFFFFF, "fps :");
	mlx_string_put(e->mlx, e->win, 40, 12, 0xFFFFFF, ft_itoa(fps_2));
	mlx_string_put(e->mlx, e->win, 5, 30, 0xFFFFFF, "life :");
	mlx_string_put(e->mlx, e->win, 50, 30, 0xFFFFFF, ft_itoa(e->p.life));
}
