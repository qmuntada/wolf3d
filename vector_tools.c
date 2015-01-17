/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:34:44 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/17 17:04:25 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		vect_init(t_vectlst **list)
{
	(**list).floorev = 0;
	(**list).floorsv = 0;
	(**list).floorbot = 0;
	(**list).floortop = 0;
	(**list).wfloorsv = 0;
	(**list).wfloorev = 0;
	(**list).wfloorbot = 0;
	(**list).wfloortop = 0;
	(**list).ceilsv = 0;
	(**list).ceilev = 0;
	(**list).ceilbot = 0;
	(**list).ceiltop = 0;
	(**list).wceilsv = 0;
	(**list).wceilev = 0;
	(**list).wceilbot = 0;
	(**list).wceiltop = 0;
	(**list).wallc = 0;
	(**list).wallf = 0;
	(**list).hc = 0;
	(**list).hf = 0;
}

t_vectlst	*vect_new(t_vector *content, char side)
{
	t_vectlst	*list;
	t_vector	ctnt;

	ctnt.x = content->x;
	ctnt.y = content->y;
	ctnt.dist = content->dist;
	ctnt.uvx = content->uvx;
	ctnt.uvy = content->uvy;
	list = malloc(sizeof(t_vectlst));
	list->side = side;
	list->next = NULL;
	list->vector = ctnt;
	vect_init(&list);
	return (list);
}

void		vect_addsort(t_vectlst **blst, t_vector *content, char side)
{
	t_vectlst	*tmp;
	t_vectlst	*tmp2;
	t_vectlst	**tmp3;

	if (*blst)
	{
		tmp = vect_new(content, side);
		tmp2 = *blst;
		tmp3 = &*blst;
		while (tmp2 && tmp2->vector.dist < tmp->vector.dist)
		{
			tmp3 = &tmp2->next;
			tmp2 = tmp2->next;
		}
		*tmp3 = tmp;
		tmp->next = tmp2;
	}
	else
		*blst = vect_new(content, side);
}

void		vect_clear(t_vectlst **blst)
{
	t_vectlst *list;
	t_vectlst *tmp;

	list = *blst;
	tmp = NULL;
	while (list)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		free(list);
		list = tmp;
	}
	*blst = NULL;
}
