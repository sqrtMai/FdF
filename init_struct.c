#include "fdf.h"

int init_zoom(t_fdf *fdf)
{
	if (fdf->map->map_len < 20)
		return 40;
	return 1;
}
void init_window(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, 1920, 1080, "FdF");
	fdf->img.img = mlx_new_image(fdf->mlx, 1920, 1080);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel, &fdf->img.line_length,
									&fdf->img.endian);
	fdf->img.width = 1920;
	fdf->img.height = 1080;
	fdf->zoom = init_zoom(fdf);
	mlx_hook(fdf->window, 2, 1L << 0, key_hook, fdf);
	mlx_hook(fdf->window, 17, 0, close_window, fdf);

	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img.img, 0, 0);
	mlx_loop(fdf->mlx);
}

int init_color(t_fdf *fdf, char *split)
{
	int i;

	i = 0;
	while (split[i] && split[i] != ',')
		i++;
	if (!split[i])
		return (0x00FFFFFF);
	if (split[i] && split[i + 3])
		return (ft_atoi_base(&split[i + 3], "0123456789ABCDEF"));
	//TODO implement invalid map if there is !split + 1;
}
static void put_datas_to_point(t_fdf *fdf, char **split)
{
	int i;
	int y;
	int z;

	i = 0;
	y = 0;
	z = 0;
	fdf->map->points = malloc(sizeof(t_point *) * fdf->map->map_height);
	while (i < fdf->map->map_height)
		fdf->map->points[i++] = malloc(sizeof(t_point) * (fdf->map->map_len));
	i = 0;
	while (split[z])
	{
		if (y == (fdf->map->map_len))
		{
			y = 0;
			i++;
		}
		fdf->map->points[i][y].z = ft_atoi(split[z]);
		fdf->map->points[i][y].x = y;
		fdf->map->points[i][y].y = i;
		fdf->map->points[i][y++].color = init_color(fdf, split[z++]);
	}
	free_everything((void **)split);
}

static void init_fdf_struct(t_fdf *fdf, char *map)
{
	fdf->map = malloc(sizeof(t_map));
	fdf->map->map = read_map(map);
	check_valid_size(fdf, fdf->map->map);
	fdf->map->map_height = get_map_height(fdf->map->map);
	fdf->map->map_len = get_map_len(fdf->map->map);
}
void init_datas(t_fdf *fdf, char *map)
{
	char **split;

	init_fdf_struct(fdf, map);
	split = ft_split(fdf->map->map, " \n");
	put_datas_to_point(fdf, split);
	//init_window(fdf);
}
