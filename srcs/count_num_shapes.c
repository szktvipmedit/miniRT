/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_num_shapes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:25:52 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/22 15:07:31 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

int	is_all_spaces(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

static int	new_line(int line_num)
{
	if (line_num < INT_MAX)
	{
		return (0);
	}
	else
	{
		ft_printf_stderr(NOTICE_MAX_OBJECTS);
		return (1);
	}
}

static void	count_num_shapes_each_shape(char *line, int fd, int *line_num)
{
	char	**info;

	while (line)
	{
		if (is_all_spaces(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		info = ft_split(line, ' ');
		if (!info)
			error_exit(ERROR_MALLOC);
		if (!ft_strncmp(info[0], "sp", 3) || !ft_strncmp(info[0], "pl", 3)
			|| !ft_strncmp(info[0], "cy", 3))
			(*line_num)++;
		free(line);
		ft_split_array_all_free(info);
		if (new_line(*line_num))
			break ;
		else
			line = get_next_line(fd);
	}
}

int	count_num_shapes(char *filename)
{
	int		fd;
	int		line_num;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(ERROR_OPEN);
	line_num = 0;
	line = get_next_line(fd);
	if (!line)
		error_exit(ERROR_EMPTY_FILE);
	count_num_shapes_each_shape(line, fd, &line_num);
	close(fd);
	return (line_num);
}
