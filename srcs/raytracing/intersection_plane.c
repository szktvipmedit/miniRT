#include "../../incs/raytracing.h"
#include "../../incs/vector_utils.h"

static void	store_intersection_point_info_case_plane(intersection_point_t *out_intp,
		ray_t ray, plane_t pln, float t)
{
	out_intp->distance = t;
	out_intp->position.x = ray.start.x + t * ray.direction.x;
	out_intp->position.y = ray.start.y + t * ray.direction.y;
	out_intp->position.z = ray.start.z + t * ray.direction.z;
	out_intp->normal = pln.normal;
}

static int	evalate_t_value_case_plane(intersection_point_t *out_intp,
		ray_t ray, plane_t pln, float t)
{
	if (t > 0)
	{
		if (out_intp)
			store_intersection_point_info_case_plane(out_intp, ray, pln, t);
		return (1);
	}
	return (0);
}

static float	calc_t_value(ray_t ray, plane_t pln, float dn_dot)
{
	vector_t	s_p;

	s_p.x = ray.start.x - pln.position.x;
	s_p.y = ray.start.y - pln.position.y;
	s_p.z = ray.start.z - pln.position.z;
	return (-dot(&s_p, &pln.normal) / dn_dot);
}

int	intersection_test_case_plane(intersection_point_t *out_intp,
		const shape_t *shape, const ray_t *ray)
{
	const plane_t	*pln;
	float			dn_dot;
	float			t;

	(void)t;
	pln = &shape->data.plane;
	dn_dot = dot(&ray->direction, &pln->normal);
	if (dn_dot != 0)
	{
		t = calc_t_value(*ray, *pln, dn_dot);
		if (evalate_t_value_case_plane(out_intp, *ray, *pln, t))
			return (1);
		return (0);
	}
	return (0);
}
