#include "../../incs/raytracing.h"
#include "../../incs/vector_utils.h"

static void	store_intersection_point_info_case_sphere(intersection_point_t *out_intp,
		ray_t ray, sphere_t sph, float t)
{
	out_intp->distance = t;
	set_vector(&out_intp->position, ray.start.x + t * ray.direction.x,
		ray.start.y + t * ray.direction.y, ray.start.z + t * ray.direction.z);
	set_vector(&out_intp->normal, out_intp->position.x - sph.center.x,
		out_intp->position.y - sph.center.y, out_intp->position.z
		- sph.center.z);
	normalize(&out_intp->normal);
}

static int	evalate_t_value_case_sphere(intersection_point_t *out_intp,
		ray_t ray, sphere_t sph, float t)
{
	if (t > 0)
	{
		if (out_intp) //交点が存在するならば
			store_intersection_point_info_case_sphere(out_intp, ray, sph, t);
		return (1);
	}
	else
		return (0);
}

float	evalate_discriminant(float A, float B, float D)
{
	float	t;
	float	t1;
	float	t2;

	(void)t1;
	(void)t2;
	if (D == 0)
		t = -B / (2 * A);
	else if (D > 0)
	{
		t1 = (-B + sqrt(D)) / (2 * A);
		t2 = (-B - sqrt(D)) / (2 * A);
		if (t1 > 0)
			t = t1;
		if (t2 > 0 && t2 < t)
			t = t2;
	}
	else
		t = -1.0f;
	return (t);
}

static void	calc_quad_function_case_sphere(t_quad_func_info *quad_func_info,
		ray_t ray, sphere_t sph)
{
	quad_func_info->A = dot(&ray.direction, &ray.direction);
	quad_func_info->B = 2 * dot(&ray.direction, &quad_func_info->pe_pc);
	quad_func_info->C = dot(&quad_func_info->pe_pc, &quad_func_info->pe_pc)
		- SQR(sph.radius);
	quad_func_info->D = SQR(quad_func_info->B) - 4 * quad_func_info->A
		* quad_func_info->C;
	quad_func_info->t = evalate_discriminant(quad_func_info->A,
			quad_func_info->B, quad_func_info->D);
}

int	intersection_test_case_shpere(intersection_point_t *out_intp,
		const shape_t *shape, const ray_t *ray)
{
	t_quad_func_info	quad_func_info;
	const sphere_t		*sph;

	sph = &shape->data.sphere;
	set_vector(&quad_func_info.pe_pc, ray->start.x - sph->center.x, ray->start.y
		- sph->center.y, ray->start.z - sph->center.z);
	calc_quad_function_case_sphere(&quad_func_info, *ray, *sph);
	if (evalate_t_value_case_sphere(out_intp, *ray, *sph, quad_func_info.t))
		return (1);
	return (0);
}
