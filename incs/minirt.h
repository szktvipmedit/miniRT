#ifndef MINIRT_H
# define MINIRT_H

#include "../libft/libft.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define WIDTH 1920
#define HEIGHT 1080

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
    int				**z_values;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*data_addr;
	int				size_line;
	int				bit_per_pixel;
	int				endian;
}               t_rt;




void draw(t_rt  *rt_info);
#endif