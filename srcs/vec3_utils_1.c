/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:50:11 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/22 14:50:15 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

double	square(double x)
{
	return (x * x);
}

// 最小値を返す関数
double	min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

// 最大値を返す関数
double	max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

//constrain 関数をC言語で実装した例
double	constrain(double v, double vmin, double vmax)
{
	if (v < vmin)
		return (vmin);
	else if (v > vmax)
		return (vmax);
	else
		return (v);
}
