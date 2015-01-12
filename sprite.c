
#include "wolf.h"

void	get_sprite_data(t_env *e, char **data, int n)
{
	e->slist.s[n].y = (float)ft_atoi(data[0]) * BLOC + 32;
	e->slist.s[n].x = (float)ft_atoi(data[1]) * BLOC + 32;
	e->slist.s[n].z = (float)ft_atoi(data[2]);
	e->slist.s[n].life = 100.0;
	e->slist.s[n].attitude = ft_atoi(data[3]);
	e->slist.s[n].texture = ft_atoi(data[4]);
	e->slist.s[n].size = ft_atoi(data[5]);
	e->slist.s[n].state = 0;
	e->slist.s[n].attack = 0;
}

void	get_sprite_list(t_env *e, char **data, int *i)
{
	char	**data_line;
	int		x;

	x = -1;
	*i = *i + 1;
	if (!data[*i])
		err_map();
	data_line = ft_strsplit(data[*i], ' ');
	e->slist.n = ft_atoi(data_line[0]);
	e->slist.s = malloc(sizeof(t_sprite) * e->slist.n);
	while (++x < e->slist.n)
	{
		*i = *i + 1;
		data_line = ft_strsplit(data[*i], ' ');
		get_sprite_data(e, data_line, x);
	}
}

void	sprite_sort(t_env *e)
{
	int			x;
	int			y;
	int			done;
	t_sprite	tmp;

	x = -1;
	done = 1;
	while (++x < e->slist.n && done)
	{
		y = 0;
		done = 0;
		while (++y < (e->slist.n - x))
		{
			if (e->slist.s[y - 1].dist < e->slist.s[y].dist)
			{
				tmp = e->slist.s[y - 1];
				e->slist.s[y - 1] = e->slist.s[y];
				e->slist.s[y] = tmp;
				done = 1;
			}
		}
	}
}

void	sprite_calc(t_env *e)
{
	int		n;
	int		y;
	int		x;
	float	uvx;
	float	uvy;
	float	pas;
	int		pos;
	int		color;

	n = -1;
	while (++n < e->slist.n)
	{
		pas = get_sprite_coord(e, n);
		if ((e->slist.s[n].botx >= 0 && e->slist.s[n].botx < e->img.width) \
			|| (e->slist.s[n].topx >= 0 && e->slist.s[n].topx < e->img.width) \
			|| (e->slist.s[n].botx < 0 && e->slist.s[n].topx > e->img.width))
		{
			display_sprite(e, n, pas);
		}
	}
}

void	sprite_display(t_env *e)
{
	int		x;

	x = -1;
	while (++x < e->slist.n)
	{
		e->slist.s[x].dist = \
			((sqrt(pow((e->p.x - e->slist.s[x].x), 2.0) + \
			pow((e->p.y - e->slist.s[x].y), 2.0))) / \
			((float)BLOC / 64)) / SCALE;
		if (e->slist.s[x].dist < 16)
			e->slist.s[x].dist = 16;
	}
	sprite_sort(e);
	sprite_calc(e);
}
