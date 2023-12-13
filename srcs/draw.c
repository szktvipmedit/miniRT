#include "../incs/minirt.h"

void stroke()
{

}
void draw(t_rt  *rt_info)
{
    (void)rt_info;
    int y = 0;
    int x = 0;
    while(y < HEIGHT)
    {
        x = 0;
        double ny = 255 / (double)HEIGHT;
        int b;
        while(x < WIDTH)
        {
            double nx = 255 / (double)WIDTH;
            double nxy = 255 / (double)(WIDTH * HEIGHT);
            int r = 255 - (int)(nx * x);
            int g = (int)(ny * y);
            b = (int)(nxy * x * y);
            int color = r << 16 | g << 8 | b;

            int i = (y * rt_info->size_line) + (x * rt_info->bit_per_pixel / 8);
            rt_info->data_addr[i] = color;
            rt_info->data_addr[i + 1] = color >> 8;
            rt_info->data_addr[i + 2] = color >> 16;
            x++;
        }
        printf("%i\n", b);
        y++;
    }
    mlx_put_image_to_window(rt_info->mlx_ptr, rt_info->win_ptr, rt_info->img_ptr, 0, 0);
}