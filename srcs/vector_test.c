#include <stdio.h>
#include <math.h>
#include "../includes/vector.h"

void vector_test()
{
    /*
        Testing Vector
        v1 : (1.000000, 2.000000, 3.000000)
        v2 (copy of v1) : (1.000000, 2.000000, 3.000000)
        v3 (null vector) : (0.000000, 0.000000, 0.000000)
        v4 (3*v1) : (3.000000, 6.000000, 9.000000)
        v1 adding (1,1,1) : (2.000000, 3.000000, 4.000000)
        v3 adding v1 : (2.000000, 3.000000, 4.000000)
        v1.v4 = 60.000000
        n2(v1) = 29.000000
        n2(v1) = 29.000000
        n(v1) = 5.385165
        v1 (normalized) : (0.371391, 0.557086, 0.742781)
    */
    t_vect v1, v2, v3, v4;
    printf("Testing Vector\n");

    vector_set(&v1, 1, 2, 3);
    vector_setv(&v2, &v1);
    vector_nullify(&v3);
    vector_setv(&v4, &v2);
    vector_scale(&v4, 3.0);
    vector_print(&v1, "v1");
    vector_print(&v2, "v2 (copy of v1)");
    vector_print(&v3, "v3 (null vector)");
    vector_print(&v4, "v4 (3*v1)");

    vector_add(&v1, 1, 1, 1);
    vector_print(&v1, "v1 adding (1,1,1)");
    vector_addv(&v3, &v1);
    vector_print(&v3, "v3 adding v1");
    printf("v1.v4 = %f\n", vector_scalar(&v1, &v4));
    printf("n2(v1) = %f\n", vector_normes(&v1));
    printf("n2(v1) = %f\n", vector_scalar(&v1, &v1));
    printf("n(v1) = %f\n", vector_norme(&v1));
    vector_normalize(&v1);
    vector_print(&v1, "v1 (normalized)");
    printf("non nullified v1 is null : %d\n", vector_isnull(&v1));
    vector_nullify(&v1);
    printf("nullified v1 is null : %d\n", vector_isnull(&v1));

    vector_set(&v1, 1, 0, 5);
    vector_print(&v1, "reset v1");
    vector_rotz(&v1, M_PI);
    vector_print(&v1, "After half turn XY");
    vector_rotz(&v1, 3 * M_PI_2);
    vector_print(&v1, "Quarter turn XY");
    int n = 25;
    for (int i = 0; i < n; i++)
    {
        vector_rotz(&v1, 2 * M_PI / ((double)n));
    }
    vector_print(&v1, "Same place after many small turns XY");

    vector_set(&v1, 5, 1, 1);
    vector_print(&v1, "reset v1");
    vector_rotx(&v1, M_PI_2);
    vector_print(&v1, "After a quarter turn YZ");

    vector_set(&v1, 1, 5, 1);
    vector_print(&v1, "reset v1");
    vector_roty(&v1, M_PI_2);
    vector_print(&v1, "After a quarter turn YZ");
}