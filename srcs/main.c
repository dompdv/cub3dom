#include <stdio.h>
#include "../includes/cub3d.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_vertical_line(t_data *data, int x, int draw_start, int draw_end, int color)
{
	int y;
	y = draw_start;
	while (y < draw_end)
	{
		my_mlx_pixel_put(data, x, y, color);
		y++;
	}
}

void cast_ray(t_hit *hit, t_vect *eye, t_vect *dir, t_world *world)
{
	double dist_min; // Distance [eye,screen]
	t_vect dir_n;	 // Normalized direction vector

	dist_min = vector_norm(dir);
	vector_setv(&dir_n, dir);
	vector_normalize(&dir_n);
	object_cast_ray(world->scene, hit, eye, &dir_n, dist_min);
}

void add_cube(t_object *cubes, int x, int y, int type_cube)
{
	if (type_cube == 0)
		return;
	t_color color_face1, color_face2;
	if (type_cube == 1)
	{
		color_set(&color_face1, 140, 0, 0);
		color_set(&color_face2, 120, 0, 0);
	}
	if (type_cube == 2)
	{
		color_set(&color_face1, 0, 140, 0);
		color_set(&color_face2, 0, 120, 0);
	}
	if (type_cube == 3)
	{
		color_set(&color_face1, 0, 0, 140);
		color_set(&color_face2, 0, 0, 120);
	}
	if (type_cube == 4 || type_cube == 5)
	{
		color_set(&color_face1, type_cube * 50, type_cube * 40, type_cube * 40);
		color_set(&color_face2, type_cube * 50, type_cube * 40, type_cube * 40);
	}
	double p_x = (double)x;
	double p_y = (double)y;
	cubes_add_face_x1(cubes, p_x + 1, p_y, p_y + 1, 0, 1, &color_face1);
	cubes_add_face_xm1(cubes, p_x, p_y, p_y + 1, 0, 1, &color_face1);
	cubes_add_face_y1(cubes, p_y + 1, p_x, p_x + 1, 0, 1, &color_face2);
	cubes_add_face_ym1(cubes, p_y, p_x, p_x + 1, 0, 1, &color_face2);
}

int loop(t_world *world)
{
	int x, y;
	int color;

	printf("loop: %d\n", world->time);
	world->time += 1;
	for (x = 0; x < world->screen_width; x++)
	{
		for (y = 0; y < world->screen_height; y++)
		{
			t_vect ray;
			t_hit hit;
			hit_nothing(&hit);
			color = 0;
			camera_ray(&ray, &world->camera, x, y, world->screen_width, world->screen_height);
			cast_ray(&hit, &world->camera.origin, &ray, world);
			if (hit_has_hit(&hit))
				color = color_to_int(&hit.color);
			my_mlx_pixel_put(&world->img, x, world->screen_height - 1 - y, color);
		}
	}
	mlx_put_image_to_window(world->mlx, world->window_ref, world->img.img, 0, 0);
	return (0);
}
int main(void)
{
	t_world world;
	world.time = 0;
	world.screen_width = SCREEN_WIDTH;
	world.screen_height = SCREEN_HEIGHT;

	t_object *floor;
	t_color floor_color1, floor_color2;

	color_set(&floor_color1, 200, 200, 230);
	color_set(&floor_color2, 180, 180, 210);
	floor = object_new_floor(floor_color1, floor_color2);

	t_object *sky;
	t_color azimut, horizon;
	color_set(&horizon, 200, 200, 200);
	color_set(&azimut, 0, 0, 150);
	sky = object_new_sky(horizon, azimut);

	t_object *cubes;
	t_color color_face1, color_face2;
	color_set(&color_face1, 140, 0, 0);
	color_set(&color_face2, 0, 140, 0);
	cubes = object_new_cubes(mapWidth * mapHeight);
	for (int c = 0; c < mapWidth; c++)
	{
		for (int r = 0; r < mapHeight; r++)
		{
			add_cube(cubes, c, r, worldMap[mapHeight - 1 - r][c]);
		}
	}

	world.scene = object_new_container(3);
	container_add(world.scene, floor);
	container_add(world.scene, cubes);
	container_add(world.scene, sky);

	camera_set_origin(&world.camera, 4, 11, 0.5);
	camera_set_direction(&world.camera, 1, 1, 0);
	camera_set_focal(&world.camera, 0.2);
	camera_set_real_width(&world.camera, 0.4);
	camera_print(&world.camera);

	world.mlx = mlx_init();
	world.window_ref = mlx_new_window(world.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3Dom");
	world.img.img = mlx_new_image(world.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	world.img.addr = mlx_get_data_addr(world.img.img, &world.img.bits_per_pixel, &world.img.line_length, &world.img.endian);

	mlx_loop_hook(world.mlx, &loop, (void *)&world);
	mlx_loop(world.mlx);

	object_free(world.scene);
	return 0;
}

int main2(void)
{
	test_suite_camera();
	return 0;
}