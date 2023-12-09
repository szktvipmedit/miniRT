#include "../incs/minirt.h"

void    read_ambient_light_info(t_rt *rt_info, char *line)
{
    while()
}

void    read_info(t_rt *rt_info, char *filename)
{
    int fd;
    int line_num;
    char *line;    
    fd = open(filename, O_RDONLY);
    line_num = 1;
    while(line = get_next_line(fd))
    {
        if(!ft_strncmp(line, "A ", 2))
            read_ambient_light_info(rt_info, line);
        else if(!ft_strncmp(line, "C ", 2))
            read_camera_info(rt_info, line);
        else if(!ft_strncmp(line, "L ", 2))
            read_light_info(rt_info, line);
        else if(!ft_strncmp(line, "sp ", 3))
            read_sphere_info(rt_info, line);
        else if(!ft_strncmp(line, "pl ", 3))
            read_plane_info(rt_info, line);
        else if(!ft_strncmp(line, "cy ", 3))
            read_cylinder_info(rt_info, line);
        else
            ft_printf_stderr("%s: %zu: invalid identifier\n", filename, line_num);
        line_num++;
    }
}