#include "../incs/minirt.h"

void	ft_init_scene(char *file, t_scene *scene)
{
	scene->num_shapes = count_num_shapes(file);
	scene->shapes = malloc(sizeof(t_shape) * scene->num_shapes + 1);
	if(!scene->shapes)
		error_exit(ERROR_MALLOC);
	read_info(scene, file);
}
