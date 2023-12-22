#include "libft/libft.h"
#include <stdio.h>
static int is_path(char *str)
{
	size_t i;
	i = 0;
	while(str[i])
	{
		if(str[i] == '/')
			return 1;
		i++;
	}	
	return 0;
}
static void get_filename_from_path(char *path)
{
	size_t i;
	size_t len;
	size_t sla_i;
	i = 0;
	if(!is_path(path))
		return ;
	len = ft_strlen(path);
	sla_i = len - 1;
	while (sla_i >= 0)
	{
		if (path[sla_i] == '/')
			break ;
		sla_i--;
	}
	path = path + sla_i+1;

	printf("%s\n",path);
    return;
}
int	main(void)
{
	get_filename_from_path("rt_files/error/.rt");
	get_filename_from_path(".rt");
	get_filename_from_path("rt_files/er.r/or/.rt");
	get_filename_from_path("rt_files/er.r/or/a.rt");
	get_filename_from_path("rt_files/er.r/or/a.art");
	get_filename_from_path("rt_files/er.r/or/afsda.rt");
	get_filename_from_path("rt_files/er.r/or/sfsa.asdrt");
	get_filename_from_path("rt");
}