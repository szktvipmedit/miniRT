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
#define SQR(x) ((x)*(x))
#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)
#define CLAMP(v,minv,maxv) MIN(MAX(v,minv),maxv)
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

//draw.c
void draw(t_rt  *rt_info);

//error_messages.c
void	error_malloc(void);

//init_rt_info.c
void	image_init(t_rt *rt_info);
void    rt_info_init(t_rt *rt_info);



#endif