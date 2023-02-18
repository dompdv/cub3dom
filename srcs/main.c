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
int main(void)
{
	t_display display;
	t_data img;
	t_world world;
	int x, y, color;

	world.map = (int **)worldMap;

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
	t_color color_face1;
	color_set(&color_face1, 140, 0, 0);
	cubes = object_new_cubes(10);
	cubes_add_face_x1(cubes, -2, 1, 2, 0, 10, &color_face1);

	world.scene = object_new_container(3);
	container_add(world.scene, floor);
	container_add(world.scene, cubes);
	container_add(world.scene, sky);

	camera_set_origin(&world.camera, 0, 0, 0.5);
	camera_set_direction(&world.camera, -1, 0, 0);
	camera_set_focal(&world.camera, 0.2);
	camera_set_real_width(&world.camera, 0.4);
	camera_print(&world.camera);

	display.mlx = mlx_init();
	display.window.reference = mlx_new_window(display.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3Dom");
	img.img = mlx_new_image(display.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (x = 0; x < SCREEN_WIDTH; x++)
	{
		for (y = 0; y < SCREEN_HEIGHT; y++)
		{
			t_vect ray;
			t_hit hit;
			color = 0;
			camera_ray(&ray, &world.camera, x, y, SCREEN_WIDTH, SCREEN_HEIGHT);
			cast_ray(&hit, &world.camera.origin, &ray, &world);
			if (hit_has_hit(&hit))
				color = color_to_int(&hit.color);
			my_mlx_pixel_put(&img, x, SCREEN_HEIGHT - 1 - y, color);
		}
	}
	//	draw_vertical_line(&img, x, draw_start, draw_stop, color);
	mlx_put_image_to_window(display.mlx, display.window.reference, img.img, 0, 0);
	mlx_loop(display.mlx);

	object_free(world.scene);
	return 0;
}

int main2(void)
{
	test_suite_camera();
	return 0;
}