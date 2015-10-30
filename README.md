# WOLF3D

42 - Realise a l'aide de la minilibx.

MAJ : Fonctionne avec la nouvelle minilibx !
Par contre, la libraire permetant de bloquer la souris au centre de l'ecran (X11) a ete viree des dumps ;_;

UPDATE : The game work and you don't need to install the mlx anymore.
It also work without the X11 library now but the mouse isn't locked at the center of the screen anymore.

If you think mouse movement is too fast, you can adjust it in wolf.h : just modify the "# define RSPEED (ADJUSTED VALUE)"

Modifying the other defines is not advised so do it at your own risk !
Harmless modification you can do :
	WIDTH / HEIGHT (change the resolution)
	MSPEED (change the speed of the player)
	SCALE (change the scale of the world, harmless but not advised)

You can also customize the map or even make one yourself !
To play on it, you have to rename it "map" and place it in the root "wolf3d" folder.

Have fun !
