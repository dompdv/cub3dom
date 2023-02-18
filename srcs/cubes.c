#include <stdlib.h>
#include "../includes/object.h"
#include "../includes/cubes.h"

t_object *object_new_cubes(int n_max_faces)
{
    t_object *object;
    t_cubes *cubes;
    object = malloc(sizeof(t_object));
    object->type = O_Container;
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

void cubes_add_face_x1(t_object *self, double y_min, double y_max, double z_min, double z_max, double x, t_color *color)
{
    t_cubes *cubes = self->cubes;
    if (cubes->n_x1 < cubes->n_max)
    {
        t_face *face;
        face = &cubes->face_x1[cubes->n_x1];
        face->type = F_X;
        face->normal = 1;
        face->a = x;
        face->b_min = y_min;
        face->b_max = y_max;
        face->c_min = z_min;
        face->c_max = z_max;
        color_setc(&face->color, color);
        cubes->n_x1 += 1;
    }
}

void cubes_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min)
{
}