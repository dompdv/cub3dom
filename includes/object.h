#ifndef OBJECT_H
#define OBJECT_H
#include "color.h"
#include "vector.h"

#define INFINITY 1e+100

typedef struct s_hit
{
    int hit;
    t_vect impact;
    double distance;
    t_color color;
} t_hit;

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
    t_color color1;
    t_color color2;
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

void hit_set(t_hit *hit, t_hit *from);
void hit_nothing(t_hit *hit);
void hit_something(t_hit *hit, double distance, t_vect *impact, t_color *color);
int hit_has_hit(t_hit *hit);

t_object *object_new_container(int n_max_objects);
t_object *object_new_sky(t_color horizon, t_color azimut);
t_object *object_new_floor(t_color color1, t_color color2);
void object_free(t_object *o);

void container_add(t_object *self, t_object *o);

void object_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min);

#endif