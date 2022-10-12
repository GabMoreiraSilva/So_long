#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include "./libft/libft.h"

typedef struct s_img{
	int width;
	int height;
	char **matrix;
	char *path;
	
	void *mlx_ptr;
	void *mlx_win;
}	t_img;

#endif