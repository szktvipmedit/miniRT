#include "../incs/minirt.h"

void	image_init(t_rt *rt_info)
{
	rt_info->img_ptr = mlx_new_image(rt_info->mlx_ptr, WIDTH, HEIGHT);
	if (!rt_info->img_ptr)
		error_malloc();
	rt_info->data_addr = mlx_get_data_addr(rt_info->img_ptr,
			&rt_info->bit_per_pixel,
			&rt_info->size_line,
			&rt_info->endian);
	printf("rt_info->size_line = %i\n", rt_info->size_line);
	if (!rt_info->data_addr)
		error_malloc();
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
}


