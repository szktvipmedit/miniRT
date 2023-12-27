/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:17:47 by jyasukaw          #+#    #+#             */
/*   Updated: 2023/12/27 14:41:52 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <math.h>

# define HEIGHT 700
# define WIDTH 700

# define ESC 53

# define SHININESS 20.0
# define EPSILON 0.00195312
# define SHADOW -1

# define ERROR_MALLOC "Error: malloc failed!\n"
# define ERROR_ARG_CNT "Error: The number of arguments is different\n"
# define ERROR_OPEN "Error: open failed!\n"
# define ERROR_EMPTY_FILE "Error: The file passed is empty!\n"
# define ERROR_USAGE "Error: Usage: ./miniRT {~~.rt}\n"
# define NOTICE_MAX_OBJECTS "The maximum number of objects is INT_MAX\n"
# define ERROR_INFO_CNT "Please specify one information each for ambient_light,\
camera, and light\n"
# define ERROR_NORMAL "Cannot be displayed because the normal vector is [0, 0,\
0]\n"
typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct s_color3
{
	double			r;
	double			g;
	double			b;
}					t_color3;

typedef struct s_ray
{
	t_vec3			start;
	t_vec3			direction;
	t_vec3			x_dir;
	t_vec3			y_dir;
	t_vec3			pw;
}					t_ray;

typedef struct s_sphere
{
	t_vec3			center;
	double			radius;
}					t_sphere;

typedef struct s_plane
{
	t_vec3			position;
	t_vec3			normal;
}					t_plane;

typedef struct s_cylinder
{
	t_vec3			position;
	double			radius;
	double			height;
	t_vec3			normal;
}					t_cylinder;

typedef enum e_shape_type
{
	ST_SPHERE,
	ST_PLANE,
	ST_CYLINDER
}					t_shape_type;

typedef struct s_shape
{
	t_shape_type	type;

	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	} u_data;
	t_color3		diffuse_ref;
}					t_shape;

typedef struct s_light
{
	t_vec3			vector;
	double			specular_ref;
	t_color3		illuminance;
}					t_light;

typedef struct s_ambient
{
	double			ambient_ref;
	t_color3		amb_illuminance;
}					t_ambient;

typedef struct s_camera
{
	t_vec3			camera_position;
	t_vec3			forward_dir;
	double			degree;
}					t_camera;

typedef struct s_read_cnt
{
	int				light_cnt;
	int				ambient_cnt;
	int				camera_cnt;
	int				line_num;
}					t_read_cnt;

typedef struct s_intersection_point
{
	t_vec3			position;
	t_vec3			normal;
	double			distance;
}					t_intersection_point;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_shape			*shapes;
	ssize_t			num_shapes;
}					t_scene;

typedef struct s_rt
{
	t_scene			scene;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*pixel_addr;
	int				bit_per_pixel;
	int				size_line;
	int				endian;
	t_ray			ray;
	t_color3		color;
	int				pixel_index;
	unsigned int	*pixel;
	int				flag;
	t_ray			shadow_ray;

}					t_rt;

typedef struct s_cy
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			t_outer;
	double			t_inner;
	t_vec3			p_outer;
	t_vec3			p_inner;
	t_vec3			center_2p_outer;
	t_vec3			center_2p_inner;
	double			height_outer;
	double			height_inner;
}					t_cy;

// minirt_utils.c
int					ft_clean_up_and_exit_0(t_rt *rt);
int					ft_clean_up_and_exit_1(t_rt *rt);

// init_scene.c
void				ft_init_scene(char *file, t_scene *scene);

// rendering.c
void				ft_rendering(t_rt *rt);

// raytrace.c
void				ft_raytrace(t_rt *rt);

// get_nearest_shape.c
int					ft_get_nearest_shape(t_rt *rt, t_ray *ray,
						t_shape **out_shape, t_intersection_point *out_intp);

// intersection_test_utils.c
void				ft_calculate_sphere_t(t_sphere *sph, t_ray *ray,
						t_vec3 pe_pc, double *t);
int					ft_test_sphere(t_shape *shape, t_ray *ray,
						t_intersection_point *out_intp);
int					ft_test_plane(t_shape *shape, t_ray *ray,
						t_intersection_point *out_intp);
int					ft_set_cy_info(t_cy *cy, t_cylinder *cylin, t_ray *ray);
int					ft_test_cylinder(t_shape *shape, t_ray *ray,
						t_intersection_point *out_intp);

// vec3_utils_1.c
double				square(double x);
double				min(double a, double b);
double				max(double a, double b);
double				constrain(double v, double vmin, double vmax);

// vec3_utils_2.c
t_vec3				v_init(double x, double y, double z);
t_vec3				v_add(t_vec3 a, t_vec3 b);
t_vec3				v_sub(t_vec3 a, t_vec3 b);
t_vec3				v_mult(t_vec3 a, double b);

// vec3_utils_3.c
double				v_dot(t_vec3 a, t_vec3 b);
t_vec3				v_cross(t_vec3 a, t_vec3 b);
double				v_norm(t_vec3 v);
t_vec3				v_normalize(t_vec3 v);

void				error_exit(char *error_message);
int					ft_syntax_check_double_value(char *str);
void				ft_split_array_all_free(char **str);

size_t				count_info_in_line(char **info);
void				check_info_count(char **info, size_t need_info_count,
						int line_num);
double				check_range_value(double val, double range_min,
						double range_max, int line_num);
double				create_double_value(char *str, int line_num);

void				store_normalized_values(t_vec3 *vec, char *info,
						int line_num);
void				store_coordinate_values(t_vec3 *vec, char *info,
						int line_num);
void				store_rgb_values(t_color3 *col, char *info, int line_num);

void				read_light_info(t_scene *scene, char **info, int line_num,
						t_read_cnt *read_cnt);
void				read_camera_info(t_scene *scene, char **info, int line_num,
						t_read_cnt *read_cnt);
void				read_ambient_light_info(t_scene *scene, char **info,
						int line_num, t_read_cnt *read_cnt);
void				read_sphere_info(t_scene *scene, char **info, int line_num,
						int *store_shape_num);
void				read_plane_info(t_scene *scene, char **info, int line_num,
						int *store_shape_num);
void				read_cylinder_info(t_scene *scene, char **info,
						int line_num, int *store_shape_num);
int					count_num_shapes(char *file);
void				read_info(t_scene *scene, char *filename,
						t_read_cnt *read_cnt);
double				ft_atod(char *str);
void				normalize_color(t_color3 *col);
int					is_all_spaces(char *str);

void	store_cylinder_info_out(t_intersection_point *out_intp,
								t_cy *cy,
								t_cylinder *cylin);

void	store_cylinder_info_in(t_intersection_point *out_intp,
							t_cy *cy,
							t_cylinder *cylin);
void				init_read_cnt(t_read_cnt *read_cnt);

#endif