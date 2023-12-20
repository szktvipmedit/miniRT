#include "../../incs/raytracing.h"
#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void	create_shadow_ray(t_pixel_info *pixel_info)
{
	pixel_info->shadow_ray.start = ft_add_vec(pixel_info->inter_p.position,
			ft_mult_vec(pixel_info->light_dir, EPSILON));
	pixel_info->shadow_ray.direction = pixel_info->light_dir;
}

void	calc_color(const scene_t *scene, t_pixel_info *pixel_info,
		const ray_t *eye_ray, colorf_t *out_col)
{
	float dist_intp_light; //視線と物体の交点からlightまでの距離。これを超えたところに物体があっても影にならない
	pixel_info->light_dir = ft_sub_vec(scene->lights->vector,
			pixel_info->inter_p.position);
	dist_intp_light = norm(&pixel_info->light_dir);
	//{視線と物体の交点}と{light}の距離は正規化前の入射ベクトルと同じ
	normalize(&pixel_info->light_dir);
	//入射ベクトルが決定した時点で影の計算に入る
	create_shadow_ray(pixel_info);
	calc_radience(scene, pixel_info, eye_ray, dist_intp_light);
	set_color(out_col, ft_constrain(pixel_info->amb_rd.r + pixel_info->dif_rd.r
			+ pixel_info->sep_rd.r + pixel_info->ref_rd.r, 0, 1),
		ft_constrain(pixel_info->amb_rd.g + pixel_info->dif_rd.g
			+ pixel_info->sep_rd.g + pixel_info->ref_rd.g, 0, 1),
		ft_constrain(pixel_info->amb_rd.b + pixel_info->dif_rd.b
			+ pixel_info->sep_rd.b + pixel_info->ref_rd.b, 0, 1));
}

int	recursive_raytrace(const scene_t *scene, const ray_t *eye_ray,
		colorf_t *out_col, int recursion_level)
{
	t_pixel_info	pixel_info;

	if (recursion_level > MAX_RECURSION)
		return (0);
	else
	{
		pixel_info.recursion_level = recursion_level;
		init_color(&pixel_info);
		if (get_nearest_shape(scene, eye_ray, FLT_MAX, 0, &pixel_info.shape,
								&pixel_info.inter_p)) //視線と物体の交点を見つける
			calc_color(scene, &pixel_info, eye_ray, out_col);
	}
	return (0);
} /* int raytrace(const scene_t* scene, const ray_t *eye_ray,
	colorf_t *out_col) */
int	raytrace(const scene_t *scene, const ray_t *eye_ray, colorf_t *out_col)
{
	return (recursive_raytrace(scene, eye_ray, out_col, 0));
}

int	intersection_test(const shape_t *shape, const ray_t *ray,
		intersection_point_t *out_intp)
{
	if (shape->type == ST_SPHERE)
		return (intersection_test_case_shpere(out_intp, shape, ray));
	else if (shape->type == ST_PLANE)
		return (intersection_test_case_plane(out_intp, shape, ray));
	return (0);
	/* int intersection_test(const shape_t *shape, const ray_t* ray,  */
}

int	get_nearest_shape_info(shape_t *shape, const ray_t *ray,
		intersection_point_t *nearest_intp, shape_t **nearest_shape,
		int exit_once_found)
{
	int						res;
	intersection_point_t	intp;

	(void)nearest_shape;
	res = intersection_test(shape, ray, &intp);
	if (res && intp.distance < nearest_intp->distance)
	{
		*nearest_shape = shape;
		*nearest_intp = intp;
		if (exit_once_found)
			return (1);
	}
	return (0);
}

int	get_nearest_shape(const scene_t *scene, const ray_t *ray, float max_dist,
		int exit_once_found, shape_t **out_shape,
		intersection_point_t *out_intp)
{
	size_t					i;
	shape_t					*nearest_shape;
	intersection_point_t	nearest_intp;

	i = 0;
	nearest_shape = NULL;
	nearest_intp.distance = max_dist;
	while (i < scene->num_shapes)
	{
		if (get_nearest_shape_info(&scene->shapes[i], ray, &nearest_intp,
				&nearest_shape, exit_once_found))
			break ;
		i++;
	}
	if (nearest_shape)
		return (store_out_variable(nearest_shape, nearest_intp, out_shape,
				out_intp));
	return (0);
}
void init_shape(shape_t* shape, shape_type st, ...)
{
  va_list args;
  va_start(args, st);

  shape->type = st;
  if ( st == ST_SPHERE )
    {
      sphere_t* sph = &shape->data.sphere;
      
      sph->center.x = va_arg(args, double);
      sph->center.y = va_arg(args, double);
      sph->center.z = va_arg(args, double);
      sph->radius   = va_arg(args, double);
    }
  else if ( st == ST_PLANE )
    {
      plane_t* plane = &shape->data.plane;
      
      plane->position.x = va_arg(args, double);
      plane->position.y = va_arg(args, double);
      plane->position.z = va_arg(args, double);

      plane->normal.x = va_arg(args, double);
      plane->normal.y = va_arg(args, double);
      plane->normal.z = va_arg(args, double);
    }
  else
    {
      fprintf(stderr, "init_shape : unknown shape type.\n");
      abort();
    }
  
  va_end(args);
}

void init_material(material_t* mat,
		   float ambR, float ambG, float ambB,
		   float difR, float difG, float difB,
		   float speR, float speG, float speB,
		   float shns, material_type type,
       float refR, float refG, float refB)
{
  SET_COLOR(mat->ambient_ref,  ambR, ambG, ambB);
  SET_COLOR(mat->diffuse_ref,  difR, difG, difB);
  SET_COLOR(mat->specular_ref, speR, speG, speB);
  mat->shininess = shns;
  mat->type = type;
  SET_COLOR(mat->reflect_ref, refR, refG, refB)
}

void init_light(light_t* light, light_type lt,
		float vx, float vy, float vz,
		float illR, float illG, float illB)
{
  light->type = lt;
  SET_VECTOR(light->vector, vx, vy, vz);
  SET_COLOR(light->illuminance, illR, illG, illB);
}