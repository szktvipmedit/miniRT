#include "../incs/minirt.h"

void store_rgb_values(t_color3 *col, char *info, size_t line_num)
{
    char **rgb;
    rgb = ft_split(info, ',');
    if(!rgb)
        error_exit(ERROR_MALLOC);
    check_info_count(rgb, 3, line_num);
    col->r = check_range_value(create_double_value(rgb[0], line_num), 0.0, 255.0, line_num);
    col->g = check_range_value(create_double_value(rgb[1], line_num), 0.0, 255.0, line_num);
    col->b = check_range_value(create_double_value(rgb[2], line_num), 0.0, 255.0, line_num);
    ft_split_array_all_free(rgb);
}

void store_coordinate_values(t_vec3 *vec, char *info, size_t line_num)
{
    char **xyz;
    xyz = ft_split(info, ',');
    if(!xyz)
        error_exit(ERROR_MALLOC);
    check_info_count(xyz, 3, line_num);
    vec->x  = create_double_value(xyz[0], line_num);
    vec->y  = create_double_value(xyz[1], line_num);
    vec->z  = create_double_value(xyz[2], line_num);
    ft_split_array_all_free(xyz);
}

void store_normalized_values(t_vec3 *vec, char *info, size_t line_num)
{
    char **xyz;
    xyz = ft_split(info, ',');
    if(!xyz)
        error_exit(ERROR_MALLOC);
    check_info_count(xyz, 3, line_num);
    vec->x  = create_double_value(xyz[0], line_num);
    vec->y  = create_double_value(xyz[1], line_num);
    vec->z  = create_double_value(xyz[2], line_num);
    ft_split_array_all_free(xyz);
}

