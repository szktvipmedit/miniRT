#include "../incs/minirt.h"

size_t count_info_in_line(char **info)
{
    size_t len;
    while(info[len])
        len++;
    return len;
}

void check_info_count(char **info, int need_info_count, size_t line_num)
{
    if(count_info_in_line(info) != need_info_count)
    {
        ft_printf_stderr("Error :.rt : line %zu: Check how much information this object requires", line_num);
        exit(1);
    }
}

//utils
double check_range_value(double val, double range_min, double range_max, size_t line_num)
{
    if(!(range_min <= val && val <= range_max))
    {
        ft_printf_stderr("Error :.rt : line %zu: Check the range of specified values", line_num);
        exit(1);
    }
    return val;
}

double create_double_value(char *str, size_t line_num)
{
    double val;
    if(ft_syntax_check_double_value(str))
    {
        ft_printf_stderr("Error :.rt : line %zu: %s is invalid value. ", line_num, str);
        exit(1);
    }
    val = ft_atod(str);
    return val;
}

void store_rgb_values(char *info, size_t line_num)
{
    size_t i;
    i = 0;
    char **rgb;
    rgb = ft_split(info, ',');
    if(!rgb)
        error_exit(ERROR_MALLOC);
    check_info_count(rgb, 3, line_num);
    while(rgb[i])
    {
         = check_range_value(create_double_value(rgb[i], line_num), 0.0, 255.0, line_num);
        //STORE: color
    }
    ft_split_array_all_free(rgb);
    
}

void store_coordinate_values(char *info, size_t line_num)
{
    size_t i;
    i = 0;
    char **xyz;
    xyz = ft_split(info, ',');
    if(!xyz)
        error_exit(ERROR_MALLOC);
    check_info_count(xyz, 3, line_num);
    while(xyz[i])
    {
        //STORE: coordinate
        = create_double_value(xyz[i], line_num);
    }
    ft_split_array_all_free(xyz);
}

void store_normalized_values(char *info, size_t line_num)
{
    size_t i;
    i = 0;
    char **xyz;
    xyz = ft_split(info, ',');
    if(!xyz)
        error_exit(ERROR_MALLOC);
    check_info_count(xyz, 3, line_num);
    while(xyz[i])
    {
        //STORE: 3dnormalize
         = check_range_value(create_double_value(xyz[i], line_num), -1.0, 1.0, line_num);
    }
    ft_split_array_all_free(xyz);
}

void	red_ambient_light_info(t_rt *rt_info, char **info, size_t line_num)
{
    check_info_count(info, 3, line_num);
    //ratio
    //STORE: ratio
     = check_range_value(create_double_value(info[1], line_num), 0.0, 1.0, line_num);

    //R,G,B
    store_rgb_values(info[2], line_num);
}

void    read_camera_info(t_rt *rt_info, char **info, size_t line_num)
{    
    check_info_count(info, 4, line_num);
    store_coordinate_values(info[1], line_num);
    store_normalized_values(info[2], line_num);
     = check_range_value(create_double_value(info[3], line_num), 0.0, 180.0, line_num);
}

void read_light_info(t_rt *rt_info, char **info, size_t line_num)
{
    check_info_count(info, 4, line_num);
    store_coordinate_values(info[1], line_num);
     = check_range_value(create_double_value(info[2], line_num), 0.0, 1.0, line_num); 
    store_rgb_values(info[3], line_num);
}

void read_sphere_info(t_rt *rt_info, char **info, size_t line_num)
{
    check_info_count(info, 4, line_num);
    store_coordinate_values(info[1], line_num);
     = create_double_value(info[2], line_num);
     store_rgb_values(info[3], line_num);
}

void read_plane_info(t_rt *rt_info, char **info, size_t line_num)
{
    check_info_count(info, 4, line_num);
    store_coordinate_values(info[1], line_num);
    store_normalized_values(info[2], line_num);
    store_rgb_values(info[3], line_num);
}
void read_cylinder_info(t_rt *rt_info, char **info, size_t line_num)
{
    check_info_count(info, 6, line_num);
    store_coordinate_values(info[1], line_num);
    store_normalized_values(info[2], line_num);
     = create_double_value(info[3], line_num);
     = create_double_value(info[4], line_num);
    store_rgb_values(info[5], line_num);
}

int	ft_isverify_file_extension(char *filename, char *extension)
{
	size_t	i;
	size_t	dot_i;
	size_t	len;

	if (!filename || !extension || ft_strlen(filename) == 1)
    	error_exit("Error: ft_isverify_file_extension()\n");
	i = 0;
	len = ft_strlen(filename);
	dot_i = len - 1;
	while (dot_i >= 0)
	{
		if (filename[dot_i] == '.')
			break ;
		dot_i--;
	}
	while (i < ft_strlen(extension))
	{
		if (dot_i == 0 || filename[dot_i++] != extension[i++])
			return (0);
	}
	return (1);
}

void	read_info(t_rt *rt_info, char *filename)
{
	int fd;
	size_t line_num;
	char *line;
    if(!ft_isverify_file_extension(filename, ".rt"))
        error_exit(ERROR_USAGE);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(ERROR_OPEN);
	line_num = 1;
    line = get_next_line(fd);
    if(!line)
        error_exit(ERROR_EMPTY_FILE);
	while (line)
	{
        // if(is_all_space(line))
        //     continue;
        char **info;
        info = ft_split(line, ' ');
        if(!info)
            error_exit(ERROR_MALLOC);
		if (!ft_strncmp(info[0], "A ", 2))
			read_ambient_light_info(rt_info, info, line_num);
		else if (!ft_strncmp(info[0], "C ", 2))
			read_camera_info(rt_info, info, line_num);
		else if (!ft_strncmp(info[0], "L ", 2))
			read_light_info(rt_info, info, line_num);
		else if (!ft_strncmp(info[0], "sp ", 3))
			read_sphere_info(rt_info, info, line_num);
		else if (!ft_strncmp(info[0], "pl ", 3))
			read_plane_info(rt_info, info, line_num);
		else if (!ft_strncmp(info[0], "cy ", 3))
			read_cylinder_info(rt_info, info, line_num);
		else
			ft_printf_stderr("Error :.rt : line %zu: invalid identifier\n", filename,
				line_num);
        free(line);
        ft_split_array_all_free(info);
        line = get_next_line(fd);
		line_num++;
	}
}