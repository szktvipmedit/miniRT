#include "../incs/minirt.h"

void ft_convert_color_range(t_color3 *color, int red, int green, int blue)
{
    color->r = (double)red / 255.0;
    color->g = (double)green / 255.0;
    color->b = (double)blue / 255.0;
}

double square(double x)
{
    return x * x;
}

// 最小値を返す関数
double min(double a, double b)
{
    if (a < b)
        return a;
    else
        return b;
}
// 最大値を返す関数
double max(double a, double b)
{
    if (a > b)
        return a;
    else
        return b;
}
//constrain 関数をC言語で実装した例
double constrain(double v, double vmin, double vmax)
{
    if (v < vmin)
        return vmin;
    else if (v > vmax)
        return vmax;
    else
        return v;
}

double dot(const t_vec3* a, const t_vec3* b)
{
  return a->x * b->x + a->y * b->y + a->z * b->z;
}

// ベクトルのノルム(長さ)
double	v_norm(t_vec3 v)
{
  return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

// ベクトルの正規化
t_vec3	v_normalize(t_vec3 v)
{
	double norm;

	norm = v_norm(v);
	v.x = v.x / norm;
	v.y = v.y / norm;
	v.z = v.z / norm;
	return (v_init(v.x, v.y, v.z));
}

t_color3	ft_init_color3(double r, double g, double b)
{
	t_color3 new;
	new.r = r;
	new.g = g;
	new.b = b;
	return (new);
}

t_vec3	v_init(double x, double y, double z)
{
	t_vec3 new;
	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3	v_add(t_vec3 a, t_vec3 b)
{
	return (v_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	v_sub(t_vec3 a, t_vec3 b)
{
	return (v_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	v_mult(t_vec3 a, double b)
{
	return (v_init(a.x * b, a.y * b, a.z * b));
}

double	v_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// ベクトルの外積
t_vec3	v_cross(t_vec3 a, t_vec3 b)
{
	return (v_init(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x));
}
