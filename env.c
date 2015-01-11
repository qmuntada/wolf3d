
#include "wolf.h"

void		get_p(t_env *e, char **data, int *i)
{
	char		**p_data;

	*i = *i + 1;
	if (!data[*i])
		err_map();
	p_data = ft_strsplit(data[*i], ' ');
	e->p.y = (ft_atoi(p_data[0]) * BLOC) - (BLOC / 2) + BLOC;
	e->p.x = (ft_atoi(p_data[1]) * BLOC) - (BLOC / 2) + BLOC;
	e->p.foot = ft_atoi(p_data[2]);
	e->p.eyes = e->p.foot + 32;
	e->p.angle = ft_atoi(p_data[3]);
	e->p.forward = 0;
	e->p.straff = 0;
	e->p.jump = 0;
	e->p.crouch = 0;
	e->p.bobbing = 0;
	e->p.shoot = 0;
	e->p.wpstate = 0;
	e->p.life = 100.0;
}

static int			**get_map(t_env *e, char **data, int *i)
{
	int		x;
	int		y;
	char	**array;
	int		**map;

	if (!e->map.width || !e->map.height)
		err_map();
	x = -1;
	*i = *i + 1;
	map = malloc(sizeof(int *) * e->map.height);
	while (++x < e->map.height)
	{
		if (!data[*i + x])
			err_map();
		array = ft_strsplit(data[*i + x], ' ');
		map[x] = malloc(sizeof(int) * e->map.width);
		y = -1;
		while (++y < e->map.width)
		{
			if (!array[y])
				err_map();
			map[x][y] = ft_atoi(array[y]);
		}
	}
	*i = *i + e->map.height - 1;
	return (map);
}

static void			analize_map_data(t_env *e, char **data, int len)
{
	int		i;

	i = -1;
	while (data[++i] && i < len)
	{
		if (strstr(data[i], "MAP NAME :"))
			e->map.name = ft_strdup(data[i] + 11);
		else if (strstr(data[i], "MAP WIDTH :"))
			e->map.width = ft_atoi(ft_strdup(data[i] + 12));
		else if (strstr(data[i], "MAP HEIGHT :"))
			e->map.height = ft_atoi(ft_strdup(data[i] + 13));
		else if (strstr(data[i], "HEIGHT MAP : FLOOR"))
			e->map.floor = get_map(e, data, &i);
		else if (strstr(data[i], "HEIGHT MAP : CEILING"))
			e->map.ceiling = get_map(e, data, &i);
		else if (strstr(data[i], "TEXTURE MAP :"))
			e->map.texture = get_map(e, data, &i);
		else if (strstr(data[i], "PLAYER POSITION :"))
			get_p(e, data, &i);
		else if (strstr(data[i], "SPRITE LIST :"))
			get_sprite_list(e, data, &i);
	}
}

static void			set_map(t_env *e, int fd)
{
	char	*line;
	char	**map_data;
	t_list	*map_buf;
	int		i;
	int		lstlen;

	i = -1;
	map_buf = NULL;
	while (get_next_line(fd, &line) == 1)
		ft_lstpushback(&map_buf, line, ft_strlen(line));
	lstlen = ft_lstlen(map_buf);
	if (!map_buf)
		err_map();
	map_data = malloc(sizeof(char **) * ft_lstlen(map_buf));
	while (map_buf)
	{
		map_data[++i] = map_buf->content;
		map_buf = map_buf->next;
	}
	analize_map_data(e, map_data, lstlen);
}

void				init_env(t_env *e, int fd)
{
	set_map(e, fd);
	e->img.width = WIDTH;
	e->img.height = HEIGHT;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, e->img.width, e->img.height, e->map.name);
	e->img.angle_w = (float)FOV / e->img.width;
	e->img.img_ptr = mlx_new_image(e->mlx, e->img.width, e->img.height);
	e->img.img = mlx_get_data_addr(e->img.img_ptr, &e->img.bpp, \
										&e->img.sl, &e->img.endian);
	e->img.dist = (e->img.width / 2) / 0.57735026;
	e->img.center = e->img.height / 2;
	e->line = malloc(sizeof(t_line) * e->img.width);
}
