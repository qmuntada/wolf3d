
# include "wolf.h"

void	init_vector_hori(t_precomp *prec, t_vector *h)
{
	if (prec->angle >= 180 && prec->angle < 360)
	{
		h->y = floor(prec->playy / BLOC) * BLOC + BLOC;
		h->uvy = 64;
	}
	else
	{
		h->y = floor(prec->playy / BLOC) * BLOC - 0.001;
		h->uvy = 0;
	}
	h->x = prec->playx + (prec->playy - h->y) / prec->td_angle;
	h->uvx = (int)h->x % 64;
	h->dist = ((sqrt(pow((prec->playx - h->x), 2.0) + pow((prec->playy - h->y), 2.0))) * prec->fisheye) / ((float)BLOC / 64);
}

void	init_vector_vert(t_precomp *prec, t_vector *v)
{
	if (prec->angle >= 90 && prec->angle < 270)
	{
		v->x = floor(prec->playx / BLOC) * BLOC - 0.001;
		v->uvx = 0;
	}
	else
	{
		v->x = floor(prec->playx / BLOC) * BLOC + BLOC;
		v->uvx = 64;
	}
	v->y = prec->playy + (prec->playx - v->x) * prec->td_angle;
	v->uvy = (int)v->y % 64;
	v->dist = ((sqrt(pow((prec->playx - v->x), 2.0) + pow((prec->playy - v->y), 2.0))) * prec->fisheye) / ((float)BLOC / 64);
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
	list->floorsv = 0;
	list->floorev = 0;
	list->wfloorsv = 0;
	list->wfloorev = 0;
	list->ceilsv = 0;
	list->ceilev = 0;
	list->wceilsv = 0;
	list->wceilev = 0;
	return (list);
}

void	vect_addsort(t_vectlst **blst, t_vector *content, char side)
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

void	vect_clear(t_vectlst **blst)
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
