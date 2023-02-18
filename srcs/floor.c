#include <stdlib.h>
#include "../includes/object.h"
#include "../includes/floor.h"

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

void floor_free(t_object *self)
{
    free(self->floor);
    free(self);
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
