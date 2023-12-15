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


void draw(t_rt  *rt_info)
{
    t_vector    viewpoint;
    t_vector    screen;
    t_vector    sphere;
    float r = 1;
    int color;
    viewpoint = init_vector(0, 0, -5);
    screen = init_vector(0, 0, 0);
    sphere = init_vector(0, 0, 5);
    int y = 0;
    int x = 0;
    while(y < HEIGHT)
    {
        screen.y = ((-2.0 * y) / (HEIGHT - 1)) + 1;
        x = 0;
        while(x < WIDTH)
        {
            screen.x = ((2.0 * x) / (WIDTH - 1)) - 1;
            t_vector direct_vec =  ft_sub_vec(screen, viewpoint);
            t_vector diff_vec = ft_sub_vec(viewpoint, sphere);//
            float A = ft_dot_vec(direct_vec, direct_vec);
            float B = 2 * ft_dot_vec(diff_vec, direct_vec);
            float C = ft_dot_vec(diff_vec, diff_vec) - pow(r, 2);
            float D = pow(B, 2) - (4 * A * C);
            if(D < 0)
                color = 0x0000ff;
            else
                color = 0xff0000;
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