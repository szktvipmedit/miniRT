/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_test_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:53:29 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/22 16:54:01 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

void	store_cylinder_info_out(t_intersection_point *out_intp, t_cy *cy,
		t_cylinder *cylin)
{
	out_intp->normal = v_sub(cy->center_2p_outer, v_mult(cylin->normal,
				cy->height_outer));
	out_intp->normal = v_normalize(out_intp->normal);
	out_intp->distance = cy->t_outer;
	out_intp->position = cy->p_outer;
}

void	store_cylinder_info_in(t_intersection_point *out_intp, t_cy *cy,
		t_cylinder *cylin)
{
	out_intp->normal = v_sub(v_mult(cylin->normal, cy->height_inner),
			cy->center_2p_inner);
	out_intp->normal = v_normalize(out_intp->normal);
	out_intp->distance = cy->t_inner;
	out_intp->position = cy->p_inner;
}
