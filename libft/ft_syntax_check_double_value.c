#include "libft.h"

static int ft_sign_check(char c, size_t *i)
{
	if(c != '+' && c != '-' && !ft_isdigit(c))
		return 1;
	if(c == '+' || c == '-')
		i++;
	return 0;
}

static void integer_part(char *str, size_t *i)
{
	while(str[*i])
    {
        if(!ft_isdigit(str[*i]))
            break;
        (*i)++;
    }
}

static int decimal_part(char *str, size_t *i)
{
	if(!ft_isdigit(str[*i]))
		return 1;
    while(str[*i])
    {
        //小数部では数字以外なら以上終了
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
    if(str[i] == '\0')
        return 0;
    if(str[i] != '.')
        return 1;
    i++;
	if(decimal_part(str, &i))
		return 1;
    return 0;
}


// #include <stdio.h>
// int main()
// {
// 	printf("500 : %i\n",ft_syntax_check_double_value("500"));
// 	printf("500.3419 : %i\n",ft_syntax_check_double_value("500.3419"));
// 	printf("0.14314 : %i\n",ft_syntax_check_double_value("0.14314"));
// 	printf("a : %i\n",ft_syntax_check_double_value("a"));
// 	printf("143a.3409 : %i\n",ft_syntax_check_double_value("143a.3409"));
// 	printf("1432a340.1494 : %i\n",ft_syntax_check_double_value("1432a340.1494"));
// 	printf("1434.a139 : %i\n",ft_syntax_check_double_value("1434.a139"));
// 	printf("1491.14a14 : %i\n",ft_syntax_check_double_value("1491.14a14"));
// 	printf("500. : %i\n",ft_syntax_check_double_value("500."));
// 	printf("500a : %i\n",ft_syntax_check_double_value("500a"));
// 	printf(".300 : %i\n",ft_syntax_check_double_value(".300"));
// 	printf("0.14a13 : %i\n",ft_syntax_check_double_value("0.14a13"));
// 	printf("349.43289. : %i\n",ft_syntax_check_double_value("349.43289."));
// }
