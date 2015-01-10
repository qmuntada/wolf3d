
#include "wolf.h"

void		draw_wallf(t_env *e, t_vectlst *list, int num)
{
	float	pas;
	int		tex;

	pas = ((float)BLOC / ((list->wfloorbot + list->wfloorsv) - (list->wfloortop - list->wfloorev)));
	pas *= ((float)list->wallf / BLOC);
	e->x = 0 + (list->wfloorsv * pas);
	tex = e->map.texture[(int)floor(list->vector.y / BLOC)][(int)floor(list->vector.x / BLOC)] * 4 + 2;
	e->px = list->wfloorbot;
	while (e->px >= list->wfloortop)
	{
		e->x += (e->x > 64.0 ? -64.0 : 0);
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
	int		tex;

	pas = ((float)BLOC / ((list->wceiltop + list->wceilev) - (list->wceilbot - list->wceilsv)));
	pas *= ((512.0 - (float)list->wallc) / BLOC);
	e->x = 64 - (list->wceilsv * pas);
	tex = e->map.texture[(int)floor(list->vector.y / BLOC)][(int)floor(list->vector.x / BLOC)] * 4 + 2;
	e->px = list->wceilbot;
	while (e->px <= list->wceiltop)
	{
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

void		draw_floor(t_env *e, t_vectlst *list, int num)
{
	float	pasx;
	float	pasy;
	float	pas;
	int		tex;

	pas = (list->floorbot + list->floorsv) - (list->floortop - list->floorev);
	pasx = (-(e->x - list->vector.uvx)) / pas;
	pasy = (-(e->y - list->vector.uvy)) / pas;
	e->x += (list->floorsv * pasx);
	e->y += (list->floorsv * pasy);
	tex = e->map.texture[(int)floor(e->ay / BLOC)][(int)floor(e->ax / BLOC)] * 4 + 1;
	e->px = list->floorbot;
	while (e->px >= list->floortop)
	{
		if (e->px < e->img.height && e->px >= 0 && e->x >= 0 && e->x <= 64 && e->y >= 0 && e->y <= 64)
			render_pointfc(e, num, list->vector.dist, tex);
		e->px = e->px - 1;
		e->x += pasx;
		e->y += pasy;
	}
}

void		draw_ceil(t_env *e, t_vectlst *list, int num)
{
	float	pasx;
	float	pasy;
	float	pas;
	int		tex;

	pas = (list->ceiltop + list->ceilev) - (list->ceilbot - list->ceilsv);
	pasx = (-(e->x - list->vector.uvx)) / pas;
	pasy = (-(e->y - list->vector.uvy)) / pas;
	e->x += (list->ceilsv * pasx);
	e->y += (list->ceilsv * pasy);
	tex = e->map.texture[(int)floor(e->ay / BLOC)][(int)floor(e->ax / BLOC)] * 4 + 4;
	e->px = list->ceilbot;
	while (e->px <= list->ceiltop)
	{
		e->x += (e->x > 64.0 ? -64.0 : 0);
		e->x += (e->x < 0 ? 64 : 0);
		e->y += (e->y > 64.0 ? -64.0 : 0);
		e->y += (e->y < 0 ? 64 : 0);
		if (e->px < e->img.height && e->px >= 0 && e->x >= 0 && e->x <= 64 && e->y >= 0 && e->y <= 64)
			render_pointfc(e, num, list->vector.dist, tex);
		e->px = e->px + 1;
		e->x += pasx;
		e->y += pasy;
	}
}


void		display_line(t_env *e, t_vectlst *list, int num)
{
	int		n;

	e->ax = e->p.x;
	e->ay = e->p.y;
	e->vx = 0;
	e->vy = 0;
	n = e->line[num].iter;
	while (list && n-- > 0)
	{
		e->dist = list->vector.dist;
		e->x = e->vx;
		e->y = e->vy;
		draw_floor(e, list, num);
		e->x = e->vx;
		e->y = e->vy;
		draw_ceil(e, list, num);
		e->vx = (int)list->vector.x % 64;
		e->vy = (int)list->vector.y % 64;
		draw_wallf(e, list, num);
		draw_wallc(e, list, num);
		e->ax = list->vector.x;
		e->ay = list->vector.y;
		list = list->next;
	}
}
