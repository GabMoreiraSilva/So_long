#include "so_long.h"

int	valid_ext(const char *str)
{
	size_t	len;

	len = ft_strlen(str) - 4;
	return (ft_strncmp(str + len, ".ber", 5));
}

int	check_size(t_map *map)
{
	int		fd;
	char	*line;

	fd = open(map->path, O_RDONLY);
	line = get_next_line(fd);
	map->width = ft_strlen(line) - 1;
	map->height = 0;
	while (line)
	{
		map->height++;
		if(map->width != ft_strlen(line) - 1)
			return(1);
		ft_freeptr((void *)line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	get_map(t_map *map)
{
	int		row;
	int		column;
	int		fd;
	char	*line;

	fd = open(map->path, O_RDONLY);
	line = get_next_line(fd);
	column = 0;
	row = 0;
	while (line)
	{
		column = 0;
		while(column <= map->width)
		{
			map->map[row][column] = line[column];
			column++;
		}
		ft_freeptr((void *)line);
		line = get_next_line(fd);
		row++;
	}
}

void	free_map(t_map *map)
{
	int	row;

	row = 0;
	while (row < map->height)
	{
		ft_freeptr(map->map[row]);
		row++;
	}
	ft_freeptr(map->map);
}

void	create_map(t_map *map)
{
	int	height;

	map->map = malloc(sizeof(char*) * map->height + 1);
	if(!map->map)
		return ;
	map->map[map->height] = NULL;
	height = 0;
	while(height < map->height)
	{
		map->map[height] = malloc (sizeof (char) * map->height);
		height++;
	}
}

int check_walls(t_map *map)
{
	int	row;
	int	column;

	row = 0;
	column = 0;
	while (row < map->height)
	{
		while (column < map->width)
		{
			if ((map->map[row][column] != '1') || (map->map[row][0] != '1'))
				return (1);
			if (column < map->width)
				column++;
		}
		column--;
		row++;
	}
	row--;
	column = 0;
	while (column < map->width)
	{
		if (map->map[row][column] != '1')
			return (1);
		column++;
	}
	return(0);
}

int count_elements(t_map *map)
{
	int	column;
	int	row;

	row = 0;
	while(map->map[row])
	{
		column = 0;
		while (map->map[row][column] != '\n')
		{
			if (map->map[row][column] == 'P')
			{
				map->infos_map.player_number++;
				map->infos_map.player_position[0] = row;
				map->infos_map.player_position[1] = column;
			}
			if (map->map[row][column] == 'C')
				map->infos_map.collectible++;
			if (map->map[row][column] == 'E')
				map->infos_map.exits++;
			if ((map->map[row][column] != 'E') && (map->map[row][column] != 'C')
				&& (map->map[row][column] != 'P') && (map->map[row][column] != '1')
				&& (map->map[row][column] != '0'))
				return (1);
			column++;
		}
		row++;
	}
	return (0);
}

int check_elements(t_map *map)
{
	if((map->infos_map.player_number != 1) || (map->infos_map.exits != 1) || (map->infos_map.collectible <= 0))
		return (1);
	return (0);
}

int	init_var_infos_map(t_map *map)
{
	map->infos_map.player_number = 0;
	map->infos_map.collectible = 0;
	map->infos_map.exits = 0;
	if(count_elements(map))
	{
		free_map(map);
		return (1);
	}
	if(check_elements(map))
	{
		free_map(map);
		return (1);
	}
	return(0);
}

int	check_create_map(t_map *map)
{
	check_size(map);
	create_map(map);
	if (!map->map)
		return (1);
	get_map(map);
	if(check_walls(map))
	{
		free_map(map);
		return (1);
	}
	if(init_var_infos_map(map))
		return (1);
}

void	place_sprites(t_window *window, t_sprites *sprites)
{
	int number;
	int *size;

	number = 64;
	size = &number;
	sprites->wall = mlx_xpm_file_to_image(window->mlx_ptr,
			"sprites/Wall.xpm", size, size);
	sprites->collectible = mlx_xpm_file_to_image(window->mlx_ptr,
			"sprites/Collect.xpm", size, size);
	sprites->exits[0] = mlx_xpm_file_to_image(window->mlx_ptr,
			"sprites/exit_close.xpm", size, size);
	sprites->exits[1] = mlx_xpm_file_to_image(window->mlx_ptr,
			"sprites/exit_open.xpm", size, size);
	sprites->floor = mlx_xpm_file_to_image(window->mlx_ptr,
			"sprites/floor.xpm", size, size);
	sprites->player = mlx_xpm_file_to_image(window->mlx_ptr,
			"sprites/mage.xpm", size, size);
}

void	sprite_print(t_window *window, t_map *map, t_sprites *sprites)
{
	if (map->map[map->pos_y][map->pos_x] == '1')
		mlx_put_image_to_window(window->mlx_ptr, window->mlx_win, sprites->wall,
		window->window_x, window->window_y);
	if (map->map[map->pos_y][map->pos_x] == '0')
		mlx_put_image_to_window(window->mlx_ptr, window->mlx_win, sprites->floor,
		window->window_x, window->window_y);
	if (map->map[map->pos_y][map->pos_x] == 'C')
		mlx_put_image_to_window(window->mlx_ptr, window->mlx_win, sprites->collectible,
		window->window_x, window->window_y);
	if (map->map[map->pos_y][map->pos_x] == 'P')
		mlx_put_image_to_window(window->mlx_ptr, window->mlx_win, sprites->player,
		window->window_x, window->window_y);
	if (map->map[map->pos_y][map->pos_x] == 'E')
		mlx_put_image_to_window(window->mlx_ptr, window->mlx_win, sprites->exits[0],
		window->window_x, window->window_y);
}

void	render_map(t_window *window, t_map *map, t_sprites *sprites)
{
	map->pos_x = 0;
	map->pos_y = 0;
	while (window->window_y < (map->height * 64))
	{
		window->window_x = 0;
		map->pos_x = 0;
		while (window->window_x < (map->width * 64))
		{	
			sprite_print(window, map, sprites);
			window->window_x += 64;
			map->pos_x++;
			
		}		
		window->window_y += 64;
		map->pos_y++;
	}
}

int	action_loop(t_data *data)
{
	
	render_map(&data->window, &data->map, &data->sprites);
	return (0);
}

int	init_game(t_data *data)
{
	data->window.mlx_ptr = mlx_init();
	if (data->window.mlx_ptr == NULL)
		return (1);
	data->window.mlx_win = mlx_new_window(data->window.mlx_ptr, (data->map.width * 64), (data->map.height * 64) + 1, "so long");
	if (data->window.mlx_win == NULL)
	{
		ft_freeptr(data->window.mlx_win);
		return (1);
	}
	place_sprites(&data->window, &data->sprites);
	mlx_loop_hook(data->window.mlx_ptr, action_loop, (void *)data);
	mlx_loop(data->window.mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_printf("Error\nParams Wrong: %s\n", strerror(5)));
	if (valid_ext(argv[1]))
		return (ft_printf("Error\nWrong Extension: %s\n", strerror(2)));
	data.map.path = argv[1];
	if(check_create_map(&data.map))
		return (ft_printf("Error\nWrong Extension: %s\n", strerror(59)));
	init_game(&data);
}
