#include "../../incs/raytracing.h"

void	set_color(colorf_t *col, float r, float g, float b)
{
	col->r = r;
	col->g = g;
	col->b = b;
}

void	init_color(t_pixel_info *pixel_info)
{
	set_color(&pixel_info->dif_rd, 0, 0, 0);
	set_color(&pixel_info->sep_rd, 0, 0, 0);
	set_color(&pixel_info->ref_rd, 0, 0, 0);
}
