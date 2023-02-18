#ifndef OBJECT_H
#define OBJECT_H
#include "color.h"
#include "vector.h"
#include "hit.h"
#include "container.h"
#include "sky.h"
#include "floor.h"
#include "cubes.h"

#define INFINITY 1e+100

typedef enum
{
    O_Container,
    O_Sky,
    O_Floor,
    O_Cubes
} Object_types;

typedef struct s_object
{
    Object_types type;
    union
    {
        t_container *container;
        t_floor *floor;
        t_sky *sky;
        t_cubes *cubes;
    };

} t_object;

void object_free(t_object *o);

void object_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min);

#endif