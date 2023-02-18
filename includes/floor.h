#ifndef FLOOR_H
#define FLOOR_H
#include "object.h"
#include "vector.h"
#include "color.h"
#include "hit.h"

typedef struct s_object t_object;

typedef struct s_floor
{
    t_color color1;
    t_color color2;
} t_floor;

t_object *object_new_floor(t_color color1, t_color color2);
void floor_free(t_object *self);
void floor_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min);

#endif