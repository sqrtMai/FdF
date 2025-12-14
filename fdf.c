#include "fdf.h"

// t_point project_iso(t_fdf *fdf, t_point source)
// {
// 	t_point screen;
// 	float a = 3.14 / 6;

//     screen.x = ((source.x - source.y) * cos(0.523599)) * fdf->zoom
//                + fdf->img.width / 2;
//     screen.y = ((source.x + source.y) * sin(0.523599) - source.z) * fdf->zoom
//                + fdf->img.height / 2;


// 	return screen;
// }

int main(int argc, char **argv)
{
	t_fdf fdf;
	char *map;
	char **split;

	if (argc != 2 || !argv[1])
		return 0;
	if ((ft_findstr(argv[1], ".fdf")) == 0)
		return (ft_printf("Wrong extension"), 1);
	init_datas(&fdf, argv[1]);
	return 0;
}
