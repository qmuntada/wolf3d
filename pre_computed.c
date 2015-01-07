
#include "wolf.h"

void	pre_comput(t_env *e, float ray)
{
	e->precomp.angle = ray;
	e->precomp.angle += (e->precomp.angle < 0 ? 360 : 0);
	e->precomp.angle += (e->precomp.angle > 360 ? -360 : 0);
	e->precomp.d_angle = ray / 180.0 * M_PI;
	e->precomp.td_angle = tan(e->precomp.d_angle);
	e->precomp.mwidth = e->map.width * BLOC;
	e->precomp.mheight = e->map.height * BLOC;
	e->precomp.playx = e->p.x;
	e->precomp.playy = e->p.y;
	e->precomp.playangle = e->p.angle;
	e->precomp.fisheye = (cos((e->precomp.playangle - e->precomp.angle) / 180 * M_PI)) / SCALE;
}
