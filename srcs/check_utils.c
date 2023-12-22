#include "../incs/minirt.h"

size_t	count_info_in_line(char **info)
{
	size_t	len;

	len = 0;
	while (info[len])
		len++;
	return (len);
}

void	check_info_count(char **info, size_t need_info_count, int line_num)
{
	if (count_info_in_line(info) != need_info_count)
	{
		printf("Error :.rt : line \
%i: Check how much information this object requires", line_num);
		exit(1);
	}
}

double	check_range_value(double val, double range_min, double range_max,
		int line_num)
{
	if (!(range_min <= val && val <= range_max))
	{
		ft_printf_stderr("Error :.rt : line \
%i: Check the range of specified values", line_num);
		exit(1);
	}
	return (val);
}

// void    check_str_double_range(char *str)
// {

// }

double	create_double_value(char *str, int line_num)
{
	double val;
	if (ft_syntax_check_double_value(str))
	{
		ft_printf_stderr("Error :.rt : line %i: %s is invalid value. ",
			line_num, str);
		exit(1);
	}
	val = ft_atod(str);
	return (val);
}