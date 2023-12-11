#include "../incs/minirt.h"

t_vec3	vec3_init(double x, double y, double z)
{
	t_vec3 new;
	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

//内積
double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_mult(t_vec3 a, double b)
{
	return (vec3_init(a.x * b, a.y * b, a.z * b));
}

// ベクトルのノルム(長さ)
double	vec3_mag(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

// ベクトルの正規化
t_vec3	vec3_normalize(t_vec3 a)
{
	double mag = vec3_mag(a);
	return (vec3_init(a.x / mag, a.y / mag, a.z / mag));
}

// 最小値を返す関数
double min(double a, double b) {
    return (a < b) ? a : b;
}
// 最大値を返す関数
double max(double a, double b) {
    return (a > b) ? a : b;
}
//constrain 関数をC言語で実装した例
double constrain(double v, double vmin, double vmax) {
    if (v < vmin) {
        return vmin;
    } else if (v > vmax) {
        return vmax;
    } else {
        return v;
    }
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

	t_vec3 light_vec;
	light_vec = vec3_init(-5, 5, -5);//光源位置

	t_vec3	pw = vec3_init(0, 0, 0);
	pw.z = 0;
	
	y = 0;
	while (y < HEIGHT)
	{
		pw.y = -2.0 * y / (HEIGHT-1) + 1;
		x = 0;
		while (x < WIDTH)
		{
			pw.x = 2.0 * x / (WIDTH-1) -1;

			t_vec3	eye_dir = vec3_sub(pw, camera_vec);
			t_vec3	tmp = vec3_sub(camera_vec, sphere_vec);

			double a = vec3_dot(eye_dir, eye_dir);
			double b = 2.0 * vec3_dot(tmp, eye_dir);
			double c = vec3_dot(tmp, tmp) - sphere_r	* sphere_r;
			double d = b * b - 4 * a * c;

			double t = -1;//とりあえず0より小さい値で初期化？

			if (d == 0)
				t = -b / (2 * a);
			else if (d > 0)
			{
				double t1 = (-b - sqrt(d)) / (2 * a);
				double t2 = (-b + sqrt(d)) / (2 * a);

				t = t1 > 0 && t2 > 0 ? min(t1, t2) : max(t1, t2);
			}

			color = 0x6495ED;//𝑅𝐺𝐵=(100,149,237)水色の背景色と同義

			if (t > 0)
			{
				t_vec3	pi = vec3_add(camera_vec, vec3_mult(eye_dir, t));//交点位置𝐩i→=𝐩e→+𝑡𝐝e→
				t_vec3	light_dir = vec3_sub(light_vec, pi);//入射ベクトル
				light_dir = vec3_normalize(light_dir);//正規化が必要であることに注意せよ
				t_vec3	sphere_n = vec3_sub(pi, sphere_vec);//法線ベクトル(球の)
				sphere_n = vec3_normalize(sphere_n);//正規化が必要であることに注意せよ

				double nldot = constrain(vec3_dot(light_dir, sphere_n), 0, 1);//入射ベクトルと法線ベクトルの内積を計算し、0=< =<1に制限する

				int gray = (int)(255 * nldot);//以下3行はchatGPT。まだよくわからない
				gray = constrain(gray, 0, 255);
				color = (gray << 16) | (gray << 8) | gray;
			}

			int pixel_index = (x * (rt_info->bit_per_pixel / 8)) + (y * rt_info->size_line);
			unsigned int *pixel = (unsigned int *)(rt_info->data_addr + pixel_index);
			*pixel = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(rt_info->mlx_ptr, rt_info->win_ptr, rt_info->img_ptr, 0, 0);
}
