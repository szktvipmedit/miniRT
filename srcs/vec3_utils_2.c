/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:50:16 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/22 14:50:19 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

t_vec3	v_init(double x, double y, double z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3	v_add(t_vec3 a, t_vec3 b)
{
	return (v_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	v_sub(t_vec3 a, t_vec3 b)
{
	return (v_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	v_mult(t_vec3 a, double b)
{
	return (v_init(a.x * b, a.y * b, a.z * b));
}
