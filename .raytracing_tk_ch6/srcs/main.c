#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "../incs/vector_utils.h"
#include "../incs/raytracing.h"
#include <unistd.h>

#define WIDTH 512
#define HEIGHT 512

void scene_setting(scene_t *scene); /* forward */
void	error_malloc(void)
{
	write(2, "Error\n", 6);
	exit(1);
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
static  int	close_window(t_rt *rt_info)
{
	mlx_destroy_image(rt_info->mlx_ptr, rt_info->img_ptr);
	mlx_clear_window(rt_info->mlx_ptr, rt_info->win_ptr);
	mlx_destroy_window(rt_info->mlx_ptr, rt_info->win_ptr);
	exit(0);
	return (0);
}

static int	deal_key(int key, t_rt *rt_info)
{
	if (rt_info == NULL)
		return (0);
	// if (key == ESC)
	// 	close_window(rt_info);
	// mlx_destroy_image(rt_info->mlx_ptr, rt_info->img_ptr);
	// mlx_clear_window(rt_info->mlx_ptr, rt_info->win_ptr);
	// image_init(rt_info);
	// draw(rt_info);
	return (0);
}

int main()
{
  t_rt rt_info;
  rt_info_init(&rt_info);
  int y,x;                            /* スクリーン座標 */
  unsigned char r,g,b;                /* 画素値(RGB) */
  scene_t scene;
  vector_t eye_pos    = { 0, 0, -5 }; /* 視点位置 */
  vector_t pw;                        /* 三次元空間でのスクリーン座標 */

  scene_setting(&scene);
  
  printf("P3\n");
  printf("%d %d\n", WIDTH, HEIGHT);
  printf("255\n");

  pw.z = 0; /* スクリーンのz座標は常にゼロ */
  
  for(y = 0; y < HEIGHT; ++y)
    {
      pw.y = (-2.0f * y)/(HEIGHT-1) + 1.0f;
      for(x = 0; x < WIDTH; ++x)
        {
          ray_t eye_ray;
          colorf_t col = {100/255.0, 149/255.0, 237/255.0};
          
          pw.x = (2.0f * x)/(WIDTH-1 ) - 1.0f;

          eye_ray.start = eye_pos;
          eye_ray.direction.x = pw.x - eye_pos.x;
          eye_ray.direction.y = pw.y - eye_pos.y;
          eye_ray.direction.z = pw.z - eye_pos.z;

          raytrace(&scene, &eye_ray, &col);

          r = 255 * CLAMP(col.r, 0, 1);
          g = 255 * CLAMP(col.g, 0, 1);
          b = 255 * CLAMP(col.b, 0, 1);

          printf("%d %d %d\n", r, g, b);
          int i = (y * rt_info.size_line) + (x * (rt_info.bit_per_pixel / 8));
          rt_info.data_addr[i] = b;
          rt_info.data_addr[++i] = g;
          rt_info.data_addr[++i] = r;
        }/* for */
    }/* for */
 mlx_put_image_to_window(rt_info.mlx_ptr, rt_info.win_ptr, rt_info.img_ptr, 0, 0); 
  free(scene.lights);
  free(scene.shapes);
  mlx_key_hook(rt_info.win_ptr, deal_key, &rt_info);
    mlx_hook(rt_info.win_ptr, 17, 1L << 17, close_window, &rt_info);
    mlx_loop(rt_info.mlx_ptr);
  return 0;
  
}/* int main() */
