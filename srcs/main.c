#include "../incs/minirt.h"
#include "../incs/raytracing.h"
#include "../incs/vector_utils.h"

static int	close_window(t_rt *rt_info)
{
	mlx_destroy_image(rt_info->mlx_ptr, rt_info->img_ptr);
	mlx_clear_window(rt_info->mlx_ptr, rt_info->win_ptr);
	mlx_destroy_window(rt_info->mlx_ptr, rt_info->win_ptr);
	exit(0);
	return (0);
}

static int	deal_key(int key, t_rt *rt_info)
{
	(void)key;
	if (rt_info == NULL)
		return (0);
	if (key == ESC)
		close_window(rt_info);
	mlx_destroy_image(rt_info->mlx_ptr, rt_info->img_ptr);
	mlx_clear_window(rt_info->mlx_ptr, rt_info->win_ptr);
	image_init(rt_info);
	create_image(rt_info);
	return (0);
}

int	main(void)
{
	t_rt rt_info;

	rt_info_init(&rt_info);
	scene_setting(rt_info.scene);
	create_image(&rt_info);
	mlx_put_image_to_window(rt_info.mlx_ptr, rt_info.win_ptr, rt_info.img_ptr,
		0, 0);
	mlx_key_hook(rt_info.win_ptr, deal_key, &rt_info);
	mlx_hook(rt_info.win_ptr, 17, 1L << 17, close_window, &rt_info);
	mlx_loop(rt_info.mlx_ptr);
	return (0);
}