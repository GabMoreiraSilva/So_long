#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include "./libft/libft.h"

typedef struct s_img{
	int width;
	int height;
	int **matrix;
	
	void *mlx_ptr;
	void *mlx_win;
}	t_img;

#endif