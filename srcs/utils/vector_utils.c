#include "../../incs/vector_utils.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
void	set_vector(vector_t *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

vector_t init_vector(double x, double y, double z)
{
    vector_t new;
    new.x = x;
    new.y = y;
    new.z = z;
    return new;
}

vector_t ft_add_vec(vector_t vec1, vector_t vec2)
{
    return init_vector(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

vector_t ft_sub_vec(vector_t vec1, vector_t vec2)
{
    return init_vector(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

vector_t ft_mult_vec(vector_t vec, double mult)
{
    return init_vector(vec.x * mult, vec.y * mult, vec.z * mult);
}

float ft_constrain(float v, double vmin, double vmax) {
    if (v < vmin) {
        return vmin;
    } else if (v > vmax) {
        return vmax;
    } else {
        return v;
    }
}

float dot(const vector_t* a, const vector_t* b)
{
  return a->x * b->x + a->y * b->y + a->z * b->z;
}

float squared_norm(const vector_t*v)
{
  return SQR(v->x) + SQR(v->y) + SQR(v->z);
}

float norm(const vector_t *v)
{
  return sqrt(squared_norm(v));
}

float normalize(vector_t* v)
{
  float vnorm = norm(v);
  v->x /= vnorm;
  v->y /= vnorm;
  v->z /= vnorm;
  return vnorm;
}

void cross(vector_t* o, const vector_t*a, const vector_t*b)
{
  o->x = a->y * b->z - a->z * b->y;
  o->y = a->z * b->x - a->x * b->z;
  o->z = a->x * b->y - a->y * b->x;
}

const char* vector_str(const vector_t*v)
{
  static char buf[1024];
  memset(buf, 0, sizeof(buf));
  sprintf((void*)buf, "(%f, %f, %f)", v->x, v->y, v->z);
  return buf;
}