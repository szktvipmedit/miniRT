#include "../incs/minirt.h"

void	error_malloc(void)
{
	write(2, ERROR_MALLOC, ft_strlen(ERROR_MALLOC));
	exit(1);
}