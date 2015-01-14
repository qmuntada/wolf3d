Projet WOLF3D pour l'ecole 42.

Realise a l'aide de la minilibx.

Compilation sur MAC (pour l'instant pas de Makefile) :
gcc *.c libft/libft.a -I/usr/X11/include -L/usr/X11/lib -lX11 -lXext -lmlx

Compilation sur LINUX :
gcc *.c libft/libft.a -L/usr/lib/X11 -lmlx -lXext -lX11 -lm

Change the define in wolf.h to switch X11 version (LINUX or MAC)

If you think mouse movement is too fast, you can adjust it in wolf.h : just modify the "# define RSPEED (ADJUSTED VALUE)"

Modifying the other defines is not advised so do it at your own risk !
Harmless modification you can do :
	WIDTH / HEIGHT (change the resolution)
	MSPEED (change the speed of the player)
	SCALE (change the scale of the world, harmless but not advised)

You can also customize the map or even make one yourself !

Have fun !
