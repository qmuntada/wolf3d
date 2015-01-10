
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
	display_line(e, blist, num);
}
