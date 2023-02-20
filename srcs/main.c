#include <stdio.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>
#include "../includes/cub3d.h"

#define KEY_Q 113
#define KEY_D 100
#define KEY_Z 122
#define KEY_S 115
#define KEY_A 97
#define KEY_W 119

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

void exit_cub3d(t_world *world)
{
	if (!world)
		exit(0);

	if (world->window_ref && world->mlx)
	{
		// mlx_destroy_image(&world->mlx, &world->img.img);
		mlx_destroy_window(world->mlx, world->window_ref);
	}
	if (world->mlx)
	{
		mlx_destroy_display(world->mlx);
		mlx_loop_end(world->mlx);
		free(world->mlx);
	}
	object_free(world->scene);
	exit(0);
}

int monitor_input(int key, t_world *world)
{
	double v = 0.15;
	double rot_rad = M_PI / 20;
	if (key == KEY_Z)
		camera_move(&world->camera, v, 0);
	if (key == KEY_S)
		camera_move(&world->camera, -v, 0);
	if (key == KEY_Q)
		camera_move(&world->camera, 0, v);
	if (key == KEY_D)
		camera_move(&world->camera, 0, -v);
	if (key == XK_Left)
		camera_turn(&world->camera, rot_rad);
	if (key == XK_Right)
		camera_turn(&world->camera, -rot_rad);
	if (key == XK_Escape)
		exit_cub3d(world);
	return (0);
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

void add_cube(t_object *cubes, int x, int y, int type_cube, int *map, int x_min, int x_max, int y_min, int y_max, int w, int h)
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
	if (x >= (x_max - 1) || map[(h - 1 - y) * w + x + 1] == 0)
		cubes_add_face_x1(cubes, p_x + 1, p_y, p_y + 1, 0, 1, &color_face1);
	if (x > x_min || map[(h - 1 - y) * w + x - 1] == 0)
		cubes_add_face_xm1(cubes, p_x, p_y, p_y + 1, 0, 1, &color_face1);
	if (y < (y_max - 1) || map[(h - 1 - y - 1) * w + x] == 0)
		cubes_add_face_y1(cubes, p_y + 1, p_x, p_x + 1, 0, 1, &color_face2);
	if (y > y_min || map[(h - y) * w + x] == 0)
		cubes_add_face_ym1(cubes, p_y, p_x, p_x + 1, 0, 1, &color_face2);
}

int loop(t_world *world)
{
	int x, y;
	int color;
	time_t seconds;
	float fps = 0;

	seconds = time(NULL);
	time_t elapsed;
	elapsed = seconds - world->start_time;
	if (seconds > world->start_time)
		fps = ((float)world->frames) / ((float)(elapsed));
	if (elapsed > 0 && elapsed % 5 == 0)
	{
		printf("Frames: %ld, Time: %ld, FPS: %f \n", world->frames, elapsed, fps);
		world->start_time = seconds;
		world->frames = 0;
	}
	world->frames += 1;

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
	world.frames = 0;
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

	t_color color_face1, color_face2;
	color_set(&color_face1, 140, 0, 0);
	color_set(&color_face2, 0, 140, 0);
	int slice = 2;
	int w, h;
	w = mapWidth / slice;
	h = mapHeight / slice;
	t_object **area_cubes;
	area_cubes = malloc(slice * slice * sizeof(t_object));
	for (int i = 0; i < slice * slice; i++)
	{
		area_cubes[i] = object_new_cubes(mapWidth * mapHeight / (slice * slice));
	}
	for (int ac = 0; ac < slice; ac++)
	{
		for (int ar = 0; ar < slice; ar++)
		{
			for (int c = ac * w; c < (ac + 1) * w; c++)
			{
				for (int r = ar * h; r < (ar + 1) * h; r++)
					add_cube(area_cubes[ac + ar * slice], c, r, worldMap[mapHeight - 1 - r][c],
							 (int *)worldMap, ac * w, (ac + 1) * w, ar * h, (ar + 1) * h, mapWidth, mapHeight);
			}
		}
	}

	printf("Sky\n");
	object_print(sky);
	printf("Floor\n");
	object_print(floor);

	world.scene = object_new_container(2 + slice * slice);
	printf("Container\n");
	object_print(world.scene);
	printf("Cubes\n");
	for (int i = 0; i < slice * slice; i++)
	{
		object_print(area_cubes[i]);
		container_add(world.scene, area_cubes[i]);
	}
	object_print(world.scene);
	container_add(world.scene, floor);
	object_print(world.scene);
	container_add(world.scene, sky);
	object_print(world.scene);
	free(area_cubes);

	camera_set_origin(&world.camera, 4, 11, 0.5);
	camera_set_direction(&world.camera, 1, 1, 0);
	camera_set_focal(&world.camera, 0.2);
	camera_set_real_width(&world.camera, 0.4);
	camera_print(&world.camera);

	world.mlx = mlx_init();
	world.window_ref = mlx_new_window(world.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3Dom");
	world.img.img = mlx_new_image(world.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	world.img.addr = mlx_get_data_addr(world.img.img, &world.img.bits_per_pixel, &world.img.line_length, &world.img.endian);
	world.start_time = time(NULL);
	mlx_loop_hook(world.mlx, &loop, (void *)&world);
	//	mlx_key_hook(world.window_ref, &monitor_input, &world);
	mlx_hook(world.window_ref, KeyPress, KeyPressMask, &monitor_input, &world);

	mlx_loop(world.mlx);

	return 0;
}

int main2(void)
{
	test_suite_camera();
	return 0;
}