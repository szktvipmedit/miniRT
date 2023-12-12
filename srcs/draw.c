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
        int color = 0xff0000;
        while(x < WIDTH)
        {
            // if(0 <= x && x < WIDTH && 0 <= y && y < HEIGHT)
            // {
            
            double n = 255 / (double)WIDTH;
            int r = (int)(n * x);
            int b = (int)(n * x);
            int g = (int)(n * x);
            // color = (r << 16) | (g << 8) | b; 

            int i = (y * rt_info->size_line) + (x * rt_info->bit_per_pixel / 8);
            rt_info->data_addr[i] = r;
            rt_info->data_addr[i + 1] = g;
            rt_info->data_addr[i + 2] = b;
            // }
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(rt_info->mlx_ptr, rt_info->win_ptr, rt_info->img_ptr, 0, 0);
}