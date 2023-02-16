#ifndef VECTOR_H
#define VECTOR_H

typedef struct s_vect
{
    double x;
    double y;
    double z;
} t_vect;

void vector_set(t_vect *vect, double x, double y, double z);
void vector_set_polar(t_vect *vect, double theta, double psi, double l);
void vector_setv(t_vect *vect, t_vect *vect2);
void vector_add(t_vect *vect, double x, double y, double z);
void vector_addv(t_vect *vect, t_vect *vect2);
void vector_scale(t_vect *vect, double l);
double vector_scalar(t_vect *vect, t_vect *vect2);
double vector_normes(t_vect *vect);
double vector_norme(t_vect *vect);
int vector_isnull(t_vect *vect);
void vector_nullify(t_vect *vect);
void vector_normalize(t_vect *vect);
void vector_rotx(t_vect *vect, double rad);
void vector_roty(t_vect *vect, double rad);
void vector_rotz(t_vect *vect, double rad);
void vector_print(t_vect *vector, char *name);
void vector_test();

#endif
