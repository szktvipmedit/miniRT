#include "../incs/minirt.h"

void	ft_add_ambient_color(t_scene scene, t_color3 *color)
{
	color->r += scene.ambient.ambient_ref * scene.ambient.ambient_illuminance.r;
	color->g += scene.ambient.ambient_ref * scene.ambient.ambient_illuminance.g;
	color->b += scene.ambient.ambient_ref * scene.ambient.ambient_illuminance.b;
}

void	ft_add_diffuse_color(t_scene scene, t_shape *shape, double nl_dot, t_color3 *color)
{
	color->r += shape->material.diffuse_ref.r * scene.light.illuminance.r * nl_dot;
	color->g += shape->material.diffuse_ref.g * scene.light.illuminance.g * nl_dot;
	color->b += shape->material.diffuse_ref.b * scene.light.illuminance.b * nl_dot;
}

void	ft_add_specular_color(t_scene scene, double vr_dot_pow, t_color3 *color)
{
	color->r += scene.light.specular_ref * scene.light.illuminance.r * vr_dot_pow;
	color->g += scene.light.specular_ref * scene.light.illuminance.g * vr_dot_pow;
	color->b += scene.light.specular_ref * scene.light.illuminance.b * vr_dot_pow;
}

void	ft_add_light_ref_color(t_rt *rt, t_shape *shape, t_intersection_point intp, t_vec3 light_dir)
{
	double nl_dot;
	t_vec3 ref_dir;
	t_vec3 inv_eye_dir;
	double vr_dot;
	double vr_dot_pow;

	nl_dot = dot(&light_dir, &intp.normal);
	nl_dot = constrain(nl_dot, 0, 1);
	ft_add_diffuse_color(rt->scene, shape, nl_dot, &rt->color);
	if (nl_dot > 0)
	{
		ref_dir = v_sub(v_mult(intp.normal, 2 * nl_dot), light_dir);
		ref_dir = v_normalize(ref_dir);
		inv_eye_dir = v_mult(rt->ray.direction, -1);
		inv_eye_dir = v_normalize(inv_eye_dir);
		vr_dot = dot(&inv_eye_dir, &ref_dir);
		vr_dot = constrain(vr_dot, 0, 1);
		vr_dot_pow = pow(vr_dot, shape->material.shininess);
		ft_add_specular_color(rt->scene, vr_dot_pow, &rt->color);
	}
}




void	ft_raytrace(t_rt *rt)
{
	t_shape 							*shape;
	t_intersection_point	intp;
	t_vec3 								light_dir;
	double 								dl;
	t_intersection_point	tmp;

	rt->flag = get_nearest_shape(rt, &rt->ray, &shape, &intp);//視線方向(ray)の方向でもっとも近い物体を探す
	if (rt->flag == 0)//視線方向に物体がなかった場合はここでreturn
		return ;
  ft_add_ambient_color(rt->scene, &rt->color);//環境光の強さを計算してcolに入れる
	light_dir = v_sub(rt->scene.light.vector, intp.position);
	dl = v_norm(light_dir) - EPSILON;//正規化する前の入射ベクトルの大きさを代入
	light_dir = v_normalize(light_dir);
	rt->shadow_ray.start = v_add(intp.position, v_mult(light_dir, EPSILON));
	rt->shadow_ray.direction = light_dir;
	rt->flag = SHADOW;
	rt->flag = get_nearest_shape(rt, &rt->shadow_ray, &shape, &tmp);
	if (rt->flag == 0 || dl < tmp.distance)
		ft_add_light_ref_color(rt, shape, intp, light_dir);
}




int intersection_test(const t_shape *shape, const t_ray* ray, t_intersection_point* out_intp)
{
  if ( shape->type == ST_SPHERE )
    {
      const t_sphere *sph = &shape->u_data.sphere;
      t_vec3 pe_pc;
      double A,B,C,D;
      double t;
      
      pe_pc.x = ray->start.x - sph->center.x;
      pe_pc.y = ray->start.y - sph->center.y;
      pe_pc.z = ray->start.z - sph->center.z;

      A = dot(&ray->direction, &ray->direction);
      B = 2 * dot(&ray->direction, &pe_pc);
      C = dot(&pe_pc, &pe_pc) - square(sph->radius);
      D = square(B) - 4*A*C;

      t = -1.0f;
      if ( D == 0 )
				t = -B / (2*A);
			else if ( D > 0 )
			{
				double t1 = (-B + sqrt(D))/(2*A);
				double t2 = (-B - sqrt(D))/(2*A);

				if ( t1 > 0 ) t = t1;
				if ( t2 > 0 && t2 < t ) t = t2;
			}
      if ( t > 0 )
			{
				if ( out_intp )
				{
					out_intp->distance = t;
					
					out_intp->position.x = ray->start.x + t * ray->direction.x;
					out_intp->position.y = ray->start.y + t * ray->direction.y;
					out_intp->position.z = ray->start.z + t * ray->direction.z;

					out_intp->normal.x = out_intp->position.x - sph->center.x;
					out_intp->normal.y = out_intp->position.y - sph->center.y;
					out_intp->normal.z = out_intp->position.z - sph->center.z;
					out_intp->normal = v_normalize(out_intp->normal);
				}
				return 1;
			}
			else
				return 0;
    }
  else if ( shape->type == ST_PLANE )
    {
      const t_plane *pln = &shape->u_data.plane;
      double dn_dot = dot(&ray->direction, &pln->normal);

      if ( dn_dot != 0 )
        {
          t_vec3 s_p;
          double t;
          
          s_p.x = ray->start.x - pln->position.x;
          s_p.y = ray->start.y - pln->position.y;
          s_p.z = ray->start.z - pln->position.z;

          t = -dot(&s_p, &pln->normal) / dn_dot;

          if ( t > 0 )
            {
              if ( out_intp )
                {
                  out_intp->distance = t;

                  out_intp->position.x = ray->start.x + t * ray->direction.x;
                  out_intp->position.y = ray->start.y + t * ray->direction.y;
                  out_intp->position.z = ray->start.z + t * ray->direction.z;
                  // dn_dotがマイナスだったらなす角が90°より大きいから法線ベクトルを逆向きになる
                  out_intp->normal = dn_dot > 0 ? v_mult(pln->normal, -1) : pln->normal;//-1をかけるタイミングに依存
                  // out_intp->normal = pln->normal;
                }

              return 1;
            }
          else
            {
              return 0;
            }
        }
    }
    else if ( shape->type == ST_CYLINDER )
    {
      const t_cylinder *cylin = &shape->u_data.cylinder;
      t_vec3 n = v_init(0, 1, 0);

      // レイが球に当たったか計算する
      double a = v_norm(v_cross(ray->direction, n));
      a = a * a;
      double b = 2 * v_dot(v_cross(ray->direction, n), v_cross(v_sub(ray->start, cylin->position), n));
      double c = v_norm(v_cross(v_sub(ray->start, cylin->position), n));
      c = c * c - cylin->radius * cylin->radius;
      // 判別式
      double d = b * b - 4 * a * c;

      if (d < 0)
      {
        return (0);
      }

      // レイと円筒との距離を求める
      double t_outer = (-b - sqrt(d)) / (2 * a);  // 円筒の外側
      double t_inner = (-b + sqrt(d)) / (2 * a);  // 円筒の内側

      // レイと縦に無限に伸びる円筒との交点
      t_vec3 p_outer = v_add(ray->start, v_mult(ray->direction, t_outer));
      t_vec3 p_inner = v_add(ray->start, v_mult(ray->direction, t_inner));

      t_vec3 center2p_outer = v_sub(p_outer, cylin->position);
      t_vec3 center2p_inner = v_sub(p_inner, cylin->position);

      // 底面から交点までの高さ
      double height_outer = v_dot(center2p_outer, n);
      double height_inner = v_dot(center2p_inner, n);

      if (height_outer >= 0 && height_outer <= cylin->height)
      {
        out_intp->normal = v_sub(center2p_outer, v_mult(n, height_outer));
        out_intp->normal = v_normalize(out_intp->normal);
        out_intp->distance = t_outer;
        out_intp->position = p_outer;
        if (t_outer > 0)//やっぱりこれ必要だった
          return (1);
      }
      else if (height_inner >= 0 && height_inner <= cylin->height)
      {
        out_intp->normal = v_sub(v_mult(n, height_inner), center2p_inner);
        out_intp->normal = v_normalize(out_intp->normal);
        out_intp->distance = t_inner;
        out_intp->position = p_inner;
        if (t_inner > 0)
          return (1);
      }
      else
        return (0);
    }
    return (0);
}

void  ft_update(t_shape **nearest_shape, t_shape *shapes, t_intersection_point	*nearest_intp, t_intersection_point	intp)
{
	*nearest_shape = shapes;
	*nearest_intp = intp;
}

int get_nearest_shape(t_rt *rt, const t_ray *ray, t_shape **out_shape, t_intersection_point *out_intp)
{
	ssize_t								i;
	t_shape								*nearest_shape;
	t_intersection_point	nearest_intp;
	int										res;
	t_intersection_point	intp;

	nearest_shape = NULL;
  nearest_intp.distance = DBL_MAX;//まずは一番大きく設定
	i = -1;
	while (++i < rt->scene.num_shapes)
	{
		res = intersection_test(&rt->scene.shapes[i], ray, &intp);
		if (res != 0 && intp.distance < nearest_intp.distance)
      ft_update(&nearest_shape, &rt->scene.shapes[i], &nearest_intp, intp);
			// if ( ray_type ) break;//ここだとshapes[0]が光源より遠いときに影がでなくなってしまう
	}
	if (nearest_shape != NULL)
	{
		if (out_shape != NULL && rt->flag != SHADOW)//shadow_rayの時はここでshapeの内容が書き換わるのを防ぐ
			*out_shape = nearest_shape;
		if (out_intp != NULL)
			*out_intp = nearest_intp;
		return (1);
	}
	else
		return (0);
}


void init_shape(t_shape* shape, t_shape_type st, ...)
{
  va_list args;
  va_start(args, st);

  shape->type = st;
  if ( st == ST_SPHERE )
    {
      t_sphere* sph = &shape->u_data.sphere;
      
      sph->center.x = va_arg(args, double);
      sph->center.y = va_arg(args, double);
      sph->center.z = va_arg(args, double);
      sph->radius   = va_arg(args, double);
    }
  else if ( st == ST_PLANE )
    {
      t_plane* plane = &shape->u_data.plane;
      
      plane->position.x = va_arg(args, double);
      plane->position.y = va_arg(args, double);
      plane->position.z = va_arg(args, double);

      plane->normal.x = va_arg(args, double);
      plane->normal.y = va_arg(args, double);
      plane->normal.z = va_arg(args, double);
    }
    else if (st == ST_CYLINDER)
    {
      t_cylinder *cylin = &shape->u_data.cylinder;

      cylin->position.x = va_arg(args, double);
      cylin->position.y = va_arg(args, double);
      cylin->position.z = va_arg(args, double);
      cylin->radius     = va_arg(args, double);
      cylin->height     = va_arg(args, double);
    }
  else
    {
      fprintf(stderr, "init_shape : unknown shape type.\n");
      abort();
    }
  
  va_end(args);
}









void init_material(t_material* mat,
		   double difR, double difG, double difB,
		   double shns)
{
  ft_set_color(&mat->diffuse_ref,  difR, difG, difB);
  mat->shininess = shns;
}

void init_light(t_light* light, double vx, double vy, double vz, double spe_r, double illR, double illG, double illB)
{
  light->vector = v_init(vx, vy, vz);
  light->specular_ref = spe_r;
  ft_convert_color_range(&light->illuminance, illR, illG, illB);
}

void init_ambient(t_ambient *ambient, double amb_r, double illR, double illG, double illB)
{
  ambient->ambient_ref = amb_r;
  ft_convert_color_range(&ambient->ambient_illuminance, illR, illG, illB);
}

void  init_camera(t_camera *camera, double vx, double vy, double vz, double nx, double ny, double nz, double fov)
{
  camera->camera_position = v_init(vx, vy, vz);
  camera->forward_dir = v_init(nx, ny, nz);
  camera->degree = fov;
}
