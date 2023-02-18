#include <stdlib.h>
#include <stdio.h>
#include "../includes/object.h"

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

t_object *object_new_floor(t_color color)
{
    t_object *object;
    t_floor *floor;
    object = malloc(sizeof(t_object));
    object->type = O_Floor;
    floor = malloc(sizeof(t_floor));
    color_setc(&floor->color, &color);
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
