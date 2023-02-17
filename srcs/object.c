#include <stdlib.h>
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

void object_free(t_object *self)
{
    if (self->type == O_Container)
    {
        int i;
        for (i = 0; i < self->container->n_max; i++)
        {
            free(self->container->objects[i]);
        }
        free(self->container->objects);
        free(self->container);
        free(self);
    }
}

void container_add(t_object *self, t_object *o)
{
    if (o->type != O_Container)
        return;
    if (self->container->n < self->container->n_max)
    {
        self->container->objects[self->container->n] = o;
        self->container->n++;
    }
}