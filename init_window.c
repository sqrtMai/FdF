#include "fdf.h"

t_point project_iso(t_fdf *fdf, t_point source)
{
    t_point screen;
    float angle = 3.141592 / 9;
    float x_rot;
	float y_rot;
	float rot_angle = 4.7;

    x_rot = ((source.x * cos(rot_angle) - source.y * sin(rot_angle)) * fdf->zoom + fdf->img.width / 2);
    y_rot = ((source.x * sin(rot_angle) + source.y * cos(rot_angle)) * fdf->zoom + fdf->img.height / 2);

    screen.x = ((x_rot - y_rot) * cos(angle));
    screen.y = ((x_rot + y_rot) * sin(angle) - source.z);

    return screen;
}

void ft_put_pixel(t_fdf *fdf, int x, int y, int color)
{
    char *pxl;

    if (x >= 0 && x < fdf->img.width && y >= 0 && y < fdf->img.height)
    {
        pxl = fdf->img.addr + (y * fdf->img.line_length + x * (fdf->img.bits_per_pixel / 8));
        *(unsigned int *)pxl = color;
    }
}

void draw_map(t_fdf *fdf)
{
	int x;
	int y;
	t_point screen;

	x = 0;
	while (x < fdf->map->map_height)
	{
		y = 0;
		while (y < fdf->map->map_len)
		{
			screen = project_iso(fdf, fdf->map->points[x][y]);
			ft_put_pixel(fdf, screen.x, screen.y, fdf->map->points[x][y].color);
			y++;
		}
		x++;
	}
}
