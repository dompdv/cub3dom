#include <stdlib.h>
#include <stdio.h>
#include "../includes/object.h"
#include "../includes/color.h"
#include "../includes/hit.h"
#include "../includes/container.h"
#include "../includes/sky.h"
#include "../includes/floor.h"
#include "../includes/cubes.h"

void object_init(t_object *self)
{
    self->bounded = 0;
    self->englobing = 0;
    self->x_min = 0;
    self->x_max = 0;
    self->y_min = 0;
    self->y_max = 0;
    self->z_min = 0;
    self->z_max = 0;
}

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

void object_update_bounding_box(t_object *self, double x_min, double x_max, double y_min, double y_max, double z_min, double z_max)
{
    if (x_min < self->x_min)
        self->x_min = x_min;
    if (x_max > self->x_max)
        self->x_max = x_max;
    if (y_min < self->y_min)
        self->y_min = y_min;
    if (y_max > self->y_max)
        self->y_max = y_max;
    if (z_min < self->z_min)
        self->z_min = z_min;
    if (z_max > self->z_max)
        self->z_max = z_max;
}
void object_update_bounding_box_o(t_object *self, t_object *o2)
{
    object_update_bounding_box(self, o2->x_min, o2->x_max, o2->y_min, o2->y_max, o2->z_min, o2->z_max);
}

void object_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min)
{
    if (self->type == O_Container)
        container_cast_ray(self, hit, eye, dir_n, dist_min);
    if (self->type == O_Floor)
        floor_cast_ray(self, hit, eye, dir_n, dist_min);
    if (self->type == O_Sky)
        sky_cast_ray(self, hit, eye, dir_n, dist_min);
    if (self->type == O_Cubes)
        cubes_cast_ray(self, hit, eye, dir_n, dist_min);
}

void object_print(t_object *self)
{
    printf("Object type: %d, englobing: %d, bounded: %d, x,y,z=(%f,%f),(%f,%f),(%f,%f)\n",
           (int)self->type, self->englobing, self->bounded, self->x_min, self->x_max, self->y_min, self->y_max, self->z_min, self->z_max);
}