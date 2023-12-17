#include "../incs/minirt.h"

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

t_vector init_vector(double x, double y, double z)
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
t_vector ft_mult_vec(t_vector vec, double mult)
{
    return init_vector(vec.x * mult, vec.y * mult, vec.z * mult);
}
double ft_dot_vec(t_vector vec1, t_vector vec2)
{
    return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

double ft_get_magnitude_vec(t_vector vec)
{
    return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}

t_vector    ft_normalize_vec(t_vector primitive_vec)
{
    double vec_mag = ft_get_magnitude_vec(primitive_vec);
    return ft_mult_vec(primitive_vec, 1/vec_mag);
}

double get_t_surface_hit_light(double t1, double t2)
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

t_vector calc_intersection_sight_and_sphere_vec(t_vector viewpoint, t_vector view_direct_vec, double A, double B, double C, double D)
{
    double t;
    t_vector intersection_sight_and_sphere_vec;
    if(D > 0)//交差点が２つある場合
    {
        double t1;
        double t2;
        t1 = ((-1 * B) - sqrt(D)) / (2 * A);
        t2 = ((-1 * B) + sqrt(D)) / (2 * A);
        t = get_t_surface_hit_light(t1, t2); //正かつ小さい方のtを採用
    }
    else
        t = ((-1 * B) - sqrt(D)) / (2 * A);
    return ft_add_vec(viewpoint, ft_mult_vec(view_direct_vec, t));
}

t_vector calc_normal_vec(t_vector pi, t_vector object_vec)
{
    double x,y,z;
    t_vector normal_vec;
    normal_vec = ft_sub_vec(ft_mult_vec(pi, 2), ft_mult_vec(object_vec, 2));
    normal_vec = ft_normalize_vec(normal_vec);
    return init_vector(normal_vec.x, normal_vec.y, normal_vec.z);
}

double ft_constrain(double v, double vmin, double vmax) {
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
    double      ka = 0.01;//環境光反射係数
    double      ia = 0.1;//環境光の強度
    double      kd = 0.69;//拡散反射係数
    double      ks = 0.3;//鏡面反射係数
    double      alpha = 8;//光沢度
    double r = 1;
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

            double A = ft_dot_vec(view_direct_vec, view_direct_vec);
            double B = 2 * ft_dot_vec(diff_vec, view_direct_vec);
            double C = ft_dot_vec(diff_vec, diff_vec) - pow(r, 2);
            double D = pow(B, 2) - (4 * A * C);
            if(D < 0)
                color = 0x6495ED;
            else//交差している
            {
                t_vector    pi;

                pi = calc_intersection_sight_and_sphere_vec(viewpoint, view_direct_vec, A, B, C, D);
                //直接光の拡散反射光の放射輝度
                t_vector light_dir = calc_normal_vec(light, pi);
                t_vector sphere_normal_vec = calc_normal_vec(pi, sphere);
                double di_dot = ft_dot_vec(sphere_normal_vec, light_dir);
                double diffuse_radience = ft_constrain(di_dot, 0, 1) * kd;
                t_vector reverse_view_direct_vec;
                t_vector specular_reflect_dir_vec;
                double specular_radience = 0;
                if(di_dot > 0)
                {
                    //直接光の鏡面反射光の放射輝度
                    reverse_view_direct_vec = ft_normalize_vec(ft_mult_vec(view_direct_vec, -1));
                    specular_reflect_dir_vec = ft_sub_vec(ft_mult_vec(sphere_normal_vec, 2 * di_dot), light_dir);
                    specular_radience = ft_constrain(ft_dot_vec(reverse_view_direct_vec, specular_reflect_dir_vec), 0, 1);
                    specular_radience = pow(specular_radience, alpha) * ks;
                }
                //環境光の反射光の放射輝度
                double ambient_radience = ka * ia;
                double radience = diffuse_radience + specular_radience + ambient_radience;
                radience = ft_constrain(radience, 0, 1);
                //radienceが1に近いほど白く(255に近く)なる
                int shadow = (int)(radience * 255);
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