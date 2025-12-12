/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:30:33 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/12 15:55:48 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void init_window(void)
{
	void	*mlx;
	t_list image;

	mlx = mlx_init();
	image.img = mlx_new_window(mlx, 1920, 1080, "FdF");
	mlx_loop(mlx);
}

char *read_map(char *map)
{
	char *full_map;
	char *gnl;
	char *gnl2;
	char *directory = ft_strjoin("test_maps/", map);
	int fd = open(directory, O_RDONLY);
	int len;

	len = 0;
	gnl = get_next_line(fd);
	gnl2 = get_next_line(fd);
	while (gnl)
	{
		len += ft_strlen(gnl);
		free(gnl);
		gnl = get_next_line(fd);
	}
	full_map = malloc(len + 1);
	len = 0;
	while (gnl2)
	{
		ft_memcpy(full_map, gnl2, ft_strlen(gnl2));
		free(gnl2);
		gnl2 = get_next_line(fd);
	}
	return (full_map[len] = 0, full_map);
}

t_data *fill_infos(char *map)
{
	t_data *datas;

	datas = malloc(sizeof(t_data));
	datas->map = read_map(map);
	return datas;
}

int main(int argc, char **argv)
{
	t_data	*datas;

	if (argc != 2)
		return 0;
	datas = fill_infos(argv[1]);
	printf("%s", datas->map);
	//init_window();
	return 0;
}
