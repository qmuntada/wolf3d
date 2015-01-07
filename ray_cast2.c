
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
