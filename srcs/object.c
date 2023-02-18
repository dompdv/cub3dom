#include <stdlib.h>
#include <stdio.h>
#include "../includes/object.h"
#include "../includes/color.h"

void hit_set(t_hit *hit, t_hit *from)
{
    hit->hit = from->hit;
    hit->distance = from->distance;
    vector_setv(&hit->impact, &from->impact);
    color_setc(&hit->color, &from->color);
}

void hit_nothing(t_hit *hit)
{
    hit->hit = 0;
    hit->distance = INFINITY;
}

void hit_something(t_hit *hit, double distance, t_vect *impact, t_color *color)
{
    hit->hit = 1;
    hit->distance = distance;
    vector_setv(&hit->impact, impact);
    color_setc(&hit->color, color);
}

int hit_has_hit(t_hit *hit)
{
    return hit->hit;
}

t_object *object_new_container(int n_max_objects)
{
    t_object *object;
    t_container *container;
    object = malloc(sizeof(t_object));
    object->type = O_Container;
    container = malloc(sizeof(t_container));
    container->n_max = n_max_objects;
    container->n = 0;
    container->objects = malloc(n_max_objects * sizeof(t_object));
    object->container = container;
    return object;
}

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

t_object *object_new_floor(t_color color1, t_color color2)
{
    t_object *object;
    t_floor *floor;
    object = malloc(sizeof(t_object));
    object->type = O_Floor;
    floor = malloc(sizeof(t_floor));
    color_setc(&floor->color1, &color1);
    color_setc(&floor->color2, &color2);
    object->floor = floor;
    return object;
}

void container_free(t_object *self)
{
    int i;
    for (i = 0; i < self->container->n_max; i++)
    {
        object_free(self->container->objects[i]);
    }
    free(self->container->objects);
    free(self->container);
    free(self);
}

void sky_free(t_object *self)
{
    free(self->sky);
    free(self);
}

void floor_free(t_object *self)
{
    free(self->floor);
    free(self);
}

void object_free(t_object *self)
{
    if (self->type == O_Container)
        container_free(self);
    if (self->type == O_Floor)
        floor_free(self);
    if (self->type == O_Sky)
        sky_free(self);
}

void container_add(t_object *self, t_object *o)
{
    if (self->type != O_Container)
        return;
    if (self->container->n < self->container->n_max)
    {
        self->container->objects[self->container->n] = o;
        self->container->n++;
    }
}

void container_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min)
{
    double distance;
    int i;
    t_hit local_hit;
    hit_nothing(hit);
    distance = INFINITY;

    for (i = 0; i < self->container->n; i++)
    {
        t_object *o = self->container->objects[i];
        object_cast_ray(o, &local_hit, eye, dir_n, dist_min);
        if (hit_has_hit(&local_hit)) // We hit something...
        {
            if (local_hit.distance <= distance && local_hit.distance >= dist_min) // ...closer to the previous one and after the screen
            {
                // update the distance and the impact description
                distance = local_hit.distance;
                hit_set(hit, &local_hit);
            }
        }
    }
}

void floor_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min)
{
    t_vect impact;
    t_color color;
    hit_nothing(hit);
    if ((dir_n->z * eye->z) < 0) // No impact if you're above the floor looking up or below the floor looking down
    {
        // Impact location
        vector_set(&impact, eye->x - dir_n->x * eye->z / dir_n->z, eye->y - dir_n->y * eye->z / dir_n->z, 0);
        long x, y;
        x = (long)impact.x;
        y = (long)impact.y;
        // Create the checker effect
        if ((x + y) % 2 == 0)
            color_setc(&color, &self->floor->color1);
        else
            color_setc(&color, &self->floor->color2);
        double distance;
        distance = vector_dist(eye, &impact);
        if (distance > dist_min)
        {
            hit_something(hit, distance, &impact, &color);
        }
    }
}

void sky_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min)
{
    t_vect impact;
    t_color color;
    hit_nothing(hit);
    vector_setv(&impact, dir_n);
    vector_scale(&impact, INFINITY);

    color_setc(&color, &self->sky->horizon);
    color_gradient(&color, &self->sky->azimut, dir_n->z);
    hit_something(hit, INFINITY, &impact, &color);
}

void object_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min)
{
    if (self->type == O_Container)
        container_cast_ray(self, hit, eye, dir_n, dist_min);
    if (self->type == O_Floor)
        floor_cast_ray(self, hit, eye, dir_n, dist_min);
    if (self->type == O_Sky)
        sky_cast_ray(self, hit, eye, dir_n, dist_min);
}
