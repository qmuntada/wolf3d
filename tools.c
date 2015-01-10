
# include "wolf.h"

int		jump(t_env *e)
{
	if (e->p.jump2 < 15 && e->p.eyes <= e->map.ceiling[(int)e->p.y / BLOC][(int)e->p.x / BLOC])
		e->p.foot += GRAVITY + (8 - (e->p.jump2 += 1));
	if (e->p.foot == e->map.floor[(int)(e->p.y / BLOC)][(int)(e->p.x / BLOC)])
	{
		e->p.jump2 = 0;
		return (0);
	}
	return (1);
}
