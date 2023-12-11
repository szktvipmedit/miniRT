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

	double li = 1.0;//光源の光の強度(light_intensity)
	double ai = 0.1;//環境光の強度(ambient_intensity)
	double ka = 0.01;//環境光反射係数(k_amb)
	double kd = 0.69;//拡散反射係数(k_dif)
	double ks = 0.3;//鏡面反射係数(k_spe)
	double shininess = 8;//光沢度
	
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
				double radince_amb = ka * ai;//環境光の反射光の放射輝度𝑅𝑎を計算する𝑅𝑎=𝑘𝑎x𝐼𝑎

				t_vec3	pi = vec3_add(camera_vec, vec3_mult(eye_dir, t));//交点位置𝐩i→=𝐩e→+𝑡𝐝e→
				t_vec3	light_dir = vec3_sub(light_vec, pi);//入射ベクトル
				light_dir = vec3_normalize(light_dir);//正規化が必要であることに注意せよ
				t_vec3	sphere_n = vec3_sub(pi, sphere_vec);//法線ベクトル(球の)
				sphere_n = vec3_normalize(sphere_n);//正規化が必要であることに注意せよ

				double nldot = constrain(vec3_dot(light_dir, sphere_n), 0, 1);//入射ベクトルと法線ベクトルの内積を計算し、0=< =<1に制限する

				double radince_dif = kd * li * nldot;//直接光の拡散反射光の放射輝度𝑅𝑑を計算する．𝑅𝑑=𝑘𝑑x𝐼𝑖(𝐧⃗ ⋅ℓ⃗ )
				double radince_spe = 0.0;//以下の条件に当てはまらない時の直接光の鏡面反射光の放射輝度𝑅𝑠はゼロとする．
				if (nldot > 0)
				{
					t_vec3	refdir = vec3_sub(vec3_mult(sphere_n, 2 * nldot), light_dir);//正反射ベクトル𝐫⃗ を計算する．𝐫⃗ =2(𝐧⃗ ⋅ℓ⃗ )𝐧⃗ −ℓ⃗
					t_vec3	inv_eye_dir = vec3_mult(eye_dir, -1);//視線ベクトルの逆ベクトル𝐯⃗ を計算する𝐯⃗ =−𝐝e→
					inv_eye_dir = vec3_normalize(inv_eye_dir);//正規化が必要であることに注意せよ
					
					double vrdot = constrain(vec3_dot(refdir, inv_eye_dir), 0, 1);//正反射ベクトルと視線ベクトルの逆ベクトルの内積を計算し制限

					radince_spe = ks * li * pow(vrdot, shininess);//直接光の鏡面反射光の放射輝度𝑅𝑠を計算する𝑅𝑠=𝑘𝑠𝐼𝑖(𝐯⃗ ⋅𝐫⃗ )𝛼
				}

				double radiance = constrain(radince_amb + radince_dif + radince_spe, 0, 1);//反射光の放射輝度𝑅𝑟を計算する𝑅𝑟=𝑅𝑎+𝑅𝑑+𝑅𝑠

				int gray = (int)(255 * radiance);//以下3行はchatGPT。まだよくわからない
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
