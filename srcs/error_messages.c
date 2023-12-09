#include "../incs/minirt.h"

void	error_malloc(void)
{
	write(2, ERROR_MALLOC, ft_strlen(ERROR_MALLOC));
	exit(1);
}

void    error_arg_cnt(void)
{
    write(2, ERROR_ARG_CNT, ft_strlen(ERROR_ARG_CNT));
    exit(1);
}