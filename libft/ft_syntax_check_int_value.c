#include "libft.h"

static int ft_sign_check(char c, size_t *i)
{
	if(c != '+' && c != '-' && !ft_isdigit(c))
		return 1;
	if(c == '+' || c == '-')
		i++;
	return 0;
}

static int integer_part(char *str, size_t *i)
{
	while(str[*i])
    {
        if(!ft_isdigit(str[*i]))
            return 1;
        (*i)++;
    }
    return 0;
}

int ft_syntax_check_double_value(char *str)
{
    size_t i;
    i = 0;
    
	if(ft_sign_check(str[0], &i))
		return 1;
    integer_part(str, &i);
    return 0;
}


