/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyasukaw <jyasukaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:52:08 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/22 15:32:32 by jyasukaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

static void	ft_init_rt(t_rt *rt)
{
	rt->mlx_ptr = mlx_init();
	if (rt->mlx_ptr == NULL)
		ft_clean_up_and_exit_1(rt);
	rt->win_ptr = mlx_new_window(rt->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	if (rt->win_ptr == NULL)
		ft_clean_up_and_exit_1(rt);
	rt->img_ptr = mlx_new_image(rt->mlx_ptr, WIDTH, HEIGHT);
	if (rt->img_ptr == NULL)
		ft_clean_up_and_exit_1(rt);
	rt->pixel_addr = mlx_get_data_addr(rt->img_ptr, &rt->bit_per_pixel,
			&rt->size_line, &rt->endian);
	if (rt->pixel_addr == NULL)
		ft_clean_up_and_exit_1(rt);
}

static int	ft_deal_key(int key_code, t_rt *rt)
{
	if (key_code == ESC)
		ft_clean_up_and_exit_0(rt);
	return (0);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q miniRT");
// }

int	main(int argc, char **argv)
{
	t_rt	rt;

	if (argc == 2)
	{
		ft_init_scene(argv[1], &rt.scene);
		ft_init_rt(&rt);
		ft_rendering(&rt);
		mlx_hook(rt.win_ptr, 2, 0, ft_deal_key, &rt);
		mlx_hook(rt.win_ptr, 17, 0, ft_clean_up_and_exit_0, &rt);
		mlx_loop(rt.mlx_ptr);
		exit(0);
	}
	else
		error_exit(ERROR_ARG_CNT);
}
