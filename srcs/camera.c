#include <math.h>
#include <stdio.h>
#include "../includes/camera.h"
#include "../includes/vector.h"

void camera_set_origin(t_camera *camera, double x, double y, double z)
{
    vector_set(&camera->origin, x, y, z);
}

void camera_set_originv(t_camera *camera, t_vect *origin)
{
    vector_setv(&camera->origin, origin);
}

void _compute_local_referential(t_camera *camera)
{
    // rotation de -PI/2 du vecteur direction
    vector_setv(&camera->local_x, &camera->direction);
    vector_rotz(&camera->local_x, -M_PI_2);
    // le vecteur horizontal est horizontal ;)
    camera->local_x.z = 0;
    // On le renormalise
    vector_normalize(&camera->local_x);
    // le vecteur vertical s'obtient par produit vectoriel
    vector_product(&camera->local_x, &camera->direction, &camera->local_y);
}

void camera_set_direction(t_camera *camera, double x, double y, double z)
{
    t_vect n; // Normalised direction
    vector_set(&n, x, y, z);
    vector_normalize(&n);
    vector_setv(&camera->direction, &n);
    _compute_local_referential(camera);
}

void camera_set_direction_polar(t_camera *camera, double theta, double psi)
{
    t_vect n; // Normalised direction
    vector_set_polar(&n, theta, psi, 1.0);
    vector_setv(&camera->direction, &n);
    _compute_local_referential(camera);
}

void camera_set_directionv(t_camera *camera, t_vect *direction)
{
    t_vect n; // Normalised direction
    vector_setv(&n, direction);
    vector_normalize(&n);
    vector_setv(&camera->direction, &n);
    _compute_local_referential(camera);
}

void camera_set_focal(t_camera *camera, double f)
{
    camera->focal = f;
}

void camera_set_real_width(t_camera *camera, double w)
{
    camera->real_width = w;
}

void camera_ray(t_vect *ray, t_camera *camera, int x, int y, int screen_w, int screen_h)
{
    t_vect u, v;
    double scale_factor;
    // Compute the center of the screen in model space
    vector_setv(ray, &camera->direction);
    vector_scale(ray, camera->focal);
    //    vector_addv(ray, &camera->origin);
    // Horizontal
    scale_factor = camera->real_width / ((double)screen_w);
    vector_setv(&u, &camera->local_x);
    vector_scale(&u, scale_factor);
    vector_scale(&u, (double)(x - screen_w / 2));
    // Vertical
    vector_setv(&v, &camera->local_y);
    vector_scale(&v, scale_factor);
    vector_scale(&v, (double)(y - screen_h / 2));
    // Add all
    vector_addv(ray, &u);
    vector_addv(ray, &v);
}

void camera_print(t_camera *camera)
{
    printf("Camera:\n");
    vector_print(&camera->origin, "Origin");
    vector_print(&camera->direction, "Direction");
    vector_print(&camera->local_x, "Local_x");
    vector_print(&camera->local_y, "Local_y");
}
