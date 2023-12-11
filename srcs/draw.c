#include "../incs/minirt.h"

typedef struct	s_vec3 {
	double		x;
	double		y;
	double		z;
} t_vec3;

t_vec3	vec3_init(double x, double y, double z)
{
	t_vec3 new;
	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_mult(t_vec3 a, double b)
{
	return (vec3_init(a.x * b, a.y * b, a.z * b));//ここから上はJunさんのブログから引用
}

void draw(t_rt  *rt_info)
{
	int	x;
	int	y;
	int	color;
	t_vec3 camera_vec;
	camera_vec = vec3_init(0, 0, -5);

	t_vec3 sphere_vec;
	sphere_vec = vec3_init(0, 0, 5);
	double sphere_r = 1;

	t_vec3	pw = vec3_init(0, 0, 0);
	pw.z = 0;
	
	y = 0;
	while (y < HEIGHT)
	{
		pw.y = -2.0 * y / (HEIGHT-1) + 1;//二次元配列を(0, 0)を中心とした縦横2の正方形に置き換える
		x = 0;
		while (x < WIDTH)
		{
			pw.x = 2.0 * x / (WIDTH-1) -1;

			t_vec3	eye_dir = vec3_sub(pw, camera_vec);//視線方向ベクトル
			t_vec3	tmp = vec3_sub(camera_vec, sphere_vec);//視点 - 球の中心

			double a = vec3_dot(eye_dir, eye_dir);
			double b = 2.0 * vec3_dot(tmp, eye_dir);
			double c = vec3_dot(tmp, tmp) - sphere_r	* sphere_r;
			double d = b * b - 4 * a * c;//ベクトルの連立方程式の判別式𝐷=𝐵2−4𝐴𝐶

			if (d >= 0)//𝐷=0 のとき，レイは球とただ一つの交点を持つ, 𝐷>0 のとき，レイは球と二つの交点を持つ．
				color = 0xFF0000;//赤一色
			else
				color = 0x0000FF;//青一色
			// Minilibxの画素データへのアクセス
			int pixel_index = (x * (rt_info->bit_per_pixel / 8)) + (y * rt_info->size_line);
			unsigned int *pixel = (unsigned int *)(rt_info->data_addr + pixel_index);
			*pixel = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(rt_info->mlx_ptr, rt_info->win_ptr, rt_info->img_ptr, 0, 0);//ディスプレイに表示
}
