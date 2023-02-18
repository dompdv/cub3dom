#ifndef COLOR_H
#define COLOR_H

typedef struct s_color
{
    int r;
    int g;
    int b;
} t_color;

void color_set(t_color *c, int r, int g, int b);
void color_setc(t_color *c, t_color *c2);
int color_to_int(t_color *c);

#endif
