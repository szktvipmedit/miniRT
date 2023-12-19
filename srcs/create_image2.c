#include "../incs/minirt.h"

void	store_pixel_addr(t_rt *rt_info, colorf_t col, int x, int y)
{
	int	i;

	i = (y * rt_info->size_line) + (x * (rt_info->bit_per_pixel / 8));
	rt_info->pixel_addr[i] = col.b;
	rt_info->pixel_addr[++i] = col.g;
	rt_info->pixel_addr[++i] = col.r;
}

void	create_color(colorf_t *col)
{
	col->r = 255 * CLAMP(col->r, 0, 1);
	col->g = 255 * CLAMP(col->g, 0, 1);
	col->b = 255 * CLAMP(col->b, 0, 1);
}
