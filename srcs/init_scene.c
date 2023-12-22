/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:17:59 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/22 14:26:12 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

static int	is_path(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static void	get_filename_from_path(char *path)
{
	size_t	len;
	size_t	sla_i;

	if (!is_path(path))
		return ;
	len = ft_strlen(path);
	sla_i = len - 1;
	while (sla_i >= 0)
	{
		if (path[sla_i] == '/')
			break ;
		sla_i--;
	}
	path = path + sla_i + 1;
}

static int	ft_verify_file_extension(char *filename, char *extension)
{
	size_t	i;
	size_t	dot_i;
	size_t	len;

	get_filename_from_path(filename);
	if (!filename || !extension || ft_strlen(filename) == 1)
		return (0);
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

void	ft_init_scene(char *file, t_scene *scene)
{
	if (!ft_verify_file_extension(file, ".rt"))
		error_exit(ERROR_USAGE);
	scene->num_shapes = count_num_shapes(file);
	scene->shapes = malloc(sizeof(t_shape) * scene->num_shapes + 1);
	if (!scene->shapes)
		error_exit(ERROR_MALLOC);
	read_info(scene, file);
}
