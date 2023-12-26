/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:26:54 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/26 13:35:15 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

void	read_each_objects_hub(char *line, t_scene *scene, int *store_shape_num,
		t_read_cnt *read_cnt)
{
	char	**info;

	info = ft_split(line, ' ');
	if (!info)
		error_exit(ERROR_MALLOC);
	if (!ft_strncmp(info[0], "A", 2))
		read_ambient_light_info(scene, info, read_cnt->line_num, read_cnt);
	else if (!ft_strncmp(info[0], "C", 2))
		read_camera_info(scene, info, read_cnt->line_num, read_cnt);
	else if (!ft_strncmp(info[0], "L", 2))
		read_light_info(scene, info, read_cnt->line_num, read_cnt);
	else if (!ft_strncmp(info[0], "sp", 3))
		read_sphere_info(scene, info, read_cnt->line_num, store_shape_num);
	else if (!ft_strncmp(info[0], "pl", 3))
		read_plane_info(scene, info, read_cnt->line_num, store_shape_num);
	else if (!ft_strncmp(info[0], "cy", 3))
		read_cylinder_info(scene, info, read_cnt->line_num, store_shape_num);
	else
	{
		ft_printf_stderr("Error :.rt : line %i: invalid identifier\n",
			read_cnt->line_num);
		exit(1);
	}
	ft_split_array_all_free(info);
}

void	read_objects(char *line, t_scene *scene, int fd, t_read_cnt *read_cnt)
{
	int	store_shape_num;

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
		read_each_objects_hub(line, scene, &store_shape_num, read_cnt);
		free(line);
		if (read_cnt->line_num < INT_MAX)
			line = get_next_line(fd);
		else
			break ;
		read_cnt->line_num++;
	}
	if (read_cnt->line_num == 1)
		error_exit(ERROR_EMPTY_FILE);
}

void	read_info(t_scene *scene, char *filename, t_read_cnt *read_cnt)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(ERROR_OPEN);
	line = get_next_line(fd);
	if (!line)
		error_exit(ERROR_EMPTY_FILE);
	read_objects(line, scene, fd, read_cnt);
	close(fd);
}
