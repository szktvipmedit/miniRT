#ifndef SCENE_H
# define SCENE_H

#include "../minilibx_macos/mlx.h"
#include "../libft/libft.h"
#include "raytracing.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define HEIGHT 512
#define WIDTH 512
//key--------------------------
# define ESC 53
# define PLUS 24
# define MINUS 27
# define ALLOW_TOP 126
# define ALLOW_RIGHT 124
# define ALLOW_BOTTOM 125
# define ALLOW_LEFT 123

#define ERROR_MALLOC "Error: malloc failed\n"

typedef struct s_rt
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*pixel_addr;
	int				size_line;
	int				bit_per_pixel; 
	int				endian;

    scene_t         *scene;
}               t_rt;


void    rt_info_init(t_rt *rt_info);
void	create_image(t_rt *rt_info);
void	store_pixel_addr(t_rt *rt_info, colorf_t col, int x, int y);
void	create_color(colorf_t *col);
void	image_init(t_rt *rt_info);
//error_messages
void	error_malloc(void);
#endif