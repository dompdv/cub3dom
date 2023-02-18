#ifndef SKY_H
#define SKY_H
#include "object.h"
#include "vector.h"
#include "color.h"
#include "hit.h"

typedef struct s_object t_object;

typedef struct s_sky
{
    t_color horizon;
    t_color azimut;
} t_sky;

t_object *object_new_sky(t_color horizon, t_color azimut);
void sky_free(t_object *self);
void sky_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min);

#endif