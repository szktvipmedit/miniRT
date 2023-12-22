#include "../incs/minirt.h"

static int sign_flag(char *str, size_t *i)
{
	int minus_flag;

	minus_flag = 1;
	if(str[0] == '+' || str[0] == '-')
	{
		if(str[0] == '-')
			minus_flag = -1;
		(*i)++;
	}
	return minus_flag;
}

static int	ft_isoverflow(long long nbr, unsigned int digit, int sign)
{
	if (sign < 0)
		return ((DBL_MIN + digit) / 10 > (-1) * nbr);
	if (sign > 0)
		return ((DBL_MAX - digit) / 10 < nbr);
	return (0);
}

static double integer_part(char *str, size_t *i, int sign)
{
	double integer;
	integer = 0;
	while(str[*i] && ft_isdigit(str[*i]))
    {
		if (ft_isoverflow(integer, (str[*i] - '0'), sign))
		{
			ft_printf_stderr("The compatible range of input values is DBL_MIN to DBL_MAX\n");
			exit(1);
		}
        integer *= 10;
		integer += str[*i] - '0';
        (*i)++;
    }
	return integer;
}

static size_t decimal_part(char *str, double *decimal, size_t *i, int sign)
{
	size_t deci_len;
	deci_len = 0;
	while(str[*i] && ft_isdigit(str[*i]))
    {
		if (ft_isoverflow(*decimal, (str[*i] - '0'), sign))
		{
			ft_printf_stderr("The compatible range of input values is DBL_MIN to DBL_MAX\n");
			exit(1);
		}
        *decimal *= 10;
		*decimal += str[*i] - '0';
        (*i)++;
		deci_len++;
    }
	return deci_len;
}

double ft_atod(char *str)
{
    /* strに関するエラー処理(ft_)はこの関数実行前にやれ */
    double integer;
    size_t i;
    int minus_flag;
    i = 0;
    minus_flag = 1;
    
	minus_flag = sign_flag(str, &i);
	integer = integer_part(str, &i, minus_flag);
	if(str[i] != '.')
		return minus_flag * integer;
	i++;
	double decimal;
	double deci_len;
	decimal = 0;
	deci_len = decimal_part(str, &decimal, &i, minus_flag);
    return minus_flag * (integer + (decimal / pow(10, deci_len)));
}
