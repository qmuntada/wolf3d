
#include "wolf.h"

char	**init_texture_parser(t_env *e, char **texture)
{
	e->tex = malloc(sizeof(t_img) * 63);
	texture = malloc(sizeof(char *) * 63);
	texture[1] = "texture/ceil4.xpm";
	texture[2] = "texture/wall1h.xpm";
	texture[3] = "texture/wall1v.xpm";
	texture[4] = "texture/ceil1.xpm";
	texture[5] = "texture/floor1.xpm";
	texture[6] = "texture/wall3h.xpm";
	texture[7] = "texture/wall3v.xpm";
	texture[8] = "texture/ceil3.xpm";
	texture[9] = "texture/floor3.xpm";
	texture[10] = "texture/wall4h.xpm";
	texture[11] = "texture/wall4v.xpm";
	texture[12] = "texture/wall4h.xpm";
	texture[13] = "texture/floor4.xpm";
	texture[14] = "texture/wall4h.xpm";
	texture[15] = "texture/wall4v.xpm";
	texture[16] = "texture/wall4h.xpm";
	texture[17] = "texture/floor5.xpm";
	texture[18] = "texture/wall2h.xpm";
	texture[19] = "texture/wall2v.xpm";
	texture[20] = "texture/ceil2.xpm";
	texture[21] = "texture/floor2.xpm";
	texture[22] = "texture/wall3h.xpm";
	texture[23] = "texture/wall3v.xpm";
	texture[24] = "texture/ceil3.xpm";
	texture[25] = "texture/floor6.xpm";
	texture[26] = "texture/wall2h.xpm";
	texture[27] = "texture/wall2v.xpm";
	texture[28] = "texture/ceil2.xpm";
	texture[29] = "texture/pistol1.xpm";
	texture[30] = "texture/pistol2.xpm";
	texture[31] = "texture/pistol3.xpm";
	texture[32] = "texture/pistol4.xpm";
	texture[33] = "texture/pistol5.xpm";
	texture[34] = "texture/imp1.xpm";
	texture[35] = "texture/imp2.xpm";
	texture[36] = "texture/imp3.xpm";
	texture[37] = "texture/imp4.xpm";
	texture[38] = "texture/imp5.xpm";
	texture[39] = "texture/imp6.xpm";
	texture[40] = "texture/imp7.xpm";
	texture[41] = "texture/imp8.xpm";
	texture[42] = "texture/imp9.xpm";
	texture[43] = "texture/imp10.xpm";
	texture[44] = "texture/sold1.xpm";
	texture[45] = "texture/sold2.xpm";
	texture[46] = "texture/sold3.xpm";
	texture[47] = "texture/sold4.xpm";
	texture[48] = "texture/sold5.xpm";
	texture[49] = "texture/sold6.xpm";
	texture[50] = "texture/sold7.xpm";
	texture[51] = "texture/sold8.xpm";
	texture[52] = "texture/sold9.xpm";
	texture[53] = "texture/sold10.xpm";
	texture[54] = "texture/blood1.xpm";
	texture[55] = "texture/four1.xpm";
	texture[56] = "texture/lavabo1.xpm";
	texture[57] = "texture/light1.xpm";
	texture[58] = "texture/skeleton1.xpm";
	texture[59] = "texture/skeleton2.xpm";
	texture[60] = "texture/table1.xpm";
	texture[61] = "texture/table2.xpm";
	texture[62] = "texture/ustens1.xpm";

	return (texture);
}

void	init_texture(t_env *e)
{
	char	**texture;
	int		i;

	texture = init_texture_parser(e, texture);
	i = 0;
	while (++i < 63)
	{
		e->tex[i].img_ptr = mlx_xpm_file_to_image(e->mlx, texture[i], \
								&e->tex[i].width, &e->tex[i].height);
		if (e->tex[i].img_ptr == NULL)
			err_texture();
		e->tex[i].img = mlx_get_data_addr(e->tex[i].img_ptr, \
								&e->tex[i].bpp, &e->tex[i].sl, \
								&e->tex[i].endian);
	}
}
