
#include "wolf.h"

void	err_map(void)
{
	ft_putstr_fd("Wolf3d: Error: Included map have incorrect data !\n", 2);
	exit(EXIT_FAILURE);
}

void	err_texture(void)
{
	ft_putstr_fd("Wolf3d: Error: Error while loading texture\n", 2);
	exit(EXIT_FAILURE);
}
