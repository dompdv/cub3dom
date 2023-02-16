#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include "vector.h"
#include "camera.h"

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_window
{
	void *reference;
	t_vect size;
} t_window;

typedef struct s_textures
{
	int **north;
	int **south;
	int **east;
	int **west;
	t_color floor;
	t_color ceiling;
} t_textures;

typedef struct s_world
{
	void *mlx;
	t_window window;
	t_vect size;
	int **map;
	t_camera camera;
	t_textures textures;
} t_world;

void test_suite_vector();
void test_suite_camera();

#endif
