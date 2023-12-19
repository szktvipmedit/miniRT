#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdarg.h>
#include <stdio.h>
#include "../incs/raytracing.h"


#define EPSILON 1.0/512

void	calc_perfect_refrect_radience(scene_t *scene, ray_t *eye_ray, intersection_point_t *inter_p, t_pixel_info *t_pixel_info)
{
    vector_t r_eye_ray = ft_mult_vec(eye_ray->direction, -1);
    normalize(&r_eye_ray);
    float vndot = dot(&r_eye_ray, &inter_p->normal);
    if(vndot > 0)
    {
        vector_t ref_eye_dir = ft_sub_vec(ft_mult_vec(inter_p->normal, 2 * vndot), r_eye_ray);
        ray_t ref_ray;
        ref_ray.start = ft_add_vec(inter_p->position, ft_mult_vec(ref_eye_dir, EPSILON));
        ref_ray.direction = ref_eye_dir;
        recursive_raytrace(scene, &ref_ray, &ref_rd,recursion_level + 1);
        ref_rd.r = ft_constrain(vndot, 0, 1) * shapes->material.reflect_ref.r * ref_rd.r; 
        ref_rd.g = ft_constrain(vndot, 0, 1) * shapes->material.reflect_ref.g * ref_rd.g; 
        ref_rd.b = ft_constrain(vndot, 0, 1) * shapes->material.reflect_ref.b * ref_rd.b; 
    }
}

int recursive_raytrace(const scene_t* scene, const ray_t *eye_ray, colorf_t *out_col, int recursion_level)
{
    if(recursion_level > MAX_RECURSION)
    {
      return 0;
    }
    else
    {
        t_pixel_info pixel_info;
      intersection_point_t inter_p;
      shape_t *shapes;
      shapes = malloc(sizeof(shape_t));
      colorf_t amb_rd = {shapes->material.ambient_ref.r * scene->ambient_illuminance.r,shapes->material.ambient_ref.g * scene->ambient_illuminance.g,shapes->material.ambient_ref.b * scene->ambient_illuminance.b};
      colorf_t dif_rd = {0, 0, 0};
      colorf_t sep_rd = {0, 0, 0};
      colorf_t ref_rd = {0, 0, 0};
      if(get_nearest_shape(scene, eye_ray, FLT_MAX, 0, &shapes, &inter_p))//視線と物体の交点を見つける
      {
        vector_t light = scene->lights->vector;
        vector_t light_dir = ft_sub_vec(light, inter_p.position);
        //入射ベクトルが決定した時点で影の計算に入る     
        float dist_intp_light = norm(&light_dir);//{視線と物体の交点}と{light}の距離は正規化前の入射ベクトルと同じ
        normalize(&light_dir);
        ray_t shadow_ray;
        shadow_ray.start = ft_add_vec(inter_p.position, ft_mult_vec(light_dir, e));
        shadow_ray.direction = light_dir;
        if(shapes->material.type == MT_PERFECT_REF)//shapeが完全鏡面反射するならば
        {
            
        }
        if(!get_nearest_shape(scene, &shadow_ray, dist_intp_light, 1, &shapes, &inter_p))//視点と物体の交点から光源の間に物体がないため直接光が来る
        {
            float nldot = dot(&inter_p.normal, &light_dir);
            dif_rd.r = ft_constrain(nldot, 0, 1) * shapes->material.diffuse_ref.r * scene->lights->illuminance.r;
            dif_rd.g = ft_constrain(nldot, 0, 1) * shapes->material.diffuse_ref.g * scene->lights->illuminance.g;
            dif_rd.b = ft_constrain(nldot, 0, 1) * shapes->material.diffuse_ref.b * scene->lights->illuminance.b;

            if(nldot > 0)
            {
              vector_t r_eye_ray;
              r_eye_ray = ft_mult_vec(eye_ray->direction, -1);
              normalize(&r_eye_ray);
              vector_t ref_vec = ft_sub_vec(ft_mult_vec(inter_p.normal, (nldot * 2)), light_dir);
              float vrdot = dot(&r_eye_ray, &ref_vec);
              sep_rd.r = pow(ft_constrain(vrdot, 0, 1), shapes->material.shininess) * shapes->material.specular_ref.r * scene->lights->illuminance.r;
              sep_rd.g = pow(ft_constrain(vrdot, 0, 1), shapes->material.shininess) * shapes->material.specular_ref.g * scene->lights->illuminance.g;
              sep_rd.b = pow(ft_constrain(vrdot, 0, 1), shapes->material.shininess) * shapes->material.specular_ref.b * scene->lights->illuminance.b;
            }
        }

        out_col->r = ft_constrain(amb_rd.r + dif_rd.r + sep_rd.r + ref_rd.r, 0, 1);
        out_col->g = ft_constrain(amb_rd.g + dif_rd.g + sep_rd.g + ref_rd.g, 0, 1);
        out_col->b = ft_constrain(amb_rd.b + dif_rd.b + sep_rd.b + ref_rd.b, 0, 1);
      }

    }
    return 0;
}/* int raytrace(const scene_t* scene, const ray_t *eye_ray, colorf_t *out_col) */

int raytrace(const scene_t* scene, const ray_t *eye_ray, colorf_t *out_col)
{
  return recursive_raytrace(scene, eye_ray, out_col, 0);
}

int intersection_test(const shape_t *shape, const ray_t* ray, 
                      intersection_point_t* out_intp)
{
  if ( shape->type == ST_SPHERE )
    {
      const sphere_t *sph = &shape->data.sphere;
      vector_t pe_pc;
      float A,B,C,D;
      float t;
      
      pe_pc.x = ray->start.x - sph->center.x;
      pe_pc.y = ray->start.y - sph->center.y;
      pe_pc.z = ray->start.z - sph->center.z;

      A = dot(&ray->direction, &ray->direction);
      B = 2 * dot(&ray->direction, &pe_pc);
      C = dot(&pe_pc, &pe_pc) - SQR(sph->radius);

      D = SQR(B) - 4*A*C;

      t = -1.0f;
      if ( D == 0 )
        {
          t = -B / (2*A);
        }
      else if ( D > 0 )
        {
          float t1 = (-B + sqrt(D))/(2*A);
          float t2 = (-B - sqrt(D))/(2*A);

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
              normalize(&out_intp->normal);
            }

          return 1;
        }
      else
        {
          return 0;
        }
    }
  else if ( shape->type == ST_PLANE )
    {
      const plane_t *pln = &shape->data.plane;
      float dn_dot = dot(&ray->direction, &pln->normal);

      if ( dn_dot != 0 )
        {
          vector_t s_p;
          float t;
          
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

                  out_intp->normal = pln->normal;
                }

              return 1;
            }
          else
            {
              return 0;
            }
        }
    }
  return 0;
}/* int intersection_test(const shape_t *shape, const ray_t* ray,  */

int get_nearest_shape(const scene_t* scene, const ray_t *ray, float max_dist, int exit_once_found,
                      shape_t **out_shape, intersection_point_t *out_intp)
{
  size_t i;
  shape_t *nearest_shape = NULL;
  intersection_point_t nearest_intp;
  nearest_intp.distance =FLT_MAX; 
  nearest_intp.distance = max_dist;

  for(i = 0; i < scene->num_shapes; ++i)
    {
      int res;
      intersection_point_t intp;
      
      res = intersection_test(&scene->shapes[i], ray, &intp);
      if ( res && intp.distance < nearest_intp.distance )
        {
          nearest_shape = &scene->shapes[i];
          nearest_intp = intp;
          if ( exit_once_found ) break;
        }
    }/* for */

  if ( nearest_shape )
    {
      if ( out_shape )
        *out_shape = nearest_shape;
      if ( out_intp )
        *out_intp = nearest_intp;
      return 1;
    }
  else
    {
      return 0;
    }
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