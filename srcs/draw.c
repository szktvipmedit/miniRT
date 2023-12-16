#include "../incs/minirt.h"

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

t_vector init_vector(float x, float y, float z)
{
    t_vector new;
    new.x = x;
    new.y = y;
    new.z = z;
    return new;
}

t_vector ft_add_vec(t_vector vec1, t_vector vec2)
{
    return init_vector(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}
t_vector ft_sub_vec(t_vector vec1, t_vector vec2)
{
    return init_vector(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}
t_vector ft_mult_vec(t_vector vec, float mult)
{
    return init_vector(vec.x * mult, vec.y * mult, vec.z * mult);
}
float ft_dot_vec(t_vector vec1, t_vector vec2)
{
    return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

float ft_get_magnitude_vec(t_vector vec)
{
    return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}

t_vector    ft_normalize_vec(t_vector primitive_vec)
{
    float vec_mag = ft_get_magnitude_vec(primitive_vec);
    return ft_mult_vec(primitive_vec, 1/vec_mag);
}

float get_t_surface_hit_light(float t1, float t2)
{
    if(t1 < 0 && t2 < 0)
        return 0;
    if(t1 > 0 && t2 > 0)
    {
        if(t1 < t2)
            return t1;
        return t2;
    }
    else if(t1 > 0 && t2 < 0)
        return t1;
    return t2;
}

t_vector calc_intersection_sight_and_sphere_vec(t_vector viewpoint, t_vector view_direct_vec, float A, float B, float C, float D)
{
    float t;
    t_vector intersection_sight_and_sphere_vec;
    if(D > 0)//交差点が２つある場合
    {
        float t1;
        float t2;
        t1 = ((-1 * B) - sqrt(D)) / (2 * A);
        t2 = ((-1 * B) + sqrt(D)) / (2 * A);
        t = get_t_surface_hit_light(t1, t2); //正かつ小さい方のtを採用
    }
    else
        t = ((-1 * B) - sqrt(D)) / (2 * A);
    return ft_add_vec(viewpoint, ft_mult_vec(view_direct_vec, t));
}

t_vector calc_sphere_normal_vec(t_vector pi, t_vector sphere_center_vec)
{
    float x,y,z;
    t_vector sphere_dir;
    sphere_dir = ft_sub_vec(ft_mult_vec(pi, 2), ft_mult_vec(sphere_center_vec, 2));
    sphere_dir = ft_normalize_vec(sphere_dir);
    return init_vector(sphere_dir.x, sphere_dir.y, sphere_dir.z);
}

float ft_constrain(double v, double vmin, double vmax) {
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
    t_vector    viewpoint;
    t_vector    screen;
    t_vector    sphere;
    t_vector    light;
    t_vector    light_incident_direction_vec;
    float r = 1;
    int color;
    viewpoint = init_vector(0, 0, -5);
    screen = init_vector(0, 0, 0);
    sphere = init_vector(0, 0, 5);
    light = init_vector(-5, 5, -5);
    int y = 0;
    int x = 0;
    while(y < HEIGHT)
    {
        screen.y = ((-2.0 * y) / (HEIGHT - 1)) + 1;
        x = 0;
        while(x < WIDTH)
        {
            screen.x = ((2.0 * x) / (WIDTH - 1)) - 1;
            t_vector view_direct_vec =  ft_sub_vec(screen, viewpoint);
            t_vector diff_vec = ft_sub_vec(viewpoint, sphere);

            float A = ft_dot_vec(view_direct_vec, view_direct_vec);
            float B = 2 * ft_dot_vec(diff_vec, view_direct_vec);
            float C = ft_dot_vec(diff_vec, diff_vec) - pow(r, 2);
            float D = pow(B, 2) - (4 * A * C);
            if(D < 0)
                color = 0x0000ff;
            else//交差している
            {
                t_vector    pi;
                t_vector    sphere_normal_vec;//球の表面上のある一点の法線ベクトル
                pi = calc_intersection_sight_and_sphere_vec(viewpoint, view_direct_vec, A, B, C, D);
                t_vector light_dir = ft_sub_vec(ft_mult_vec(light, 2), ft_mult_vec(pi, 2) );
                light_dir = ft_normalize_vec(light_dir);

                sphere_normal_vec = calc_sphere_normal_vec(pi, sphere);
                float diffuse_radience = ft_dot_vec(sphere_normal_vec, light_dir);
                diffuse_radience = ft_constrain(diffuse_radience, 0, 1);
                //diffuse_radienceが1に近いほど白く(255に近く)なる
                int shadow = (int)(diffuse_radience * 255);
                color = shadow << 16 | shadow << 8 | shadow ;
            }
            int i = (y * rt_info->size_line) + (x * (rt_info->bit_per_pixel / 8));
            rt_info->data_addr[i] = color;
            rt_info->data_addr[++i] = color >> 8;
            rt_info->data_addr[++i] = color >> 16;
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(rt_info->mlx_ptr, rt_info->win_ptr, rt_info->img_ptr, 0, 0);
}