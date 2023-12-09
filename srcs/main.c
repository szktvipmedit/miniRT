
#include "../incs/minirt.h"

void	error_malloc(void)
{
	write(2, ERROR_MALLOC, ft_strlen(ERROR_MALLOC));
	exit(1);
}
int	close_window(t_rt *rt_info)
{
	mlx_destroy_image(rt_info->mlx_ptr, rt_info->img_ptr);
	mlx_clear_window(rt_info->mlx_ptr, rt_info->win_ptr);
	mlx_destroy_window(rt_info->mlx_ptr, rt_info->win_ptr);
	exit(0);
	return (0);
}

void	image_init(t_rt *rt_info)
{
	rt_info->img_ptr = mlx_new_image(rt_info->mlx_ptr, WIDTH, HEIGHT);
	if (!rt_info->img_ptr)
		error_malloc();
	rt_info->data_addr = mlx_get_data_addr(rt_info->img_ptr,
			&rt_info->bit_per_pixel,
			&rt_info->size_line,
			&rt_info->endian);
	if (!rt_info->data_addr)
		error_malloc();
}

int	deal_key(int key, t_rt *rt_info)
{
	if (rt_info == NULL)
		return (0);
	// if (key == PLUS || key == MINUS)
	// 	zoom_map(rt_info, key);
	// if (key == ALLOW_TOP || key == ALLOW_RIGHT || key == ALLOW_BOTTOM
	// 	|| key == ALLOW_LEFT)
	// 	shift_map(rt_info, key);
	if (key == ESC)
		close_window(rt_info);
	mlx_destroy_image(rt_info->mlx_ptr, rt_info->img_ptr);
	mlx_clear_window(rt_info->mlx_ptr, rt_info->win_ptr);
	image_init(rt_info);
	draw(rt_info);
	return (0);
}

void    rt_info_init(t_rt *rt_info)
{
    rt_info->mlx_ptr = mlx_init();
	if (!rt_info->mlx_ptr)
		error_malloc();
	rt_info->win_ptr = mlx_new_window(rt_info->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	if (!rt_info->win_ptr)
		error_malloc();
	image_init(rt_info);
    mlx_key_hook(rt_info->win_ptr, deal_key, rt_info);
    mlx_hook(rt_info->win_ptr, 17, 1L << 17, close_window, rt_info);
    mlx_loop(rt_info->mlx_ptr);
}



int main(int argc, char **argv)
{
    t_rt    *rt_info;
    rt_info = (t_rt *)malloc(sizeof(t_rt));
    (void)argc;
    (void)argv;
    rt_info_init(rt_info);
    draw(rt_info);
    mlx_key_hook(rt_info->win_ptr, deal_key, rt_info);
    mlx_hook(rt_info->win_ptr, 17, 1L << 17, close_window, rt_info);
    mlx_loop(rt_info->mlx_ptr);
}
