/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 18:53:05 by qmuntada          #+#    #+#             */
/*   Updated: 2015/01/07 19:18:51 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define LINUX
//# define MAC

# ifdef MAC
#  include </usr/X11/include/X11/X.h>
#  include </usr/X11/include/X11/Xlib.h>
# endif

# ifdef LINUX
#  include <X11/X.h>
#  include <X11/Xlib.h>
# endif

# include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <time.h>

# define WIDTH 1280 // 640 1280 2560
# define HEIGHT 720 // 360 720 1440
# define FOV 60
# define MSPEED 10
# define RSPEED 20 // MOUSE SPEED
# define BLOC 64
# define GRAVITY 15
# define SCALE 2 // Plus le chiffre est grand, plus le monde paraitra petit
# define SZ 24 // SPRITE_SIZE

# define ESC 65307
# define Q 113
# define W 119
# define E 101
# define A 97
# define S 115
# define D 100
# define SPACE 32
# define C 99
# define Z 122
# define X 120

typedef struct			s_vector
{
	float				x;
	float				y;
	int					uvx;
	int					uvy;
	float				dist;
}						t_vector;

typedef struct			s_vectlst
{
	t_vector			vector;
	char				side;
	int					floorbot;
	int					floorsv;
	int					floortop;
	int					floorev;
	int					ceilbot;
	int					ceilsv;
	int					ceiltop;
	int					ceilev;
	int					wfloorbot;
	int					wfloorsv;
	int					wfloortop;
	int					wfloorev;
	int					wceilbot;
	int					wceilsv;
	int					wceiltop;
	int					wceilev;
	int					wallc;
	int					wallf;
	int					hc;
	int					hf;
	struct s_vectlst	*next;
}						t_vectlst;

typedef struct			s_line
{
	t_vectlst			*list;
	float				angle;
	int					iter;
}						t_line;

typedef struct			s_player
{
	float				x;
	float				y;
	float				eyes;
	float				foot;
	float				angle;
	float				bobbing;
	int					forward;
	int					straff;
	int					jump;
	int					jump2;
	int					crouch;
}						t_player;

typedef struct			s_map
{
	char				*name;
	int					width;
	int					height;
	int					**floor;
	int					**ceiling;
	t_player			firstpos;
}						t_map;

typedef struct			s_img
{
	void				*win;
	void				*img_ptr;
	unsigned char		*img;
	int					bpp;
	int					sl;
	int					endian;
	int					width;
	int					height;
	float				angle_w;
	int					dist;
	int					center;
}						t_img;

typedef struct			s_sprite
{
	int					alive;
	int					mobile;
	int					attitude;
	int					onsight;
	float				x;
	float				y;
	float				z;
	float				dist;
	int					texture;
	float				rel_angle;
	int					botx;
	int					topx;
	int					boty;
	int					topy;
	float				uvx;
	float				uvy;
}						t_sprite;

typedef struct			s_sprite_list
{
	int					n;
	t_sprite			*s;
}						t_sprite_list;

typedef struct			s_precomp
{
	float				angle;
	float				d_angle;
	float				td_angle;
	int					mwidth;
	int					mheight;
	float				playx;
	float				playy;
	float				playangle;
	float				fisheye;
}						t_precomp;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	t_player			p;
	t_map				map;
	t_img				img;
	t_img				*texture;
	t_line				*line;
	t_precomp			precomp;
	t_sprite_list		slist;
	int					hc;
	int					hf;
}						t_env;

typedef struct	s_event_list
{
	int			mask;
	int			(*hook)();
	void		*param;
}				t_event_list;

typedef struct			s_win_list
{
	Window				window;
	GC					gc;
	struct s_win_list	*next;
	int					(*mouse_hook)();
	int					(*key_hook)();
	int					(*expose_hook)();
	void				*mouse_param;
	void				*key_param;
	void				*expose_param;
	t_event_list		hooks[LASTEvent];
}						t_win_list;

typedef struct	s_xvar
{
	Display		*display;
	Window		root;
	int			screen;
	int			depth;
	Visual		*visual;
	Colormap	cmap;
	int			private_cmap;
	t_win_list	*win_list;
	int			(*loop_hook)();
	void		*loop_param;
	int			use_xshm;
	int			pshm_format;
	int			do_flush;
	int			decrgb[6];
}				t_xvar;


void					err_map(void);
void					err_texture(void);
void					init_env(t_env *e, int fd);
void					init_texture(t_env *e);
int						key_press(int key, t_env *e);
int						key_release(int key, t_env *e);
void					fps(t_env *e);
void					calc_img(t_env *e);
void					init_vector_hori(t_precomp *prec, t_vector *h);
void					init_vector_vert(t_precomp *prec, t_vector *v);
void					vect_addsort(t_vectlst **blst, t_vector *content, \
							char side);
void					line_cleaner(t_env *e, t_vectlst *blist, int num);
void					vect_clear(t_vectlst **blst);
void					movement(t_env *e);
void					pre_comput(t_env *e, float ray_angle);
int						jump(t_env *e);
int						mouse(int x, int y, t_env *e);
void					cursor_move(void *mlx, int x, int y);
void					get_sprite_list(t_env *e, char **data, int *i);
void					sprite_display(t_env *e);
void					pixel_put(t_env *e, int x, int y, int color, int dist);
float					get_sprite_coord(t_env *e, int n);
void					display_sprite(t_env *e, int n, float pas);

#endif