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
    if (self->x_min == 0 && self->x_max == 0 && self->y_min == 0 && self->y_max == 0 && self->z_min == 0 && self->z_max == 0)
    {
        self->x_min = x_min;
        self->x_max = x_max;
        self->y_min = y_min;
        self->y_max = y_max;
        self->z_min = z_min;
        self->z_max = z_max;
        return;
    }
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

int object_in_bounding_box(t_object *o, t_vect *eye)
{
    return (eye->x >= o->x_min && eye->x <= o->x_max && eye->y >= o->y_min && eye->y <= o->y_max && eye->z >= o->z_min && eye->z <= o->z_max);
}

int object_ray_intersects_bounding_box(t_object *o, t_vect *eye, t_vect *dir_n)
{
    double x, y, z, t;
    // x faces (YZ planes)
    if (dir_n->x != 0)
    {
        t = (o->x_min - eye->x) / dir_n->x;
        if (t > 0)
        {
            y = eye->y + t * dir_n->y;
            z = eye->z + t * dir_n->z;
            if (y >= o->y_min && y <= o->y_max && z >= o->z_min && z <= o->z_max)
                return 1;
        }
        t = (o->x_max - eye->x) / dir_n->x;
        if (t > 0)
        {
            y = eye->y + t * dir_n->y;
            z = eye->z + t * dir_n->z;
            if (y >= o->y_min && y <= o->y_max && z >= o->z_min && z <= o->z_max)
                return 1;
        }
    }
    if (dir_n->y != 0)
    {
        t = (o->y_min - eye->y) / dir_n->y;
        if (t > 0)
        {
            x = eye->x + t * dir_n->x;
            z = eye->z + t * dir_n->z;
            if (x >= o->x_min && x <= o->x_max && z >= o->z_min && z <= o->z_max)
                return 1;
        }
        t = (o->y_max - eye->y) / dir_n->y;
        if (t > 0)
        {
            x = eye->x + t * dir_n->x;
            z = eye->z + t * dir_n->z;
            if (x >= o->x_min && x <= o->x_max && z >= o->z_min && z <= o->z_max)
                return 1;
        }
    }
    if (dir_n->z != 0)
    {
        t = (o->z_min - eye->z) / dir_n->z;
        if (t > 0)
        {
            x = eye->x + t * dir_n->x;
            y = eye->y + t * dir_n->y;
            if (x >= o->x_min && x <= o->x_max && y >= o->y_min && y <= o->y_max)
                return 1;
        }
        t = (o->z_max - eye->z) / dir_n->z;
        if (t > 0)
        {
            x = eye->x + t * dir_n->x;
            y = eye->y + t * dir_n->y;
            if (x >= o->x_min && x <= o->x_max && y >= o->y_min && y <= o->y_max)
                return 1;
        }
    }
    return 0;
}
void object_cast_ray_per_type(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min)
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

void object_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min)
{
    // If bounded, check if the ray intersect
    if (!self->bounded)
        return object_cast_ray_per_type(self, hit, eye, dir_n, dist_min);
    // If the eye is in the bounding box
    if (object_in_bounding_box(self, eye))
        return object_cast_ray_per_type(self, hit, eye, dir_n, dist_min);
    // If the ray intersects the bounding box
    if (object_ray_intersects_bounding_box(self, eye, dir_n))
        return object_cast_ray_per_type(self, hit, eye, dir_n, dist_min);
}

void object_print(t_object *self)
{
    printf("Object type: %d, bounded: %d, x,y,z=(%f,%f),(%f,%f),(%f,%f)\n",
           (int)self->type, self->bounded, self->x_min, self->x_max, self->y_min, self->y_max, self->z_min, self->z_max);
}