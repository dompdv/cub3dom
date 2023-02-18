#ifndef CONTAINER_H
#define CONTAINER_H
#include "object.h"
#include "vector.h"
#include "hit.h"

typedef struct s_object t_object;

typedef struct s_container
{
    int n_max;
    int n;
    t_object **objects;
} t_container;

t_object *object_new_container(int n_max_objects);
void container_free(t_object *self);
void container_add(t_object *self, t_object *o);
void container_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min);

#endif