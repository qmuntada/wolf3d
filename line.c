
# include "wolf.h"

void	pixel_put(t_env *e, int x, int y, int color, int dist)
{
	int		pos;
	float	div;

	if (x >= 0 && x < e->img.width && y >= 0 && y < e->img.height)
	{
		pos = (x * e->img.bpp / 8) + (y * e->img.sl);
		div = 1;
		div += (float)dist / 100;
		e->img.img[pos] = (color % 256) / div;
		e->img.img[pos + 1] = ((color >> 8) % 256) / div;
		e->img.img[pos + 2] = ((color >> 16) % 256) / div;
	}
}

int		calc_wfloor(t_vectlst **list, t_env *e, int *wallf, int *fbot)
{
	(**list).wfloorbot = (e->img.center + ((e->p.eyes * e->img.dist) / (**list).vector.dist) / 2);
	*wallf = e->map.floor[(int)floor(((**list).vector.y) / BLOC)][(int)floor(((**list).vector.x) / BLOC)];
	(**list).wfloortop = (**list).wfloorbot - (((e->p.eyes * e->img.dist) / (**list).vector.dist) * (*wallf / e->p.eyes) / 2);
	if ((**list).wfloorbot > e->hf)
	{
		(**list).wfloorsv = (**list).wfloorbot - e->hf;
		(**list).wfloorbot = e->hf;
	}
	if ((**list).wfloortop < e->hc)
	{
		(**list).wfloorev = e->hc - (**list).wfloortop;
		(**list).wfloortop = e->hc;
	}
	*fbot = (**list).wfloortop;
	if ((**list).wfloortop < e->hf)
		return ((**list).wfloortop);
	return (e->hf);
}

int		calc_wceil(t_vectlst **list, t_env *e, int *wallc, int *cbot)
{
	(**list).wceilbot = (e->img.center + ((e->p.eyes * e->img.dist) / (**list).vector.dist) / 2);
	*wallc = e->map.ceiling[(int)floor(((**list).vector.y) / BLOC)][(int)floor(((**list).vector.x) / BLOC)];
	(**list).wceiltop = (**list).wceilbot - (((e->p.eyes * e->img.dist) / (**list).vector.dist) * (*wallc / e->p.eyes) / 2);
	(**list).wceilbot = (**list).wceiltop - (((e->p.eyes * e->img.dist) / (**list).vector.dist) * ((512 - *wallc) / e->p.eyes) / 2);
	if ((**list).wceilbot < e->hc)
	{
		(**list).wceilsv = e->hc - (**list).wceilbot;
		(**list).wceilbot = e->hc;
	}
	if ((**list).wceiltop > e->hf)
	{
		(**list).wceilev = (**list).wceiltop - e->hf;
		(**list).wceiltop = e->hf;
	}
	*cbot = (**list).wceiltop;
	if ((**list).wceiltop > e->hc)
		return ((**list).wceiltop);
	return (e->hc);
}

int		calc_floor(t_vectlst **list, t_env *e, int wallf, int bot)
{
	(**list).floorbot = (e->img.center + ((e->p.eyes * e->img.dist) / (**list).vector.dist) / 2);
	(**list).floortop = (**list).floorbot - (((e->p.eyes * e->img.dist) / (**list).vector.dist) * (wallf / e->p.eyes) / 2);
	(**list).floorbot = bot;
	if ((**list).floorbot > e->hf)
	{
		(**list).floorsv = (**list).floorbot - e->hf;
		(**list).floorbot = e->hf;
	}
	if ((**list).floortop < e->hc)
	{
		(**list).floorev = e->hc - (**list).floortop;
		(**list).floortop = e->hc;
	}
	if ((**list).floortop < e->hf)
		return ((**list).floortop);
	return (e->hf);
}

int		calc_ceil(t_vectlst **list, t_env *e, int wallc, int bot)
{
	(**list).ceilbot = (e->img.center + ((e->p.eyes * e->img.dist) / (**list).vector.dist) / 2);
	(**list).ceiltop = (**list).ceilbot - (((e->p.eyes * e->img.dist) / (**list).vector.dist) * (wallc / e->p.eyes) / 2);
	(**list).ceilbot = bot;
	if ((**list).ceilbot < e->hc)
	{
		(**list).ceilsv = e->hc - (**list).ceilbot;
		(**list).ceilbot = e->hc;
	}
	if ((**list).ceiltop > e->hf)
	{
		(**list).ceilev = (**list).ceiltop - e->hf;
		(**list).ceiltop = e->hf;
	}
	if ((**list).ceiltop > e->hc)
		return ((**list).ceiltop);
	return (e->hc);
}

void		display_test(t_env *e, t_vectlst *list, int num)
{
	int		color;
	int		pos;
	float	x;
	float	y;
	float	pas;
	int		bot;
	int		top;
	float	pasx;
	float	pasy;
	float	xlen;
	float	ylen;
	float	x1;
	float	y1;
	float	x2;
	float	y2;
	float	ancientx;
	float	ancienty;
	char	ancientside;
	int		n;

	x1 = 0;
	y1 = 0;
	ancientx = e->p.x;
	ancienty = e->p.y;
	ancientside = 'v';
	n = e->line[num].iter;
	while (list && n-- > 0)
	{
			x2 = list->vector.uvx;
			y2 = list->vector.uvy;
			pas = (list->floorbot + list->floorsv) - (list->floortop - list->floorev);
			xlen = x1 - x2;
			ylen = y1 - y2;
			pasx = (-xlen) / pas;
			pasy = (-ylen) / pas;
			x1 += (list->floorsv * pasx);
			y1 += (list->floorsv * pasy);
			x1 += (x1 > 64.0 ? -64.0 : 0);
			x1 += (x1 < 0 ? 64 : 0);
			y1 += (y1 > 64.0 ? -64.0 : 0);
			y1 += (y1 < 0 ? 64 : 0);
			while (list->floorbot >= list->floortop && list->floortop >= 0)
			{
				x1 += (x1 > 64.0 ? -64.0 : 0);
				x1 += (x1 < 0 ? 64 : 0);
				y1 += (y1 > 64.0 ? -64.0 : 0);
				y1 += (y1 < 0 ? 64 : 0);
				if (list->floorbot < e->img.height && list->floorbot >= 0 && x1 >= 0 && x1 <= 64 && y1 >= 0 && y1 <= 64)
				{
					pos = (((int)x1 * e->texture[2].bpp) / 8) + ((int)y1 * e->texture[2].sl);
					color = e->texture[2].img[pos] + \
							e->texture[2].img[pos + 1] * 256 \
							+ e->texture[2].img[pos + 2] * 65536;
					pixel_put(e, num, list->floorbot, color, list->vector.dist);

				}
				list->floorbot = list->floorbot - 1;
				x1 += pasx;
				y1 += pasy;
			}
		pas = ((float)BLOC / ((list->wfloorbot + list->wfloorsv) - (list->wfloortop - list->wfloorev)));
		pas *= ((float)list->wallf / BLOC);
		x = 0 + (list->wfloorsv * pas);
		x += (x > 64.0 ? -64.0 : 0);
		x += (x < 0 ? 64 : 0);
		while (list->wfloorbot >= list->wfloortop && list->wfloortop >= 0 && list->wallf > 0)
		{
			x += (x > 64.0 ? -64.0 : 0);
			x += (x < 0 ? 64.0 : 0);
			if (list->wfloorbot < e->img.height && list->wfloorbot >= 0 && x >= 0 && x <= 64)
			{
				if (list->side == 'v')
				{
					pos = (((int)list->vector.y % 64) * e->texture[1].bpp / 8) + ((int)x * e->texture[1].sl);
					color = e->texture[1].img[pos] + \
							e->texture[1].img[pos + 1] * 256 \
							+ e->texture[1].img[pos + 2] * 65536;
					pixel_put(e, num, list->wfloorbot, color, list->vector.dist);
				}
				else
				{
					pos = (((int)list->vector.x % 64) * e->texture[1].bpp / 8) + ((int)x * e->texture[1].sl);
					color = e->texture[1].img[pos] + \
							e->texture[1].img[pos + 1] * 256 \
							+ e->texture[1].img[pos + 2] * 65536;
					pixel_put(e, num, list->wfloorbot, color, list->vector.dist);
				}
			}
			x += pas;
			list->wfloorbot = list->wfloorbot - 1;
		}
		while (list->ceilbot <= list->ceiltop && list->ceilbot < e->img.height && list->wallc)
		{
			if (list->ceilbot < e->img.height && list->ceilbot >= 0)
				pixel_put(e, num, list->ceilbot, 0x555555, list->vector.dist);
			list->ceilbot = list->ceilbot + 1;
		}
		pas = ((float)BLOC / ((list->wceiltop + list->wceilev) - (list->wceilbot - list->wceilsv)));
		pas *= ((512.0 - (float)list->wallc) / BLOC);
		x = 64 - (list->wceilsv * pas);
		x += ( x > 64.0 ? -64.0 : 0);
		x += ( x < 0 ? 64 : 0);
		while (list->wceilbot <= list->wceiltop && list->wceilbot < e->img.height && list->wceilbot >= 0 && list->wallc < 512)
		{
			x += ( x > 64.0 ? -64.0 : 0);
			x += ( x < 0 ? 64 : 0);
			if (list->wceilbot < e->img.height && list->wceilbot >= 0 && x >= 0 && x <= 64)
			{
				if (list->side == 'v')
				{
					pos = (((int)list->vector.y % 64) * e->texture[1].bpp / 8) + ((int)x * e->texture[1].sl);
					color = e->texture[1].img[pos] + \
							e->texture[1].img[pos + 1] * 256 \
							+ e->texture[1].img[pos + 2] * 65536;
					pixel_put(e, num, list->wceilbot, color, list->vector.dist);
				}
				else
				{
					pos = (((int)list->vector.x % 64) * e->texture[1].bpp / 8) + ((int)x * e->texture[1].sl);
					color = e->texture[1].img[pos] + \
							e->texture[1].img[pos + 1] * 256 \
							+ e->texture[1].img[pos + 2] * 65536;
					pixel_put(e, num, list->wceilbot, color, list->vector.dist);
				}
			}
			x -= pas;
			list->wceilbot = list->wceilbot + 1;
		}
		x1 = (int)list->vector.x % 64;
		y1 = (int)list->vector.y % 64;
		ancientx = list->vector.x;
		ancienty = list->vector.y;
		ancientside = list->side;
		list = list->next;
	}
}

void	line_cleaner(t_env *e, t_vectlst *blist, int num)
{
	t_vectlst		*list;
	int			wallf;
	int			botf;
	int			botc;
	int			wallc;
	int			xtest;

	list = blist;
	e->line[num].iter = 0;
	wallf = e->map.floor[(int)(e->p.y / BLOC)][(int)(e->p.x / BLOC)];
	wallc = e->map.ceiling[(int)(e->p.y / BLOC)][(int)(e->p.x / BLOC)];
	botf = (e->img.center + ((e->p.eyes * e->img.dist) / list->vector.dist) / 2) - (((e->p.eyes * (e->img.dist)) / list->vector.dist) * (wallf / e->p.eyes) / 2);
	botc = (e->img.center + ((e->p.eyes * e->img.dist) / list->vector.dist) / 2) - (((e->p.eyes * (e->img.dist)) / list->vector.dist) * (wallc / e->p.eyes) / 2);
	e->hf = e->img.height;
	e->hc = 0;
	while (list && e->hf > e->hc)
	{
		list->hc = e->hc;
		list->hf = e->hf;
		e->hf = calc_floor(&list, e, wallf, botf);
		e->hc = calc_ceil(&list, e, wallc, botc);
		if (e->line[num].iter == 0 && e->hf < e->img.height)
		{
			xtest = e->img.height;
			while (xtest > e->hf)
			{
				pixel_put(e, num, xtest, 0xBBBBBB, 0);
				xtest--;
			}
		}
		if (e->line[num].iter == 0 && e->hc > 0)
		{
			xtest = 0;
			while (xtest < e->hc)
			{
				pixel_put(e, num, xtest, 0x555555, 0);
				xtest++;
			}
		}
		e->hf = calc_wfloor(&list, e, &wallf, &botf);
		e->hc = calc_wceil(&list, e, &wallc, &botc);
		list->wallc = wallc;
		list->wallf = wallf;
		e->line[num].iter = e->line[num].iter + 1;
		list = list->next;
	}
	display_test(e, blist, num);
	while (e->hf > e->hc && e->hf >= 0 && e->hf <= e->img.height)
	{
		pixel_put(e, num, e->hf, 0xFFFFFF, 0);
		e->hf = e->hf - 1;
	}
}
