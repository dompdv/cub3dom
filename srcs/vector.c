#include <math.h>
#include <stdio.h>
#include "../includes/vector.h"

void vector_set(t_vect *vect, double x, double y, double z)
{
	vect->x = x;
	vect->y = y;
	vect->z = z;
}
void vector_setv(t_vect *vect, t_vect *vect2)
{
	vect->x = vect2->x;
	vect->y = vect2->y;
	vect->z = vect2->z;
}

void vector_add(t_vect *vect, double x, double y, double z)
{
	vect->x += x;
	vect->y += y;
	vect->z += z;
}
void vector_addv(t_vect *vect, t_vect *vect2)
{
	vect->x += vect2->x;
	vect->y += vect2->y;
	vect->z += vect2->z;
}

void vector_scale(t_vect *vect, double l)
{
	vect->x *= l;
	vect->y *= l;
	vect->z *= l;
}

double vector_scalar(t_vect *vect, t_vect *vect2)
{
	return vect->x * vect2->x +
		   vect->y * vect2->y +
		   vect->z * vect2->z;
}

double vector_normes(t_vect *vect)
{
	return vect->x * vect->x +
		   vect->y * vect->y +
		   vect->z * vect->z;
}

double vector_norme(t_vect *vect)
{
	return sqrt(vector_normes(vect));
}

int vector_isnull(t_vect *vect)
{
	return vect->x == 0.0 &&
		   vect->y == 0.0 &&
		   vect->z == 0.0;
}

void vector_nullify(t_vect *vect)
{
	vector_set(vect, 0.0, 0.0, 0.0);
}

void vector_normalize(t_vect *vect)
{
	if (!vector_isnull(vect))
	{
		double norm;
		norm = vector_norme(vect);
		vector_scale(vect, 1 / norm);
	}
}

void vector_rotx(t_vect *vect, double rad)
{
	double c, s, y, z;
	c = cos(rad);
	s = sin(rad);
	y = c * vect->y - s * vect->z;
	z = s * vect->y + c * vect->z;
	vect->y = y;
	vect->z = z;
}

void vector_roty(t_vect *vect, double rad)
{
	double c, s, z, x;
	c = cos(rad);
	s = sin(rad);
	z = c * vect->z - s * vect->x;
	x = s * vect->z + c * vect->x;
	vect->z = z;
	vect->x = x;
}

void vector_rotz(t_vect *vect, double rad)
{
	double c, s, x, y;
	c = cos(rad);
	s = sin(rad);
	x = c * vect->x - s * vect->y;
	y = s * vect->x + c * vect->y;
	vect->x = x;
	vect->y = y;
}

void vector_print(t_vect *vector, char *name)
{
	printf("%s : (%f, %f, %f)\n", name, vector->x, vector->y, vector->z);
}
