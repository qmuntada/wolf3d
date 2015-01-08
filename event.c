
#include "wolf.h"

void	movehor(t_env *e)
{
	float	x;
	float	y;
	float	dist;

	if (e->p.forward == 1)
	{
		x = e->p.x + MSPEED * cos(e->p.angle / 180 * M_PI);
		dist = ((sqrt(pow((x - e->slist.s[e->slist.n - 1].x), 2.0) + pow((e->p.y - e->slist.s[e->slist.n - 1].y), 2.0)))) / ((float)BLOC / 64);
		if (e->map.floor[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
			e->p.x += MSPEED * cos(e->p.angle / 180 * M_PI);
		y = e->p.y - MSPEED * sin(e->p.angle / 180 * M_PI);
		dist = ((sqrt(pow((e->p.x - e->slist.s[e->slist.n - 1].x), 2.0) + pow((y - e->slist.s[e->slist.n - 1].y), 2.0)))) / ((float)BLOC / 64);
		if (e->map.floor[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
			e->p.y -= MSPEED * sin(e->p.angle / 180 * M_PI);
	}
	else if (e->p.forward == -1)
	{
		x = e->p.x - MSPEED * cos(e->p.angle / 180 * M_PI);
		dist = ((sqrt(pow((x - e->slist.s[e->slist.n - 1].x), 2.0) + pow((e->p.y - e->slist.s[e->slist.n - 1].y), 2.0)))) / ((float)BLOC / 64);
		if (e->map.floor[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
			e->p.x -= MSPEED * cos(e->p.angle / 180 * M_PI);
		y = e->p.y + MSPEED * sin(e->p.angle / 180 * M_PI);
		dist = ((sqrt(pow((e->p.x - e->slist.s[e->slist.n - 1].x), 2.0) + pow((y - e->slist.s[e->slist.n - 1].y), 2.0)))) / ((float)BLOC / 64);
		if (e->map.floor[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
			e->p.y += MSPEED * sin(e->p.angle / 180 * M_PI);
	}
}

void	movever(t_env *e)
{
	float	x;
	float	y;
	float	dist;

	if (e->p.straff == -1)
	{
		x = e->p.x + MSPEED * sin(e->p.angle / 180 * M_PI);
		dist = ((sqrt(pow((x - e->slist.s[e->slist.n - 1].x), 2.0) + pow((e->p.y - e->slist.s[e->slist.n - 1].y), 2.0)))) / ((float)BLOC / 64);
		if (e->map.floor[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
			e->p.x += MSPEED * sin(e->p.angle / 180 * M_PI);
		y = e->p.y + MSPEED * cos(e->p.angle / 180 * M_PI);
		dist = ((sqrt(pow((e->p.x - e->slist.s[e->slist.n - 1].x), 2.0) + pow((y - e->slist.s[e->slist.n - 1].y), 2.0)))) / ((float)BLOC / 64);
		if (e->map.floor[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
			e->p.y += MSPEED * cos(e->p.angle / 180 * M_PI);
	}
	else if (e->p.straff == 1)
	{
		x = e->p.x - MSPEED * sin(e->p.angle / 180 * M_PI);
		dist = ((sqrt(pow((x - e->slist.s[e->slist.n - 1].x), 2.0) + pow((e->p.y - e->slist.s[e->slist.n - 1].y), 2.0)))) / ((float)BLOC / 64);
		if (e->map.floor[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(e->p.y / BLOC)][(int)(x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
			e->p.x -= MSPEED * sin(e->p.angle / 180 * M_PI);
		y = e->p.y - MSPEED * cos(e->p.angle / 180 * M_PI);
		dist = ((sqrt(pow((e->p.x - e->slist.s[e->slist.n - 1].x), 2.0) + pow((y - e->slist.s[e->slist.n - 1].y), 2.0)))) / ((float)BLOC / 64);
		if (e->map.floor[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			<= e->p.foot + 8 && \
			e->map.ceiling[(int)(y / BLOC)][(int)(e->p.x / BLOC)] \
			> e->p.eyes && dist > e->slist.s[e->slist.n - 1].size)
			e->p.y -= MSPEED * cos(e->p.angle / 180 * M_PI);
	}
}

void	movement(t_env *e)
{
	if (e->p.forward != 0)
		movehor(e);
	if (e->p.straff != 0)
		movever(e);
	if (e->p.jump == 1)
		e->p.jump = jump(e);
}

int		key_press(int keycode, t_env *e)
{
	//printf("key %d\n", keycode);
	if (keycode == ESC)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == W || keycode == S)
		e->p.forward = (keycode == S ? -1 : 1);
	else if (keycode == A || keycode == D)
		e->p.straff = (keycode == D ? -1 : 1);
	else if (keycode == SPACE && e->p.jump == 0)
		e->p.jump = 1;
	else if (keycode == C)
		e->p.crouch = 1;
	return (0);
}

int		key_release(int keycode, t_env *e)
{
	//printf("release %d\n", keycode);
	if (keycode == W || keycode == S)
		e->p.forward = 0;
	else if (keycode == A || keycode == D)
		e->p.straff = 0;
	else if (keycode == C)
		e->p.crouch = 0;
	return (0);
}
