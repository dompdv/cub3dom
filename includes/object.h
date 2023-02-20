#ifndef OBJECT_H
#define OBJECT_H
#include "vector.h"
#include "color.h"
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
    // Englobing == 1 => we can use the bounding box to check if we hit the bounding box before testing the inside
    int englobing;
    // Bounding box (some objects are not bounded, like Sky or Floor)
    int bounded;
    double x_min, x_max, y_min, y_max, z_min, z_max;
    // Data specific to each type
    union
    {
        t_container *container;
        t_floor *floor;
        t_sky *sky;
        t_cubes *cubes;
    };

} t_object;

void object_init(t_object *self);
void object_free(t_object *o);

void object_update_bounding_box(t_object *self, double x_min, double x_max, double y_min, double y_max, double z_min, double z_max);
void object_update_bounding_box_o(t_object *self, t_object *o2);

void object_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min);
void object_print(t_object *self);
#endif