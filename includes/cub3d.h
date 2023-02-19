#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include "vector.h"
#include "camera.h"
#include "color.h"
#include "object.h"

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

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
	t_camera camera;
	void *mlx;
	void *window_ref;
	t_object *scene;
	t_textures textures;
	int time;
	t_data img;
	int screen_width;
	int screen_height;
} t_world;

void test_suite_vector();
void test_suite_camera();

#endif
