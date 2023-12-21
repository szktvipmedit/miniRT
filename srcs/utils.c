#include "../incs/minirt.h"

void	ft_split_array_all_free(char **str)
{
	ssize_t len;
	len = 0;
	while (str[len])
			len++;
	len--;
	while (len >= 0 && str[len])
	{	
		free(str[len]);
		str[len] = 0;
		len--;
	}
	free(str);
	str = 0;
}

static int	ft_sign_check(char c, size_t *i)
{
	(void)i;
	if (c != '+' && c != '-' && !ft_isdigit(c))
		return (1);
	if (c == '+' || c == '-')
		(*i)++;
	return (0);
}

static void	integer_part(char *str, size_t *i)
{
	while (str[*i])
	{
		if (!ft_isdigit(str[*i]))
			break ;
		(*i)++;
	}
}

static int	decimal_part(char *str, size_t *i)
{
	if (!ft_isdigit(str[*i]))
		return (1);
	while (str[*i])
	{
		//小数部では数字以外なら以上終了
		if (!ft_isdigit(str[*i]))
			return (1);
		(*i)++;
	}
	return (0);
}
int	ft_syntax_check_double_value(char *str)
{
	size_t	i;
	i = 0;
	if (ft_sign_check(str[0], &i))
		return (1);
	integer_part(str, &i);
	if (str[i] == '\0')
		return (0);
	if (str[i] != '.')
		return (1);
	i++;
	if (decimal_part(str, &i))
		return (1);
	return (0);
}