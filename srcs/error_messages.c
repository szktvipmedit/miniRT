#include "../incs/minirt.h"

void error_exit(char *error_message)
{
	write(2, error_message, ft_strlen(error_message));
	exit(1);
}
