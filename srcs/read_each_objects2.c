#include "../incs/minirt.h"

void read_sphere_info(t_scene *scene, char **info, size_t line_num)
{
    t_sphere *sph;
    sph = &scene->shapes[line_num-1].u_data.sphere;
    check_info_count(info, 4, line_num);
    store_coordinate_values(&sph->center, info[1], line_num);
    sph->radius = create_double_value(info[2], line_num) / 2;
    store_rgb_values(&scene->shapes[line_num-1].diffuse_ref, info[3], line_num);
}

void read_plane_info(t_scene *scene, char **info, size_t line_num)
{
    t_plane *pln;
    pln = &scene->shapes[line_num-1].u_data.plane;
    check_info_count(info, 4, line_num);
    store_coordinate_values(&pln->position, info[1], line_num);
    store_normalized_values(&pln->normal, info[2], line_num);
    store_rgb_values(&scene->shapes[line_num-1].diffuse_ref, info[3], line_num);
}
void read_cylinder_info(t_scene *scene, char **info, size_t line_num)
{
    t_cylinder *cylin;
    cylin = &scene->shapes[line_num-1].u_data.cylinder;
    check_info_count(info, 6, line_num);
    store_coordinate_values(&cylin->position, info[1], line_num);
    store_normalized_values(&cylin->normal, info[2], line_num);
    cylin->radius = create_double_value(info[3], line_num) / 2;
    cylin->height = create_double_value(info[4], line_num);
    store_rgb_values(&scene->shapes[line_num-1].diffuse_ref, info[5], line_num);
}