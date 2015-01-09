
#include "wolf.h"

char	**init_texture_parser(t_env *e, char **texture)
{
	e->texture = malloc(sizeof(t_img) * 30);
	texture = malloc(sizeof(char *) * 30);
	texture[1] = "texture/ceil1.xpm";
	texture[2] = "texture/wall1h.xpm";
	texture[3] = "texture/wall1v.xpm";
	texture[4] = "texture/ceil1.xpm";
	texture[5] = "texture/floor1.xpm";
	texture[6] = "texture/wall3h.xpm";
	texture[7] = "texture/wall3v.xpm";
	texture[8] = "texture/ceil1.xpm";
	texture[9] = "texture/floor3.xpm";
	texture[10] = "texture/wall4h.xpm";
	texture[11] = "texture/wall4v.xpm";
	texture[12] = "texture/ceil1.xpm";
	texture[13] = "texture/floor4.xpm";
	texture[14] = "texture/wall4h.xpm";
	texture[15] = "texture/wall4v.xpm";
	texture[16] = "texture/ceil1.xpm";
	texture[17] = "texture/floor5.xpm";
	texture[18] = "texture/wall2h.xpm";
	texture[19] = "texture/wall2v.xpm";
	texture[20] = "texture/ceil1.xpm";
	texture[21] = "texture/floor2.xpm";
	texture[22] = "texture/wall3h.xpm";
	texture[23] = "texture/wall3v.xpm";
	texture[24] = "texture/ceil1.xpm";
	texture[25] = "texture/floor6.xpm";
	texture[26] = "texture/wall2h.xpm";
	texture[27] = "texture/wall2v.xpm";
	texture[28] = "texture/ceil1.xpm";
	texture[29] = "texture/sprite1.xpm";
	return (texture);
}

void	init_texture(t_env *e)
{
	char	**texture;
	int		i;

	texture = init_texture_parser(e, texture);
	i = 0;
	while (++i < 30)
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
