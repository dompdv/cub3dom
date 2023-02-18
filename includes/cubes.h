#ifndef CUBES_H
#define CUBES_H
#include "object.h"
#include "vector.h"
#include "color.h"
#include "hit.h"

typedef struct s_object t_object;

typedef enum
{
    F_X,
    F_Y,
    F_Z
} Faces_types;

typedef struct s_face
{
    Faces_types type;
    double normal;
    double b_min, b_max;
    double c_min, c_max;
    double a;
    t_color color;
} t_face;

typedef struct s_cubes
{
    int n_max;
    t_face *face_x1;  // Face type X with normal 1
    t_face *face_xm1; // Face type X with normal -1
    t_face *face_y1;  // Face type Y with normal 1
    t_face *face_ym1; // Face type Y with normal -1
    t_face *face_z1;  // Face type Z with normal 1
    t_face *face_zm1; // Face type Z with normal -1
    int n_x1;
    int n_xm1;
    int n_y1;
    int n_ym1;
    int n_z1;
    int n_zm1;
} t_cubes;

t_object *object_new_cubes(int n_max_faces);
void cubes_free(t_object *self);

void cubes_add_face_x1(t_object *self, double y_min, double y_max, double z_min, double z_max, double x, t_color *color);
void cubes_add_face_xm1(t_object *self, double x, double y_min, double y_max, double z_min, double z_max, t_color *color);
void cubes_add_face_y1(t_object *self, double y, double x_min, double x_max, double z_min, double z_max, t_color *color);
void cubes_add_face_ym1(t_object *self, double y, double x_min, double x_max, double z_min, double z_max, t_color *color);
void cubes_add_face_z1(t_object *self, double z, double x_min, double x_max, double y_min, double y_max, t_color *color);
void cubes_add_face_zm1(t_object *self, double z, double x_min, double x_max, double y_min, double y_max, t_color *color);

void cubes_cast_ray(t_object *self, t_hit *hit, t_vect *eye, t_vect *dir_n, double dist_min);

#endif