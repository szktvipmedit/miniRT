#include "../../incs/raytracing.h"


int store_out_variable(shape_t *nearest_shape, intersection_point_t nearest_intp, shape_t **out_shape,intersection_point_t *out_intp)
{
    if ( out_shape )
    *out_shape = nearest_shape;
    if ( out_intp )
    *out_intp = nearest_intp;
    return 1;
}