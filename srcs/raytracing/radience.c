#include "../../incs/raytracing.h"
#include "../../incs/vector_utils.h"
static void	calc_perfect_refrect_radience(const scene_t *scene,
		const ray_t *eye_ray, intersection_point_t *inter_p,
		t_pixel_info *pixel_info)
{
	vector_t	r_eye_ray;
	float		vndot;
	vector_t	ref_eye_dir;
		ray_t ref_ray;

	r_eye_ray = ft_mult_vec(eye_ray->direction, -1);
	normalize(&r_eye_ray);
	vndot = dot(&r_eye_ray, &inter_p->normal);
	if (vndot > 0)
	{
		ref_eye_dir = ft_sub_vec(ft_mult_vec(inter_p->normal, 2 * vndot),
				r_eye_ray);
		ref_ray.start = ft_add_vec(inter_p->position, ft_mult_vec(ref_eye_dir,
					EPSILON));
		ref_ray.direction = ref_eye_dir;
		recursive_raytrace(scene, &ref_ray, &pixel_info->ref_rd,
			pixel_info->recursion_level + 1);
		pixel_info->ref_rd.r = ft_constrain(vndot, 0, 1)
			* pixel_info->shape->material.reflect_ref.r * pixel_info->ref_rd.r;
		pixel_info->ref_rd.g = ft_constrain(vndot, 0, 1)
			* pixel_info->shape->material.reflect_ref.g * pixel_info->ref_rd.g;
		pixel_info->ref_rd.b = ft_constrain(vndot, 0, 1)
			* pixel_info->shape->material.reflect_ref.b * pixel_info->ref_rd.b;
	}
}

static void	calc_ambiant_radience(const scene_t *scene, t_pixel_info *pixel_info)
{
	set_color(&pixel_info->amb_rd, scene->shapes->material.ambient_ref.r
		* scene->ambient_illuminance.r, scene->shapes->material.ambient_ref.g
		* scene->ambient_illuminance.g, scene->shapes->material.ambient_ref.b
		* scene->ambient_illuminance.b);
}

static void	calc_diffuse_reflection_radience(const scene_t *scene,
		t_pixel_info *pixel_info, float nldot)
{
	set_color(&pixel_info->dif_rd, ft_constrain(nldot, 0, 1)
		* pixel_info->shape->material.diffuse_ref.r
		* scene->lights->illuminance.r, ft_constrain(nldot, 0, 1)
		* pixel_info->shape->material.diffuse_ref.g
		* scene->lights->illuminance.g, ft_constrain(nldot, 0, 1)
		* pixel_info->shape->material.diffuse_ref.b
		* scene->lights->illuminance.b);
}
static void	calc_specular_reflection_radience(const scene_t *scene,
		t_pixel_info *pixel_info, const ray_t *eye_ray, float nldot)
{
	vector_t	r_eye_ray;
	vector_t	ref_vec;
	float		vrdot;

	r_eye_ray = ft_mult_vec(eye_ray->direction, -1);
	normalize(&r_eye_ray);
	ref_vec = ft_sub_vec(ft_mult_vec(pixel_info->inter_p.normal, (nldot * 2)),
			pixel_info->light_dir);
	vrdot = dot(&r_eye_ray, &ref_vec);
	set_color(&pixel_info->sep_rd, pow(ft_constrain(vrdot, 0, 1),
			pixel_info->shape->material.shininess)
		* pixel_info->shape->material.specular_ref.r
		* scene->lights->illuminance.r, pow(ft_constrain(vrdot, 0, 1),
			pixel_info->shape->material.shininess)
		* pixel_info->shape->material.specular_ref.g
		* scene->lights->illuminance.g, pow(ft_constrain(vrdot, 0, 1),
			pixel_info->shape->material.shininess)
		* pixel_info->shape->material.specular_ref.b
		* scene->lights->illuminance.b);
}
void	calc_radience(const scene_t *scene, t_pixel_info *pixel_info,
		const ray_t *eye_ray, float dist_intp_light)
{
	float	nldot;

	if (pixel_info->shape->material.type == MT_PERFECT_REF) // shapeが完全鏡面反射するならば
		calc_perfect_refrect_radience(scene, eye_ray, &pixel_info->inter_p,
			pixel_info);
	if (!get_nearest_shape(scene, &pixel_info->shadow_ray, dist_intp_light, 1,
			&pixel_info->shape, &pixel_info->inter_p))
		//視点と物体の交点から光源の間に物体が存在せず、直接光が来るなら拡散反射輝度と鏡面反射輝度を計算する
	{
		nldot = dot(&pixel_info->inter_p.normal, &pixel_info->light_dir);
		calc_diffuse_reflection_radience(scene, pixel_info, nldot);
		if (nldot > 0)
			calc_specular_reflection_radience(scene, pixel_info, eye_ray,
				nldot);
	}
	calc_ambiant_radience(scene, pixel_info);
}
