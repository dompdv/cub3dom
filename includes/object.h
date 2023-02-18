#ifndef OBJECT_H
#define OBJECT_H
#include "color.h"
#include "vector.h"

typedef enum
{
    O_Container,
    O_Sky,
    O_Floor
} Object_types;

typedef struct s_object t_object;

typedef struct s_container
{
    int n_max;
    int n;
    t_object **objects;
} t_container;

typedef struct s_sky
{
    t_color horizon;
    t_color azimut;
} t_sky;

typedef struct s_floor
{
    t_color color;
} t_floor;

typedef struct s_object
{
    Object_types type;
    union
    {
        t_container *container;
        t_floor *floor;
        t_sky *sky;
    };

} t_object;

t_object *object_new_container(int n_max_objects);
t_object *object_new_sky(t_color horizon, t_color azimut);
t_object *object_new_floor(t_color color);
void object_free(t_object *o);

void container_add(t_object *self, t_object *o);

#endif