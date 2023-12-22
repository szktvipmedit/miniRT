/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_test_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:51:36 by jyasukaw          #+#    #+#             */
/*   Updated: 2023/12/22 16:52:55 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

void	ft_calculate_sphere_t(t_sphere *sph,
							t_ray *ray,
							t_vec3 pe_pc,
							double *t)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	c2;

	a = v_dot(ray->direction, ray->direction);
	b = 2 * v_dot(ray->direction, pe_pc);
	c = v_dot(pe_pc, pe_pc) - square(sph->radius);
	d = square(b) - 4 * a * c;
	if (d == 0)
		*t = -b / (2 * a);
	else if (d > 0)
	{
		c = (-b + sqrt(d)) / (2 * a);
		c2 = (-b - sqrt(d)) / (2 * a);
		if (c > 0)
			*t = c;
		if (c2 > 0 && c2 < *t)
			*t = c2;
	}
}

int	ft_test_sphere(t_shape *shape, t_ray *ray, t_intersection_point *out_intp)
{
	t_sphere	*sph;
	t_vec3		pe_pc;
	double		t;

	sph = &shape->u_data.sphere;
	pe_pc = v_sub(ray->start, sph->center);
	t = -1.0;
	ft_calculate_sphere_t(sph, ray, pe_pc, &t);
	if (t > 0)
	{
		if (out_intp)
		{
			out_intp->distance = t;
			out_intp->position = v_add(ray->start, v_mult(ray->direction, t));
			out_intp->normal = v_sub(out_intp->position, sph->center);
			out_intp->normal = v_normalize(out_intp->normal);
		}
		return (1);
	}
	else
		return (0);
}

int	ft_test_plane(t_shape *shape, t_ray *ray, t_intersection_point *out_intp)
{
	t_plane	*pln;
	double	dn_dot;
	t_vec3	s_p;
	double	t;

	pln = &shape->u_data.plane;
	dn_dot = v_dot(ray->direction, pln->normal);
	if (dn_dot == 0)
		return (0);
	s_p = v_sub(ray->start, pln->position);
	t = -v_dot(s_p, pln->normal) / dn_dot;
	if (t > 0)
	{
		if (out_intp)
		{
			out_intp->distance = t;
			out_intp->position = v_add(ray->start, v_mult(ray->direction, t));
			if (dn_dot > 0)
				out_intp->normal = v_mult(pln->normal, -1);
			else
				out_intp->normal = pln->normal;
		}
		return (1);
	}
	return (0);
}

int	ft_set_cy_info(t_cy *cy, t_cylinder *cylin, t_ray *ray)
{
	cy->a = v_norm(v_cross(ray->direction, cylin->normal));
	cy->a = square(cy->a);
	cy->b = 2 * v_dot(v_cross(ray->direction, cylin->normal),
			v_cross(v_sub(ray->start, cylin->position), cylin->normal));
	cy->c = v_norm(v_cross(v_sub(ray->start, cylin->position), cylin->normal));
	cy->c = square(cy->c) - square(cylin->radius);
	cy->d = square(cy->b) - 4 * cy->a * cy->c;
	if (cy->d < 0)
		return (-1);
	cy->t_outer = (-cy->b - sqrt(cy->d)) / (2 * cy->a);
	cy->t_inner = (-cy->b + sqrt(cy->d)) / (2 * cy->a);
	cy->p_outer = v_add(ray->start, v_mult(ray->direction, cy->t_outer));
	cy->p_inner = v_add(ray->start, v_mult(ray->direction, cy->t_inner));
	cy->center_2p_outer = v_sub(cy->p_outer, v_add(cylin->position,
				v_mult(v_mult(cylin->normal, -1), cylin->height / 2)));
	cy->center_2p_inner = v_sub(cy->p_inner, v_add(cylin->position,
				v_mult(v_mult(cylin->normal, -1), cylin->height / 2)));
	cy->height_outer = v_dot(cy->center_2p_outer, cylin->normal);
	cy->height_inner = v_dot(cy->center_2p_inner, cylin->normal);
	return (0);
}

int	ft_test_cylinder(t_shape *shape, t_ray *ray, t_intersection_point *out_intp,
		t_rt *rt)
{
	t_cylinder	*cylin;
	t_cy		cy;

	cylin = &shape->u_data.cylinder;
	if (ft_set_cy_info(&cy, cylin, ray) == -1)
		return (0);
	if (fabs(rt->scene.camera.forward_dir.x - cylin->normal.x) < EPSILON
		&& fabs(rt->scene.camera.forward_dir.y - cylin->normal.y) < EPSILON
		&& fabs(rt->scene.camera.forward_dir.z - cylin->normal.z) < EPSILON)
		return (0);
	if (cy.height_outer >= 0 && cy.height_outer <= cylin->height)
	{
		store_cylinder_info_out(out_intp, &cy, cylin);
		if (cy.t_outer > 0)
			return (1);
	}
	else if (cy.height_inner >= 0 && cy.height_inner <= cylin->height)
	{
		store_cylinder_info_in(out_intp, &cy, cylin);
		if (cy.t_inner > 0)
			return (1);
	}
	return (0);
}
