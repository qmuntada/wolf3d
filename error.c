/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:33:18 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/13 16:33:20 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	err_map(void)
{
	ft_putstr_fd("Wolf3d: Error: Included map have incorrect data !\n", 2);
	exit(EXIT_FAILURE);
}

void	err_texture(void)
{
	ft_putstr_fd("Wolf3d: Error: Error while loading texture\n", 2);
	exit(EXIT_FAILURE);
}
