#ifndef MINIRT_H
# define MINIRT_H

#include "../libft/libft.h"
#include "../minilibx_macos/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define WIDTH 1920
#define HEIGHT 1080

//keys--------------------------
# define ESC 53
# define PLUS 24
# define MINUS 27
# define ALLOW_TOP 126
# define ALLOW_RIGHT 124
# define ALLOW_BOTTOM 125
# define ALLOW_LEFT 123

//error messages---------------
#define ERROR_MALLOC "Error: malloc failed!\n"
#define ERROR_ARG_CNT "Error: The number of arguments is different\n"
#define ERROR_OPEN "Error: open failed!\n"
#define ERROR_EMPTY_FILE "Error: The file passed is empty!\n"
#define ERROR_USAGE "Error: Usage: ./miniRT {~~.rt}\n"

//structs-----------------------
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


//functions-----------------------
//draw.c
void draw(t_rt  *rt_info);

//error_messages.c
void    error_exit(char *error_message);

//init_rt_info.c
void	image_init(t_rt *rt_info);
void    rt_info_init(t_rt *rt_info);


void	read_info(t_rt *rt_info, char *filename);

#endif