#include "../incs/minirt.h"

static void	create_background_color(colorf_t *col)
{
	col->r = 100 / 255.0;
	col->g = 149 / 255.0;
	col->b = 237 / 255.0;
}

static void	create_eye_ray(t_rt *rt_info, ray_t *eye_ray, vector_t pw)
{
	eye_ray->start = rt_info->scene->viewpoint;
	eye_ray->direction.x = pw.x - rt_info->scene->viewpoint.x;
	eye_ray->direction.y = pw.y - rt_info->scene->viewpoint.y;
	eye_ray->direction.z = pw.z - rt_info->scene->viewpoint.z;
}

static void	prepare_raytracing(colorf_t *col, t_rt *rt_info, ray_t *eye_ray,
		vector_t pw)
{
	create_background_color(col);
	create_eye_ray(rt_info, eye_ray, pw);
}

static void	create_pixel(t_rt *rt_info, vector_t pw, int x, int y)
{
	ray_t		eye_ray;
	colorf_t	col;

	prepare_raytracing(&col, rt_info, &eye_ray, pw);
	raytrace(rt_info->scene, &eye_ray, &col);
	create_color(&col);
	store_pixel_addr(rt_info, col, x, y);
}

void	create_image(t_rt *rt_info)
{
	vector_t	pw; /*３次元空間を2次元に変換したスクリーン*/
	int			y;

	int x; /* スクリーン座標 */
	y = 0;
	x = 0;
	pw.z = 0; /* スクリーンのz座標は常にゼロ */
	while (y < HEIGHT)
	{
		pw.y = (-2.0f * y) / (HEIGHT - 1) + 1.0f;
		x = 0;
		while (x < WIDTH)
		{
			pw.x = (2.0f * x) / (WIDTH - 1) - 1.0f;
			create_pixel(rt_info, pw, x, y);
			x++;
		}
		y++;
	}
}
