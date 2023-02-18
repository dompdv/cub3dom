#include <stdlib.h>
#include "../includes/object.h"
#include "../includes/sky.h"

t_object *object_new_sky(t_color horizon, t_color azimut)
{
    t_object *object;
    t_sky *sky;
    object = malloc(sizeof(t_object));
    object->type = O_Sky;
    sky = malloc(sizeof(t_sky));
    color_setc(&sky->horizon, &horizon);
    color_setc(&sky->azimut, &azimut);
    object->sky = sky;
    return object;
}

void sky_free(t_object *self)
{
    free(self->sky);
    free(self);
}

void sky_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min)
{
    t_vect impact;
    t_color color;
    hit_nothing(hit);
    vector_setv(&impact, dir_n);
    vector_scale(&impact, INFINITY);

    color_setc(&color, &self->sky->azimut);
    color_gradient(&color, &self->sky->horizon, dir_n->z);
    hit_something(hit, INFINITY, &impact, &color);
}
