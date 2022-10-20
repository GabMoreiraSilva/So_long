#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <math.h>
#include <string.h>
# include "./libft/libft.h"

typedef struct s_window
{	
	void *mlx_ptr;
	void *mlx_win;
}	t_window;

typedef struct s_elements
{
	int player_position[2];
	int player_number;
	int collectible;
	int exits;
} t_elements;

typedef struct s_map
{
	int width;
	int height;
	char *path;
	char **map;
	t_elements infos_map;
}	t_map;

typedef struct s_data
{
	t_window window;
	t_map map;
}	t_data;


#endif