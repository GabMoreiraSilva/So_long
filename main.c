#include "so_long.h"

int main(int argc, char **argv)
{
	t_data data;

	data.map.path = argv[1];
	check_map(data.map);
	data.window.mlx_ptr = mlx_init();
	if (data.window.mlx_ptr == NULL)
		return (-1);
	data.window.mlx_win = mlx_new_window(data.window.mlx_ptr, (data.map.width * 8), (data.map.height * 8), "so long");
	if (data.window.mlx_win == NULL)
	{
		free(data.window.mlx_win);
		return (-1);
	}
}
