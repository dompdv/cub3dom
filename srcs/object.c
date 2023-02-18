#include <stdlib.h>
#include <stdio.h>
#include "../includes/object.h"
#include "../includes/color.h"
#include "../includes/hit.h"
#include "../includes/container.h"
#include "../includes/sky.h"
#include "../includes/floor.h"
#include "../includes/cubes.h"

void object_free(t_object *self)
{
    if (self->type == O_Container)
        container_free(self);
    if (self->type == O_Floor)
        floor_free(self);
    if (self->type == O_Sky)
        sky_free(self);
    if (self->type == O_Cubes)
        cubes_free(self);
}

void object_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min)
{
    if (self->type == O_Container)
        container_cast_ray(self, hit, eye, dir_n, dist_min);
    if (self->type == O_Floor)
        floor_cast_ray(self, hit, eye, dir_n, dist_min);
    if (self->type == O_Sky)
        sky_cast_ray(self, hit, eye, dir_n, dist_min);
    if (self->type == O_Sky)
        cubes_cast_ray(self, hit, eye, dir_n, dist_min);
}
