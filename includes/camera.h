#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"

typedef struct s_camera
{
    t_vect origin;     // origin of the eye
    t_vect direction;  // normalized vector of the direction
    double focal;      // length between the eye and the screen, in the direction of sight
    double real_width; // width of the screen in the model space

    // local_x and local_y are automatically set when a direction is set
    // The horizontal local vector is both horizontal for the sceen and the model space
    t_vect local_x; // horizontal unit local vector of the screen
    t_vect local_y; // vertical unit local vector of the screen
} t_camera;

void camera_set_origin(t_camera *camera, double x, double y, double z);
void camera_set_originv(t_camera *camera, t_vect *origin);
void camera_set_direction(t_camera *camera, double x, double y, double z);
void camera_set_direction_polar(t_camera *camera, double theta, double psi);
void camera_set_directionv(t_camera *camera, t_vect *direction);
void camera_set_focal(t_camera *camera, double f);
void camera_set_real_width(t_camera *camera, double w);
void camera_ray(t_vect *ray, t_camera *camera, int x, int y, int screen_w, int screen_h);
void camera_move(t_camera *camera, double vx, double vy);
void camera_turn(t_camera *camera, double rad);
void camera_print(t_camera *camera);

#endif