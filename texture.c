/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e->file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:34:31 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/17 18:02:24 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_texture_parser1(t_env *e)
{
	e->file[1] = "texture/ceil4.xpm";
	e->file[2] = "texture/wall1h.xpm";
	e->file[3] = "texture/wall1v.xpm";
	e->file[4] = "texture/ceil1.xpm";
	e->file[5] = "texture/floor1.xpm";
	e->file[6] = "texture/wall3h.xpm";
	e->file[7] = "texture/wall3v.xpm";
	e->file[8] = "texture/ceil3.xpm";
	e->file[9] = "texture/floor3.xpm";
	e->file[10] = "texture/wall4h.xpm";
	e->file[11] = "texture/wall4v.xpm";
	e->file[12] = "texture/wall4h.xpm";
	e->file[13] = "texture/floor4.xpm";
	e->file[14] = "texture/wall4h.xpm";
	e->file[15] = "texture/wall4v.xpm";
	e->file[16] = "texture/wall4h.xpm";
	e->file[17] = "texture/floor5.xpm";
	e->file[18] = "texture/wall2h.xpm";
	e->file[19] = "texture/wall2v.xpm";
	e->file[20] = "texture/ceil2.xpm";
	e->file[21] = "texture/floor2.xpm";
	e->file[22] = "texture/wall3h.xpm";
	e->file[23] = "texture/wall3v.xpm";
	e->file[24] = "texture/ceil3.xpm";
}

void	init_texture_parser2(t_env *e)
{
	e->file[25] = "texture/floor6.xpm";
	e->file[26] = "texture/wall2h.xpm";
	e->file[27] = "texture/wall2v.xpm";
	e->file[28] = "texture/ceil2.xpm";
	e->file[29] = "texture/pistol1.xpm";
	e->file[30] = "texture/pistol2.xpm";
	e->file[31] = "texture/pistol3.xpm";
	e->file[32] = "texture/pistol4.xpm";
	e->file[33] = "texture/pistol5.xpm";
	e->file[34] = "texture/imp1.xpm";
	e->file[35] = "texture/imp2.xpm";
	e->file[36] = "texture/imp3.xpm";
	e->file[37] = "texture/imp4.xpm";
	e->file[38] = "texture/imp5.xpm";
	e->file[39] = "texture/imp6.xpm";
	e->file[40] = "texture/imp7.xpm";
	e->file[41] = "texture/imp8.xpm";
	e->file[42] = "texture/imp9.xpm";
	e->file[43] = "texture/imp10.xpm";
	e->file[44] = "texture/sold1.xpm";
	e->file[45] = "texture/sold2.xpm";
	e->file[46] = "texture/sold3.xpm";
	e->file[47] = "texture/sold4.xpm";
	e->file[48] = "texture/sold5.xpm";
}

void	init_texture_parser3(t_env *e)
{
	e->file[49] = "texture/sold6.xpm";
	e->file[50] = "texture/sold7.xpm";
	e->file[51] = "texture/sold8.xpm";
	e->file[52] = "texture/sold9.xpm";
	e->file[53] = "texture/sold10.xpm";
	e->file[54] = "texture/blood1.xpm";
	e->file[55] = "texture/four1.xpm";
	e->file[56] = "texture/lavabo1.xpm";
	e->file[57] = "texture/light1.xpm";
	e->file[58] = "texture/skeleton1.xpm";
	e->file[59] = "texture/skeleton2.xpm";
	e->file[60] = "texture/table1.xpm";
	e->file[61] = "texture/table2.xpm";
	e->file[62] = "texture/ustens1.xpm";
}

void	init_texture(t_env *e)
{
	int		i;

	e->tex = malloc(sizeof(t_img) * 63);
	e->file = malloc(sizeof(char *) * 63);
	init_texture_parser1(e);
	init_texture_parser2(e);
	init_texture_parser3(e);
	i = 0;
	while (++i < 63)
	{
		e->tex[i].img_ptr = mlx_xpm_file_to_image(e->mlx, e->file[i], \
								&e->tex[i].width, &e->tex[i].height);
		if (e->tex[i].img_ptr == NULL)
			err_texture();
		e->tex[i].img = (unsigned char *)mlx_get_data_addr(e->tex[i].img_ptr, \
								&e->tex[i].bpp, &e->tex[i].sl, \
								&e->tex[i].endian);
	}
}
