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

int	count_num_shapes(char *filename)
{
	int fd;
	int line_num;
	char *line;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(ERROR_OPEN);
	line_num = 0;
    line = get_next_line(fd);
    if(!line)
        error_exit(ERROR_EMPTY_FILE);
	while (line)
	{
        if (is_all_spaces(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
        char **info;
        info = ft_split(line, ' ');
        if(!info)
            error_exit(ERROR_MALLOC);
		if (!ft_strncmp(info[0], "sp", 3) ||
            !ft_strncmp(info[0], "pl", 3) ||!ft_strncmp(info[0], "cy", 3))
            line_num++;
        free(line);
        ft_split_array_all_free(info);
        if(line_num < INT_MAX)
            line = get_next_line(fd);
        else
        {
            ft_printf_stderr(NOTICE_MAX_OBJECTS);
            break;
        }
	}
    close(fd);
    return line_num;
}