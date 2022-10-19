#include "so_long.h"

int valid_ext(const char *str)
{
	size_t len;

	len = ft_strlen(str) - 4;
	return (ft_strncmp(str + len, ".ber", 5));
}

int check_size(t_map *map)
{
	int		fd;
	char	*line;

	fd = open(map->path, O_RDONLY);
	line = get_next_line(fd);
	map->width = ft_strlen(line);
	map->height = 0;
	while (line)
	{
		map->height++;
		if(map->width != ft_strlen(line))
			return(1);
		ft_freeptr((void *)line);
		line = get_next_line(fd);
	}
	close(fd);
}

int check_map(t_map *map)
{
	if(check_size(map))
		return (1);
}

int main(int argc, char **argv)
{
	t_data data;

	if (argc != 2)
		ft_printf("Error\nParams Wrong: %s\n", strerror(5));
	if (valid_ext(argv[1]))
		ft_printf("Error\nWrong Extension: %s\n", strerror(2));
	data.map.path = argv[1];
	if(check_map(&data.map))
		ft_printf("Error\nWrong Extension: %s\n", strerror(59));
	// data.window.mlx_ptr = mlx_init();
	// if (data.window.mlx_ptr == NULL)
	// 	return (-1);
	// data.window.mlx_win = mlx_new_window(data.window.mlx_ptr, (data.map.width * 8), (data.map.height * 8), "so long");
	// if (data.window.mlx_win == NULL)
	// {
	// 	free(data.window.mlx_win);
	// 	return (-1);
	// }
}
