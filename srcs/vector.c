#include <math.h>
#include <stdio.h>
#include "../includes/vector.h"

// Init a vector in cartesian coordinates
void vector_set(t_vect *vect, double x, double y, double z)
{
	vect->x = x;
	vect->y = y;
	vect->z = z;
}

// Init a vector in polar coordinates
// Theta : angle of the rotation around Z
// Psi   : angle of rotation around after first rotation
// l     : length of the resulting vector
void vector_set_polar(t_vect *vect, double theta, double psi, double l)
{
	double ct, st, cp, sp;
	ct = cos(theta);
	st = sin(theta);
	cp = cos(psi);
	sp = sin(psi);

	vect->x = l * ct * cp;
	vect->y = l * st * cp;
	vect->z = l * sp;
}

// Init a vector with another vector
void vector_setv(t_vect *vect, t_vect *vect2)
{
	vect->x = vect2->x;
	vect->y = vect2->y;
	vect->z = vect2->z;
}

// update a vector adding coordinates
void vector_add(t_vect *vect, double x, double y, double z)
{
	vect->x += x;
	vect->y += y;
	vect->z += z;
}

// update a vector adding another vector
void vector_addv(t_vect *vect, t_vect *vect2)
{
	vect->x += vect2->x;
	vect->y += vect2->y;
	vect->z += vect2->z;
}

// update a vector scaling it by a number
void vector_scale(t_vect *vect, double l)
{
	vect->x *= l;
	vect->y *= l;
	vect->z *= l;
}

// scalar product of two vectors
double vector_scalar(t_vect *vect, t_vect *vect2)
{
	return vect->x * vect2->x +
		   vect->y * vect2->y +
		   vect->z * vect2->z;
}

// square of the norm (length) of a vector
double vector_norms(t_vect *vect)
{
	return vect->x * vect->x +
		   vect->y * vect->y +
		   vect->z * vect->z;
}

// norm (length) of a vector
double vector_norm(t_vect *vect)
{
	return sqrt(vector_norms(vect));
}

// test if a vector is null
int vector_isnull(t_vect *vect)
{
	return vect->x == 0.0 &&
		   vect->y == 0.0 &&
		   vect->z == 0.0;
}

// set a vector to the null vector
void vector_nullify(t_vect *vect)
{
	vector_set(vect, 0.0, 0.0, 0.0);
}

// scale a (non null) vector to make it of norm 1.0
void vector_normalize(t_vect *vect)
{
	if (!vector_isnull(vect))
	{
		double norm;
		norm = vector_norm(vect);
		vector_scale(vect, 1 / norm);
	}
}

// rotate the vector around the X axis by rad radians
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

// rotate the vector around the Y axis by rad radians
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

// rotate the vector around the Z axis by rad radians
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

// print the vector after a label
void vector_print(t_vect *vector, char *name)
{
	printf("%s : (%f, %f, %f)\n", name, vector->x, vector->y, vector->z);
}

// Produit vectoriel v1^v2, resultat dans le troisième paramètre
void vector_product(t_vect *v1, t_vect *v2, t_vect *result)
{
	result->x = v1->y * v2->z - v1->z * v2->y;
	result->y = v1->z * v2->x - v1->x * v2->z;
	result->z = v1->x * v2->y - v1->y * v2->x;
}