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

static double integer_part(char *str, size_t *i)
{
	double integer;
	size_t int_len;

	integer = 0;
	int_len = 0;	
	while(str[*i] && ft_isdigit(str[*i]))
    {
		if (int_len > 10)
		{
			ft_printf_stderr("The compatible range of input values is DBL_MIN to DBL_MAX\n");
			exit(1);
		}
        integer *= 10;
		integer += str[*i] - '0';
		int_len++;
        (*i)++;
    }
	return integer;
}

static size_t decimal_part(char *str, double *decimal, size_t *i)
{
	size_t deci_len;
	deci_len = 0;
	while(str[*i] && ft_isdigit(str[*i]))
    {
		if (deci_len > 4)
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
	integer = integer_part(str, &i);
	if(str[i] != '.')
		return minus_flag * integer;
	i++;
	double decimal;
	double deci_len;
	decimal = 0;
	deci_len = decimal_part(str, &decimal, &i);
    return minus_flag * (integer + (decimal / pow(10, deci_len)));
}
