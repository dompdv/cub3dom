#include "../includes/hit.h"

void hit_set(t_hit *hit, t_hit *from)
{
    hit->hit = from->hit;
    hit->distance = from->distance;
    vector_setv(&hit->impact, &from->impact);
    color_setc(&hit->color, &from->color);
}

void hit_nothing(t_hit *hit)
{
    hit->hit = 0;
    hit->distance = INFINITY;
}

void hit_something(t_hit *hit, double distance, t_vect *impact, t_color *color)
{
    hit->hit = 1;
    hit->distance = distance;
    vector_setv(&hit->impact, impact);
    color_setc(&hit->color, color);
}

int hit_has_hit(t_hit *hit)
{
    return hit->hit;
}
