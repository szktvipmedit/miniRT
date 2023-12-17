#ifndef MINIRT_H
# define MINIRT_H

#include "../libft/libft.h"
#include "../minilibx_macos/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define WIDTH 512
#define HEIGHT 512

//key--------------------------
# define ESC 53
# define PLUS 24
# define MINUS 27
# define ALLOW_TOP 126
# define ALLOW_RIGHT 124
# define ALLOW_BOTTOM 125
# define ALLOW_LEFT 123

//error messages---------------
#define ERROR_MALLOC "Error: malloc failed!\n"


typedef struct s_rt
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*data_addr;
	int				size_line;
	int				bit_per_pixel; 
	int				endian;
}               t_rt;

typedef struct s_color
{
    double  r;
    double  g;
    double  b;
}           t_color;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_ray
{
    t_vector start;
    t_vector direction;
}           t_ray;

typedef struct s_sphere
{
    t_vector center;
    double radius;
}           t_sphere;

typedef struct s_plane
{
    t_vector normal;
    t_vector position;
}               t_plane;

typedef struct s_material
{
    t_color    ambient_ref;
    t_color     diffuse_ref;
    t_color     specular_ref;
    double      shininess;
}           t_material;
#define SPHERE 0;
#define PLANE 1;
typedef struct s_shape
{
    ssize_t shape_type;
    t_sphere *sphere;
    t_plane *plane;

    t_material material;
}           t_shape;


#define LT_POINT 0;
#define LT_DIRECTIONAL 1; 
typedef struct s_light
{
    ssize_t type;
    t_vector    vector;
    t_color     illuminance;
}           t_light;

typedef struct s_scene
{
    t_shape *shapes;
    size_t  num_shapes_capacity;
    size_t num_shapes;
    t_light *lights;
    size_t num_lights_capacity;
    size_t num_lights;
    t_color ambient_illuminance;
}               t_scene;

typedef struct s_intersection_point
{
    double distance;
    t_vector position;
    t_vector normal;
}               t_intersection_point;

//draw.c
void draw(t_rt  *rt_info);

//error_messages.c
void	error_malloc(void);

//init_rt_info.c
void	image_init(t_rt *rt_info);
void    rt_info_init(t_rt *rt_info);



#endif