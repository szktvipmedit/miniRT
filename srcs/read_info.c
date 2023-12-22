#include "../incs/minirt.h"

void	read_each_objects_hub(char *line, t_scene *scene, int line_num,
		int *store_shape_num)
{
	char	**info;

	info = ft_split(line, ' ');
	if (!info)
		error_exit(ERROR_MALLOC);
	if (!ft_strncmp(info[0], "A", 2))
		read_ambient_light_info(scene, info, line_num);
	else if (!ft_strncmp(info[0], "C", 2))
		read_camera_info(scene, info, line_num);
	else if (!ft_strncmp(info[0], "L", 2))
		read_light_info(scene, info, line_num);
	else if (!ft_strncmp(info[0], "sp", 3))
		read_sphere_info(scene, info, line_num, store_shape_num);
	else if (!ft_strncmp(info[0], "pl", 3))
		read_plane_info(scene, info, line_num, store_shape_num);
	else if (!ft_strncmp(info[0], "cy", 3))
		read_cylinder_info(scene, info, line_num, store_shape_num);
	else
	{
		ft_printf_stderr("Error :.rt : line %i: invalid identifier\n",
			line_num);
		exit(1);
	}
	ft_split_array_all_free(info);
}

void	read_objects(char *line, t_scene *scene, int fd)
{
	int	line_num;
	int	store_shape_num;

	line_num = 1;
	store_shape_num = 0;
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (is_all_spaces(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		read_each_objects_hub(line, scene, line_num, &store_shape_num);
		free(line);
		if (line_num < INT_MAX)
			line = get_next_line(fd);
		else
			break ;
		line_num++;
	}
	if (line_num == 1)
		error_exit(ERROR_EMPTY_FILE);
}

void	read_info(t_scene *scene, char *filename)
{
	int		fd;
	char	*line;

	if (!ft_verify_file_extension(filename, ".rt"))
		error_exit(ERROR_USAGE);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(ERROR_OPEN);
	line = get_next_line(fd);
	if (!line)
		error_exit(ERROR_EMPTY_FILE);
	read_objects(line, scene, fd);
	close(fd);
}
