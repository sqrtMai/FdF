#include "fdf.h"

t_point project_iso(t_fdf *fdf, t_point source)
{
	t_point screen;
	float a = 3.14 / 6;

    screen.x = ((source.x - source.y) * cos(0.523599)) * fdf->zoom
                + fdf->img.width / 2;
    screen.y = ((source.x + source.y) * sin(0.523599) - source.z) * fdf->zoom
                + fdf->img.height / 2;
	return (screen);
}


