#ifndef RAYTRACING_H
#define RAYTRACING_H
#include "vector_utils.h"
#include <stdio.h>

#define SET_COLOR(col, r_, g_, b_) { col.r = r_; col.g = g_; col.b = b_; }
#define SET_VECTOR(vec, x_, y_, z_) { vec.x = x_; vec.y = y_; vec.z = z_; }
typedef struct
{
  float r,g,b;
} colorf_t;

typedef struct
{
  vector_t start;     /* 始点 */
  vector_t direction; /* 方向ベクトル */
} ray_t;

typedef struct
{
  vector_t center; /* 球の中心 */
  float radius;    /* 球の半径 */
} sphere_t;

typedef struct
{
  vector_t normal;   /* 法線ベクトル */
  vector_t position; /* 面が通る点の位置ベクトル */
} plane_t;

typedef enum
{
  MT_DEFAULT,/*通常の(完全鏡面反射を使用しない)質感*/
  MT_PERFECT_REF,/*完全鏡面反射を使用する質感*/
} material_type;

typedef struct
{
  colorf_t ambient_ref;   /* 環境光反射率(RGB) */
  colorf_t diffuse_ref;   /* 拡散反射率(RGB) */
  colorf_t specular_ref;  /* 鏡面反射率(RGB) */
  float shininess;       /* 光沢度 */

  material_type type;
  colorf_t reflect_ref; /*完全鏡面反射光係数を指定する*/
} material_t;

typedef enum
  {
    ST_SPHERE, /* 球 */
    ST_PLANE   /* 平面 */
  } shape_type;
typedef struct
{
  shape_type type;     /* 球 or 平面 */
  union
  {
    sphere_t sphere;   /* 球の情報 */
    plane_t plane;     /* 平面の情報 */
  } data;

  material_t material; /* 物体表面の質感 */
} shape_t;


typedef enum
  {
    LT_POINT,      /* 点光源 */
    LT_DIRECTIONAL/* 平行光源 */
  } light_type;
typedef struct
{
  light_type type;      /* 点光源 or 平行光源 */
  vector_t vector;      /* 光源位置 or 公選法光 */
  colorf_t illuminance; /* 照度(RGB) */
} light_t;

typedef struct
{
  vector_t viewpoint;           /* 視点位置 */
  colorf_t background_color;
  shape_t *shapes;              /* 物体リストへのポインタ */
  size_t num_shapes_capacity;   /* 物体リストの最大格納数 */
  size_t num_shapes;            /* 物体リストに実際に格納されている数 */
  light_t *lights;              /* 光源リストへのポインタ */
  size_t num_lights_capacity;   /* 光源リストの最大格納数 */
  size_t num_lights;            /* 光源リストに実際に格納されている数 */
  colorf_t ambient_illuminance; /* 環境光の強さ(RGB) */
} scene_t;


typedef struct
{
  float distance;      /* 交点までの距離 */
  vector_t position;   /* 交点の位置ベクトル */
  vector_t normal;     /* 交点における物体表面の法線ベクトル */
} intersection_point_t;

typedef struct
{
      int recursion_level; /* 完全鏡面反射の再帰回数保持*/
      intersection_point_t inter_p; //視線と物体の交点情報
      shape_t *shape;   /* intersectした物体の情報格納用 */
      vector_t light_dir; /*入射方向ベクトル*/
      ray_t     shadow_ray;
      colorf_t amb_rd; /* 環境光の輝度 */
      colorf_t dif_rd; /* 直接光の拡散反射輝度*/;
      colorf_t sep_rd; /* 直接光の鏡面反射輝度 */;
      colorf_t ref_rd; /* 完全反射輝度 */;
}     t_pixel_info;
int intersection_test(const shape_t *shape, const ray_t* ray, intersection_point_t* out_intp);
int get_nearest_shape(const scene_t* scene, const ray_t *ray, float max_dist, int exit_once_found,
                      shape_t **out_shape, intersection_point_t *out_intp);
#define MAX_RECURSION 8
int recursive_raytrace(const scene_t* scene, const ray_t *eye_ray, colorf_t *out_col, int recursion_level);
int raytrace(const scene_t* scene, const ray_t *eye_ray, colorf_t *out_col);

void scene_setting(scene_t *scene);
void init_shape(shape_t* shape, shape_type st, ...);
void init_material(material_t* mat,
		   float ambR, float ambG, float ambB,
		   float difR, float difG, float difB,
		   float speR, float speG, float speB,
		   float shns, material_type type,
       float refR, float refG, float refB);
void init_light(light_t* light, light_type lt,
		float vx, float vy, float vz,
		float illR, float illG, float illB);

#endif