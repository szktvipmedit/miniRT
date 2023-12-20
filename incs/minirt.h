#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <float.h>

# define HEIGHT 512
# define WIDTH 512

# define ESC 53

# define SHININESS 20.0//光沢度
# define EPSILON (1.0/512)
# define SHADOW -1

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct	s_color3
{
	double	r;
	double	g;
	double	b;
}	t_color3;

typedef struct	s_ray
{
	t_vec3	start;			//始点
	t_vec3	direction;	//方向ベクトル

	//上記２つを求めるために必要。norm制限のためここで宣言
	t_vec3	x_dir;			//基底ベクトルx
	t_vec3	y_dir;			//基底ベクトルy
}	t_ray;

typedef struct	s_sphere
{
	t_vec3	center;	//球の中心
	double	radius;	//球の半径
}	t_sphere;

typedef struct	s_plane
{
	t_vec3	position;	//平面が通る点の位置ベクトル
	t_vec3	normal;		//法線ベクトル
}	t_plane;

typedef struct	s_cylinder
{
	t_vec3	position;	//円筒の底円の中心位置
	double	radius;		//半径
	double	height;		//高さ
	t_vec3	normal;		//法線ベクトル
}	t_cylinder;

typedef enum	e_shape_type
{
	ST_SPHERE,	//球 (ST_はshape_typeの略)
	ST_PLANE,		//平面
	ST_CYLINDER	//円筒
}	t_shape_type;

typedef struct	s_shape
{
	t_shape_type	type;	//(球 or 平面 or 円筒)

	union
	{
		t_sphere		sphere;		//球の情報
		t_plane			plane;		//平面の情報
		t_cylinder	cylinder;	//円筒の情報
	}	u_data;

	t_color3	diffuse_ref;	//拡散反射率(RGB)
}	t_shape;

typedef struct	s_light
{
	t_vec3		vector;				//光源位置
	double		specular_ref;	//鏡面反射率
	t_color3	illuminance;	//照度(RGB)
}	t_light;

typedef struct	s_ambient
{
	double		ambient_ref;					//環境光反射率
	t_color3	ambient_illuminance;	//環境光の強さ(RGB)
}	t_ambient;

typedef struct	s_camera
{
	t_vec3	camera_position;	//カメラ位置
	t_vec3	forward_dir;			//カメラの向き
	double	degree;						//カメラの視野角
}	t_camera;

typedef struct	s_intersection_point
{
	t_vec3	position;	//交点の位置ベクトル
	t_vec3	normal;		//交点における物体表面の法線ベクトル
	double	distance;	//交点までの距離
} t_intersection_point;

typedef struct	s_scene
{
	t_ambient	ambient;		//環境光情報
	t_camera	camera;			//カメラ情報
	t_light		light;			//光源情報
  t_shape		*shapes;		//物体リストへのポインタ
  ssize_t		num_shapes;	//物体リストに実際に格納されている数
}	t_scene;

typedef struct	s_rt
{
	//	init_scene
	t_scene				scene;

	//	init_rt
	void  				*mlx_ptr;
	void					*win_ptr;
	void					*img_ptr;
	char					*pixel_addr;
	int						bit_per_pixel; 
  int						size_line;
	int						endian;

	//	rendering
	t_ray					ray;
	t_color3			color;
	int						pixel_index;
	unsigned int	*pixel;

	// raytrace
	int						flag;
	t_ray					shadow_ray;

} t_rt;


// minirt_utils.c
int	ft_clean_up_and_exit(t_rt *rt);

// rendering.c
void ft_rendering(t_rt *rt);
double dot(const t_vec3* a, const t_vec3* b);

// init_scene.c
void	ft_init_scene(char *file, t_scene *scene);




int intersection_test(const t_shape *shape, const t_ray* ray, t_intersection_point* out_intp);
int get_nearest_shape(t_rt *rt, const t_ray *ray, t_shape **out_shape, t_intersection_point *out_intp);

void	ft_raytrace(t_rt *rt);
void init_shape(t_shape* shape, t_shape_type st, ...);
void init_light(t_light* light, double vx, double vy, double vz, double spe_r, double illR, double illG, double illB);
void init_ambient(t_ambient *ambient, double amb_r, double illR, double illG, double illB);
void  init_camera(t_camera *camera, double vx, double vy, double vz, double nx, double ny, double nz, double fov);

double v_norm(t_vec3 v);
t_vec3 v_normalize(t_vec3 v);

void ft_convert_color_range(t_color3 *color, int red, int green, int blue);
double square(double x);
double min(double a, double b);
double max(double a, double b);
double constrain(double v, double vmin, double vmax);

t_color3	ft_init_color3(double r, double g, double b);

t_vec3	v_init(double x, double y, double z);
t_vec3	v_add(t_vec3 a, t_vec3 b);
t_vec3	v_sub(t_vec3 a, t_vec3 b);
t_vec3	v_mult(t_vec3 a, double b);
t_vec3	v_cross(t_vec3 a, t_vec3 b);
double	v_dot(t_vec3 a, t_vec3 b);

#endif