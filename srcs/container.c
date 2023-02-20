#include <stdlib.h>
#include <stdio.h>
#include "../includes/object.h"
#include "../includes/container.h"

t_object *object_new_container(int n_max_objects)
{
    t_object *object;
    t_container *container;
    object = malloc(sizeof(t_object));
    object->type = O_Container;

    object_init(object);
    // A priori, the container is bounded and englobing
    object->bounded = 1;

    container = malloc(sizeof(t_container));
    container->n_max = n_max_objects;
    container->n = 0;
    container->objects = malloc(n_max_objects * sizeof(t_object));
    object->container = container;
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

void container_add(t_object *self, t_object *o)
{
    if (self->type != O_Container)
        return;
    if (self->container->n < self->container->n_max)
    {
        self->container->objects[self->container->n] = o;
        self->container->n += 1;

        if (self->bounded)
        {
            if (o->bounded)
            {
                object_update_bounding_box_o(self, o);
            }
            else
            {
                // If we add an unbounded object, then the container is unbounded
                self->bounded = 0;
            }
        }
    }
}

void container_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min)
{
    // Testing is impact with each contained object is closer to the previous one
    for (int i = 0; i < self->container->n; i++)
    {
        object_cast_ray(self->container->objects[i], hit, eye, dir_n, dist_min);
    }
}
