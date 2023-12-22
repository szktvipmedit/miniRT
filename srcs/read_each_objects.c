#include "../incs/minirt.h"

void	read_ambient_light_info(t_scene *scene, char **info, int line_num)
{
	check_info_count(info, 3, line_num);
	scene->ambient.ambient_ref = check_range_value(create_double_value(info[1],
				line_num), 0.0, 1.0, line_num);
	store_rgb_values(&scene->ambient.amb_illuminance, info[2], line_num);
	normalize_color(&scene->ambient.amb_illuminance);
}

void	read_camera_info(t_scene *scene, char **info, int line_num)
{
	check_info_count(info, 4, line_num);
	store_coordinate_values(&scene->camera.camera_position, info[1], line_num);
	store_normalized_values(&scene->camera.forward_dir, info[2], line_num);
	scene->camera.degree = check_range_value(create_double_value(info[3],
				line_num), 0.0, 180.0, line_num);
}

void	read_light_info(t_scene *scene, char **info, int line_num)
{
	check_info_count(info, 4, line_num);
	store_coordinate_values(&scene->light.vector, info[1], line_num);
	scene->light.specular_ref = check_range_value(create_double_value(info[2],
				line_num), 0.0, 1.0, line_num);
	store_rgb_values(&scene->light.illuminance, info[3], line_num);
	normalize_color(&scene->light.illuminance);
}
