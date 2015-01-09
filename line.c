
# include "wolf.h"

int		calc_wfloor(t_vectlst **list, t_env *e, int *wallf, int *fbot)
{
	(**list).wfloorbot = (e->img.center + ((e->p.eyes * e->img.dist) / (**list).vector.dist) / 2);
	*wallf = e->map.floor[(int)floor(((**list).vector.y) / BLOC)][(int)floor(((**list).vector.x) / BLOC)];
	(**list).wallf = *wallf;
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
	(**list).wallc = *wallc;
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

void		render_pointwv(t_env *e, int num, int dist, int tex)
{
	int		pos;
	int		color;

	pos = ((e->vy) * e->texture[tex + 1].bpp / 8) + ((int)e->x * e->texture[tex + 1].sl);
	color = e->texture[tex].img[pos] + \
			e->texture[tex].img[pos + 1] * 256 \
			+ e->texture[tex].img[pos + 2] * 65536;
	pixel_put(e, num, e->px, color);
}

void		render_pointwh(t_env *e, int num, int dist, int tex)
{
	int		pos;
	int		color;

	pos = ((e->vx) * e->texture[tex + 1].bpp / 8) + ((int)e->x * e->texture[tex + 1].sl);
	color = e->texture[tex].img[pos] + \
			e->texture[tex].img[pos + 1] * 256 \
			+ e->texture[tex].img[pos + 2] * 65536;
	pixel_put(e, num, e->px, color);
}

void		draw_wallf(t_env *e, t_vectlst *list, int num)
{
	float	pas;
	int		tex;

	pas = ((float)BLOC / ((list->wfloorbot + list->wfloorsv) - (list->wfloortop - list->wfloorev)));
	pas *= ((float)list->wallf / BLOC);
	e->x = 0 + (list->wfloorsv * pas);
	tex = e->map.texture[(int)floor(list->vector.y / BLOC)][(int)floor(list->vector.x / BLOC)] * 4 + 2;
	e->px = list->wfloorbot;
	while (e->px >= list->wfloortop && e->px >= 0 && e->px <= e->img.height)
	{
		e->x += (e->x > 64.0 ? -64.0 : 0);
		e->x += (e->x < 0 ? 64.0 : 0);
		if (e->px < e->img.height && e->px >= 0 && e->x >= 0 && e->x <= 64)
		{
			if (list->side == 'v')
				render_pointwv(e, num, list->vector.dist, tex + 1);
			else
				render_pointwh(e, num, list->vector.dist, tex);
		}
		e->x += pas;
		e->px -= 1;
	}
}

void		draw_wallc(t_env *e, t_vectlst *list, int num)
{
	float	pas;
	float	tex;

	pas = ((float)BLOC / ((list->wceiltop + list->wceilev) - (list->wceilbot - list->wceilsv)));
	pas *= ((512.0 - (float)list->wallc) / BLOC);
	e->x = 64 - (list->wceilsv * pas);
	tex = e->map.texture[(int)floor(list->vector.y / BLOC)][(int)floor(list->vector.x / BLOC)] * 4 + 2;
	e->px = list->wceilbot;
	while (e->px <= list->wceiltop && e->px <= e->img.height && e->px >= 0)
	{
		e->x += (e->x > 64.0 ? -64.0 : 0);
		e->x += (e->x < 0 ? 64 : 0);
		if (e->px < e->img.height && e->px >= 0 && e->x >= 0 && e->x <= 64)
		{
			if (list->side == 'v')
				render_pointwv(e, num, list->vector.dist, tex + 1);
			else
				render_pointwh(e, num, list->vector.dist, tex);
		}
		e->x -= pas;
		e->px += 1;
	}
}

void		display_test(t_env *e, t_vectlst *list, int num)
{
	int		color;
	int		pos;
	float	pas;
	float	pasx;
	float	pasy;
	float	x1;
	float	y1;
	float	ancientx;
	float	ancienty;
	int		n;
	int		tex;

	x1 = 0;
	y1 = 0;
	ancientx = e->p.x;
	ancienty = e->p.y;
	n = e->line[num].iter;
	while (list && n-- > 0)
	{
		e->dist = list->vector.dist;
		pas = (list->floorbot + list->floorsv) - (list->floortop - list->floorev);
		pasx = (-(x1 - list->vector.uvx)) / pas;
		pasy = (-(y1 - list->vector.uvy)) / pas;
		x1 += (list->floorsv * pasx);
		y1 += (list->floorsv * pasy);
		tex = e->map.texture[(int)floor(ancienty / BLOC)][(int)floor(ancientx / BLOC)] * 4 + 1;
		while (list->floorbot >= list->floortop && list->floortop >= 0)
		{
			x1 += (x1 > 64.0 ? -64.0 : 0);
			x1 += (x1 < 0 ? 64 : 0);
			y1 += (y1 > 64.0 ? -64.0 : 0);
			y1 += (y1 < 0 ? 64 : 0);
			if (list->floorbot < e->img.height && list->floorbot >= 0 && x1 >= 0 && x1 <= 64 && y1 >= 0 && y1 <= 64)
			{
				pos = (((int)x1 * e->texture[tex].bpp) / 8) + ((int)y1 * e->texture[tex].sl);
				color = e->texture[tex].img[pos] + \
						e->texture[tex].img[pos + 1] * 256 \
						+ e->texture[tex].img[pos + 2] * 65536;
				pixel_put(e, num, list->floorbot, color);

			}
			list->floorbot = list->floorbot - 1;
			x1 += pasx;
			y1 += pasy;
		}
		while (list->ceilbot <= list->ceiltop && list->ceilbot < e->img.height && list->wallc)
		{
			if (list->ceilbot < e->img.height && list->ceilbot >= 0)
				pixel_put(e, num, list->ceilbot, 0x555555);
			list->ceilbot = list->ceilbot + 1;
		}
		e->vy = (int)list->vector.y % 64;
		e->vx = (int)list->vector.x % 64;
		draw_wallf(e, list, num);
		draw_wallc(e, list, num);
		x1 = (int)list->vector.x % 64;
		y1 = (int)list->vector.y % 64;
		ancientx = list->vector.x;
		ancienty = list->vector.y;
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

	list = blist;
	e->line[num].iter = 0;
	wallf = e->map.floor[(int)floor(e->p.y / BLOC)][(int)floor(e->p.x / BLOC)];
	wallc = e->map.ceiling[(int)floor(e->p.y / BLOC)][(int)floor(e->p.x / BLOC)];
	botf = e->img.height;
	botc = 0;
	e->hf = e->img.height;
	e->hc = 0;
	while (list && e->hf > e->hc)
	{
		list->hc = e->hc;
		list->hf = e->hf;
		e->hf = calc_floor(&list, e, wallf, botf);
		e->hc = calc_ceil(&list, e, wallc, botc);
		e->hf = calc_wfloor(&list, e, &wallf, &botf);
		e->hc = calc_wceil(&list, e, &wallc, &botc);
		e->line[num].iter++;
		list = list->next;
	}
	display_test(e, blist, num);
}
