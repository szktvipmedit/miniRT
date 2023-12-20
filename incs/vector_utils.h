#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include <math.h>

#define SQR(x) ((x)*(x))
#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)
#define CLAMP(v,minv,maxv) MIN(MAX(v,minv),maxv)

typedef struct {
  float x;
  float y;
  float z;
} vector_t;

void	set_vector(vector_t *vec, float x, float y, float z);
vector_t init_vector(double x, double y, double z);
vector_t ft_add_vec(vector_t vec1, vector_t vec2);
vector_t ft_sub_vec(vector_t vec1, vector_t vec2);
vector_t ft_mult_vec(vector_t vec, double mult);
float ft_constrain(float v, double vmin, double vmax);
float dot(const vector_t* a, const vector_t* b);
float squared_norm(const vector_t*v);

float norm(const vector_t *v);
float normalize(vector_t* v);

void cross(vector_t* o, const vector_t*a, const vector_t*b);

const char* vector_str(const vector_t*v);

#endif