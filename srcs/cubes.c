#include <stdlib.h>
#include <stdio.h>
#include "../includes/object.h"
#include "../includes/cubes.h"

t_object *object_new_cubes(int n_max_faces)
{
    t_object *object;
    t_cubes *cubes;
    object = malloc(sizeof(t_object));
    object_init(object);
    object->type = O_Cubes;
    object->bounded = 1;
    cubes = malloc(sizeof(t_cubes));
    cubes->n_max = n_max_faces;
    cubes->n_x1 = 0;
    cubes->n_xm1 = 0;
    cubes->n_y1 = 0;
    cubes->n_ym1 = 0;
    cubes->n_z1 = 0;
    cubes->n_zm1 = 0;

    cubes->face_x1 = malloc(n_max_faces * sizeof(t_face));
    cubes->face_xm1 = malloc(n_max_faces * sizeof(t_face));
    cubes->face_y1 = malloc(n_max_faces * sizeof(t_face));
    cubes->face_ym1 = malloc(n_max_faces * sizeof(t_face));
    cubes->face_z1 = malloc(n_max_faces * sizeof(t_face));
    cubes->face_zm1 = malloc(n_max_faces * sizeof(t_face));

    object->cubes = cubes;
    return object;
}

void cubes_free(t_object *self)
{
    free(self->cubes->face_x1);
    free(self->cubes->face_xm1);
    free(self->cubes->face_y1);
    free(self->cubes->face_ym1);
    free(self->cubes->face_z1);
    free(self->cubes->face_zm1);
    free(self->cubes);
    free(self);
}

int cubes_empty(t_object *self)
{
    return (self->cubes->n_x1 + self->cubes->n_xm1 + self->cubes->n_y1 + self->cubes->n_ym1 + self->cubes->n_z1 + self->cubes->n_zm1) == 0;
}

void order(double *a, double *b)
{
    if (*a > *b)
    {
        double c = *a;
        *a = *b;
        *b = c;
    }
}

void cubes_add_face_x1(t_object *self, double x, double y_min, double y_max, double z_min, double z_max, t_color *color)
{
    order(&y_min, &y_max);
    order(&z_min, &z_max);
    t_cubes *cubes = self->cubes;
    if (cubes->n_x1 < cubes->n_max)
    {
        t_face *face;
        object_update_bounding_box(self, x, x, y_min, y_max, z_min, z_max);
        face = &cubes->face_x1[cubes->n_x1];
        cubes->n_x1 += 1;
        face->type = F_X;
        face->normal = 1;
        face->a = x;
        face->b_min = y_min;
        face->b_max = y_max;
        face->c_min = z_min;
        face->c_max = z_max;
        color_setc(&face->color, color);
    }
}

void cubes_add_face_xm1(t_object *self, double x, double y_min, double y_max, double z_min, double z_max, t_color *color)
{
    order(&y_min, &y_max);
    order(&z_min, &z_max);
    t_cubes *cubes = self->cubes;
    if (cubes->n_xm1 < cubes->n_max)
    {
        t_face *face;
        object_update_bounding_box(self, x, x, y_min, y_max, z_min, z_max);
        face = &cubes->face_xm1[cubes->n_xm1];
        cubes->n_xm1 += 1;
        face->type = F_X;
        face->normal = -1;
        face->a = x;
        face->b_min = y_min;
        face->b_max = y_max;
        face->c_min = z_min;
        face->c_max = z_max;
        color_setc(&face->color, color);
    }
}

void cubes_add_face_y1(t_object *self, double y, double x_min, double x_max, double z_min, double z_max, t_color *color)
{
    order(&x_min, &x_max);
    order(&z_min, &z_max);
    t_cubes *cubes = self->cubes;
    if (cubes->n_y1 < cubes->n_max)
    {
        t_face *face;
        object_update_bounding_box(self, x_min, x_max, y, y, z_min, z_max);
        face = &cubes->face_y1[cubes->n_y1];
        cubes->n_y1 += 1;
        face->type = F_Y;
        face->normal = 1;
        face->a = y;
        face->b_min = x_min;
        face->b_max = x_max;
        face->c_min = z_min;
        face->c_max = z_max;
        color_setc(&face->color, color);
    }
}
void cubes_add_face_ym1(t_object *self, double y, double x_min, double x_max, double z_min, double z_max, t_color *color)
{
    order(&x_min, &x_max);
    order(&z_min, &z_max);
    t_cubes *cubes = self->cubes;
    if (cubes->n_ym1 < cubes->n_max)
    {
        t_face *face;
        object_update_bounding_box(self, x_min, x_max, y, y, z_min, z_max);
        face = &cubes->face_ym1[cubes->n_ym1];
        cubes->n_ym1 += 1;
        face->type = F_Y;
        face->normal = -1;
        face->a = y;
        face->b_min = x_min;
        face->b_max = x_max;
        face->c_min = z_min;
        face->c_max = z_max;
        color_setc(&face->color, color);
    }
}

void cubes_add_face_z1(t_object *self, double z, double x_min, double x_max, double y_min, double y_max, t_color *color)
{
    order(&x_min, &x_max);
    order(&y_min, &y_max);
    t_cubes *cubes = self->cubes;
    if (cubes->n_z1 < cubes->n_max)
    {
        t_face *face;
        object_update_bounding_box(self, x_min, x_max, y_min, y_max, z, z);
        face = &cubes->face_z1[cubes->n_z1];
        cubes->n_z1 += 1;
        face->type = F_Z;
        face->normal = 1;
        face->a = z;
        face->b_min = x_min;
        face->b_max = x_max;
        face->c_min = y_min;
        face->c_max = y_max;
        color_setc(&face->color, color);
    }
}
void cubes_add_face_zm1(t_object *self, double z, double x_min, double x_max, double y_min, double y_max, t_color *color)
{
    order(&x_min, &x_max);
    order(&y_min, &y_max);
    t_cubes *cubes = self->cubes;
    if (cubes->n_zm1 < cubes->n_max)
    {
        t_face *face;
        object_update_bounding_box(self, x_min, x_max, y_min, y_max, z, z);
        face = &cubes->face_zm1[cubes->n_zm1];
        cubes->n_zm1 += 1;
        face->type = F_Z;
        face->normal = -1;
        face->a = z;
        face->b_min = x_min;
        face->b_max = x_max;
        face->c_min = y_min;
        face->c_max = y_max;
        color_setc(&face->color, color);
    }
}

void _cast_ray_x(t_face *faces, int n_faces, t_hit *hit, t_vect *eye, t_vect *dir_n, double normal, double dist_min)
{
    t_vect impact;
    int i;
    double x, y, z; // Impact
    double d;
    double t;

    for (i = 0; i < n_faces; i++)
    {
        t_face *f = &faces[i];
        x = f->a;
        t = (x - eye->x) / dir_n->x;
        if (t > 0)
        {
            y = eye->y + t * dir_n->y;
            z = eye->z + t * dir_n->z;
            if (y >= f->b_min && y <= f->b_max && z >= f->c_min && z <= f->c_max)
            {
                vector_set(&impact, x, y, z);
                d = vector_dist(eye, &impact);
                if (d > dist_min && (!hit_has_hit(hit) || (d < hit->distance)))
                {
                    hit_something(hit, d, &impact, &f->color);
                }
            }
        }
    }
}
void _cast_ray_y(t_face *faces, int n_faces, t_hit *hit, t_vect *eye, t_vect *dir_n, double normal, double dist_min)
{
    t_vect impact;
    int i;
    double x, y, z; // Impact
    double d;
    double t;

    for (i = 0; i < n_faces; i++)
    {
        t_face *f = &faces[i];
        y = f->a;
        t = (y - eye->y) / dir_n->y;
        if (t > 0)
        {
            x = eye->x + t * dir_n->x;
            z = eye->z + t * dir_n->z;
            if (x >= f->b_min && x <= f->b_max && z >= f->c_min && z <= f->c_max)
            {
                vector_set(&impact, x, y, z);
                d = vector_dist(eye, &impact);
                if (d > dist_min && (!hit_has_hit(hit) || (d < hit->distance)))
                {
                    hit_something(hit, d, &impact, &f->color);
                }
            }
        }
    }
}

void _cast_ray_z(t_face *faces, int n_faces, t_hit *hit, t_vect *eye, t_vect *dir_n, double normal, double dist_min)
{
    t_vect impact;
    int i;
    double x, y, z; // Impact
    double d;
    double t;

    for (i = 0; i < n_faces; i++)
    {
        t_face *f = &faces[i];
        z = f->a;
        t = (z - eye->z) / dir_n->z;
        if (t > 0)
        {
            x = eye->x + t * dir_n->x;
            y = eye->y + t * dir_n->y;
            if (x >= f->b_min && x <= f->b_max && y >= f->c_min && y <= f->c_max)
            {
                vector_set(&impact, x, y, z);
                d = vector_dist(eye, &impact);
                if (d > dist_min && (!hit_has_hit(hit) || (d < hit->distance)))
                {
                    hit_something(hit, d, &impact, &f->color);
                }
            }
        }
    }
}

void cubes_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min)
{
    if (dir_n->x < 0)
        _cast_ray_x(self->cubes->face_x1, self->cubes->n_x1, hit, eye, dir_n, 1.0, dist_min);
    else if (dir_n->x > 0)
        _cast_ray_x(self->cubes->face_xm1, self->cubes->n_xm1, hit, eye, dir_n, -1.0, dist_min);
    if (dir_n->y < 0)
        _cast_ray_y(self->cubes->face_y1, self->cubes->n_y1, hit, eye, dir_n, 1.0, dist_min);
    else if (dir_n->y > 0)
        _cast_ray_y(self->cubes->face_ym1, self->cubes->n_ym1, hit, eye, dir_n, -1.0, dist_min);
    if (dir_n->z < 0)
        _cast_ray_z(self->cubes->face_z1, self->cubes->n_z1, hit, eye, dir_n, 1.0, dist_min);
    else if (dir_n->z > 0)
        _cast_ray_z(self->cubes->face_zm1, self->cubes->n_zm1, hit, eye, dir_n, -1.0, dist_min);
}