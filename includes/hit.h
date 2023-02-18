#ifndef HIT_H
#define HIT_H
#include "color.h"
#include "vector.h"
#define INFINITY 1e+100

typedef struct s_hit
{
    int hit;
    t_vect impact;
    double distance;
    t_color color;
} t_hit;

void hit_set(t_hit *hit, t_hit *from);
void hit_nothing(t_hit *hit);
void hit_something(t_hit *hit, double distance, t_vect *impact, t_color *color);
int hit_has_hit(t_hit *hit);

#endif