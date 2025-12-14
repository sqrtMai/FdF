#include "fdf.h"

static int get_map_size(int fd)
{
	int len;
	char *gnl;

	gnl = get_next_line(fd, 0);
	len = 0;
	while (gnl)
	{
		len += ft_strlen(gnl);
		free(gnl);
		gnl = get_next_line(fd, 0);
	}
	close(fd);
	return len;
}

char *read_map(char *map)
{
	char *full_map;
	char *gnl;
	int fd;
	int len;

	len = 0;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Incorrect map"), exit(1), NULL);
	full_map = malloc(get_map_size(fd) + 1);
	fd = open(map, O_RDONLY);
	gnl = get_next_line(fd, 1);
	while (gnl)
	{
		ft_memcpy(&full_map[len], gnl, ft_strlen(gnl));
		len += ft_strlen(gnl);
		free(gnl);
		gnl = get_next_line(fd, 0);
	}
	close(fd);
	return (full_map[len] = 0, full_map);
}

int get_map_len(char *map)
{
	int i;
	int word;
	int in_word;

	i = 0;
	word = 0;
	if (map[i] == ' ')
		in_word = 0;
	else
		in_word = 1;
	while (map[i] && map[i] != '\n')
	{

		while (map[i] && map[i] != '\n' && map[i] == ' ')
			i++;
		if (map[i] && map[i] != '\n' && map[i] != ' ')
			word++;
		while (map[i] && map[i] != '\n'  && map[i] != ' ')
			i++;
	}
	return word;
}

int get_map_height(char *map)
{
	int i;
	int height;

	i = 0;
	height = 0;
	while (map[i])
	{
		if ((map[i] == '\n' && map[i + 1]) || !map[i])
			height++;
		i++;
	}
	return height + 1;
}

int check_valid_size(t_fdf *fdf, char *map)
{
	int i;
	int line_size;
	int next_line_size;

	i = 0;
	line_size = get_map_len(map);
	while (map[i])
	{
		if (map[i] == '\n' && map[i + 1])
		{
			next_line_size = get_map_len(&map[i + 1]);
			if (line_size != next_line_size)
			{
				free(fdf->map->map);
				free(fdf->map);
				ft_printf("wrong\n");
				exit(1);
			}
		}
		i++;
	}
	return 1;
}
