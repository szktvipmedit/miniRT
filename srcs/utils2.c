#include "../incs/minirt.h"

double ft_atod(char *str)
{
    /* strに関するエラー処理(ft_)はこの関数実行前にやれ */
    double integer;
	
    size_t i;
    int minus_flag;
    integer = 0;
    i = 0;
    minus_flag = 1;
    
	if(str[0] == '+' || str[0] == '-')
	{
		if(str[0] == '-')
			minus_flag = -1;
		i++;
	} 
    //正数部
    while(str[i] && ft_isdigit(str[i]))
    {
        integer *= 10;
		integer += str[i] - '0';
        i++;
    }
	if(str[i] != '.')
		return minus_flag * integer;
	i++;
    //少数部
	double decimal;
	size_t deci_len;
	decimal = 0;
	deci_len = 0;
	while(str[i] && ft_isdigit(str[i]))
    {
        decimal *= 10;
		decimal += str[i] - '0';
        i++;
		deci_len++;
    }
    return minus_flag * (integer + (decimal / pow(10, deci_len)));
}

int	ft_isverify_file_extension(char *filename, char *extension)
{
	size_t	i;
	size_t	dot_i;
	size_t	len;

	if (!filename || !extension || ft_strlen(filename) == 1)
    	error_exit("Error: ft_isverify_file_extension()\n");
	i = 0;
	len = ft_strlen(filename);
	dot_i = len - 1;
	while (dot_i >= 0)
	{
		if (filename[dot_i] == '.')
			break ;
		dot_i--;
	}
	while (i < ft_strlen(extension))
	{
		if (dot_i == 0 || filename[dot_i++] != extension[i++])
			return (0);
	}
	return (1);
}

// int main()
// {
// 	double f = 500.21309481891;

//     printf("%f\n", ft_atod("0a.21309481891"));
//     printf("%f\n", f);
// }