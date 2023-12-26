/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:52:36 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/26 13:05:34 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

int	ft_clean_up_and_exit_0(t_rt *rt)
{
	if (rt->img_ptr != NULL)
		mlx_destroy_image(rt->mlx_ptr, rt->img_ptr);
	if (rt->win_ptr != NULL)
		mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
	if (rt->win_ptr != NULL)
		mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
	exit(0);
	return (0);
}

int	ft_clean_up_and_exit_1(t_rt *rt)
{
	if (rt->img_ptr != NULL)
		mlx_destroy_image(rt->mlx_ptr, rt->img_ptr);
	if (rt->win_ptr != NULL)
		mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
	if (rt->win_ptr != NULL)
		mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
	exit(1);
	return (0);
}

void	error_exit(char *error_message)
{
	write(2, error_message, ft_strlen(error_message));
	exit(1);
}

void	init_read_cnt(t_read_cnt *read_cnt)
{
	read_cnt->ambient_cnt = 0;
	read_cnt->camera_cnt = 0;
	read_cnt->light_cnt = 0;
	read_cnt->line_num = 1;
}
