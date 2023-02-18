#include <stdlib.h>
#include "../includes/object.h"
#include "../includes/container.h"

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
        self->container->n++;
    }
}

void container_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min)
{
    double distance;
    int i;
    t_hit local_hit;

    // Starting with nothing hit yet
    hit_nothing(hit);
    distance = INFINITY;

    // Testing is impact with each contained object is closer to the previous one
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
