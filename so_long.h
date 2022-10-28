#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <math.h>
#include <string.h>
# include "./libft/libft.h"
# include "minilibx-linux/mlx.h"

typedef struct s_window
{	
	void *mlx_ptr;
	void *mlx_win;
	int window_x;
	int window_y;
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
	int pos_x;
	int pos_y;
	char *path;
	char **map;
	t_elements infos_map;
}	t_map;

typedef struct s_sprites
{
	void *player;
	void *collectible;
	void *exits[2];
	void *wall;
	void *floor;
}	t_sprites;


typedef struct s_data
{
	t_window window;
	t_map map;
	t_sprites sprites;
}	t_data;


#endif