#include "libft.h"
void ft_split_array_all_free(char **str)
{
    size_t len;
    len = 0;
    while(str[len])
        len++;
    len--;
    while(len >= 0 && str[len])
    {
        free(str[len]);
        len--;
    }
    free(str);
}