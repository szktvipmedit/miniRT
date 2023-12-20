#include "libft.h"
#include <stdio.h>

double ft_atod(char *str)
{
    /* strに関するエラー処理(ft_)はこの関数実行前にやれ */
    double num;
    size_t i;
    int minus_flag;
    num = 0;
    i = 0;
    minus_flag = 1;
    
    //正数部
    while(str[i] && ft_isdigit(str[i]))
    {
        
        i++;
    }

    //少数部
    return num;
}

int main()
{
    ft_atod("500.2128");
}