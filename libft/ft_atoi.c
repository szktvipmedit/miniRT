/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:11:34 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/05 14:52:07 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_skip(char **str, int *sign, size_t *i)
{
	while (((*str)[*i] >= 9 && (*str)[*i] <= 13) || (*str)[*i] == 32)
			(*i)++;
	if ((*str)[*i] == '-' || (*str)[*i] == '+')
	{
		if ((*str)[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

static int	ft_isoverflow(long long nbr, unsigned int digit, int sign)
{
	if (sign < 0)
	{
		// printf("--------digit %u----------\n", digit);
		// printf("L+d    %i\n", INT_MIN + digit);
		// int i =INT_MIN + digit;
		// printf("L+d/10 %i\n", (INT_MIN + digit) / 10);
		// printf("nbr    %lli\n", -nbr);
		return ((INT_MIN + digit) / 10 > (-1) * nbr);
	}
	if (sign > 0)
	{
		// printf("--------digit %u----------\n", digit);
		// printf("L-d    %i\n", INT_MAX - digit);
		// printf("L-d/10 %i\n", i / 10);
		// printf("nbr    %lli\n", nbr);
		return ((INT_MAX - digit) / 10 < nbr);
	}
	return (0);
}

int	ft_atoi(char *str)
{
	size_t		i;
	long long	nbr;
	int			sign;

	i = 0;
	nbr = 0;
	sign = 1;
	ft_skip(&str, &sign, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (ft_isoverflow(nbr, (str[i] - '0'), sign))
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		nbr = (10 * nbr) + (str[i] - '0');
		i++;
	}
	return ((int)(sign * nbr));
}


// int main()
// {
// 	int i = -214748364;
// 	printf("%i\n", ft_atoi("2147483648"));
// 	printf("\n\n\n");
// 	printf("%i\n", ft_atoi("-2147483648"));
// 	printf("%i", i);
// }