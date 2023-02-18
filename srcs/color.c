#include <stdio.h>
#include "../includes/color.h"

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

int color_to_int(t_color *c)
{
    return create_trgb(0, c->r, c->g, c->b);
}

char get_color_name(int color)
{
    int r;
    int g;
    int b;

    r = (color >> 16 & 0xFF);
    g = (color >> 8 & 0xFF);
    b = (color & 0xFF);
    if (r == 255 && g == 0 && b == 0)
        return ('R');
    if (r > 0 && g == 0 && b == 0)
        return ('r');
    if (r == 0 && g == 255 && b == 0)
        return ('G');
    if (r == 0 && g > 0 && b == 0)
        return ('g');
    if (r == 0 && g == 0 && b == 255)
        return ('B');
    if (r == 0 && g == 0 && b > 0)
        return ('b');
    if (r == 255 && g == 255 && b == 255)
        return ('W');
    if (r > 0 && g > 0 && b > 0)
        return ('w');
    return ('y');
}

int get_darker(int color)
{
    int r;
    int g;
    int b;

    r = (color >> 16 & 0xFF) / 2;
    g = (color >> 8 & 0xFF) / 2;
    b = (color & 0xFF) / 2;
    return (create_trgb(0, r, g, b));
}

void color_set(t_color *c, int r, int g, int b)
{
    c->r = r;
    c->g = g;
    c->b = b;
}

void color_setc(t_color *c, t_color *c2)
{
    c->r = c2->r;
    c->g = c2->g;
    c->b = c2->b;
}
double clamp(double t)
{
    if (t < 0)
        return 0;
    if (t > 1)
        return 1;
    return t;
}
void color_gradient(t_color *c, t_color *c2, double t)
{
    t = clamp(t);
    c->r = (int)(t * (double)c->r + (1 - t) * (double)c2->r);
    c->g = (int)(t * (double)c->g + (1 - t) * (double)c2->g);
    c->b = (int)(t * (double)c->b + (1 - t) * (double)c2->b);
}

void color_print(t_color *c)
{
    printf("rgb=(%d,%d,%d)\n", c->r, c->g, c->b);
}
