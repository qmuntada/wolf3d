
#include "wolf.h"

char	**init_texture_parser(t_env *e, char **texture)
{
	e->texture = malloc(sizeof(t_img) * 4);
	texture = malloc(sizeof(char *) * 4);
	texture[1] = "texture/wall1.xpm";
	texture[2] = "texture/floor1.xpm";
	texture[3] = "texture/barrel.xpm";
	return (texture);
}

void	init_texture(t_env *e)
{
	char	**texture;
	int		i;

	texture = init_texture_parser(e, texture);
	i = 0;
	while (++i < 4)
	{
		e->texture[i].img_ptr = mlx_xpm_file_to_image(e->mlx, texture[i], \
								&e->texture[i].width, &e->texture[i].height);
		if (e->texture[i].img_ptr == NULL)
			err_texture();
		e->texture[i].img = mlx_get_data_addr(e->texture[i].img_ptr, \
								&e->texture[i].bpp, &e->texture[i].sl, \
								&e->texture[i].endian);
	}
}
