#include "includes/fdf.h"

void	getsize(t_img *data, char *path)
{
	int fd;
	char *line;
	char **splited;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	splited = ft_split(line,' ');
	data->width = ft_matrixlen(splited);
	data->height = 0;
	while(line)
	{
		data->height++;
		ft_freeptr(line);
		line = get_next_line(fd);
	}
	ft_freearray(splited);
	close(fd);
}

int	**ft_creatematrix(t_img data)
{
	int		column;
	int		**line;

	line = malloc ((data.height + 1) * sizeof (int *));
	column = 0;
	line[data.height] = NULL;
	while (line[column])
	{
		line[column] = malloc (sizeof (int) * data.width);
		column++;
	}
	return (line);
}

void	fillmatrix(t_img *data, char *path)
{
	int fd;
	char *line;
	char **splited;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	splited = ft_split(line, ' ');
	while(line)
	{
		data->height++;
		ft_freeptr(line);
		line = get_next_line(fd);
	}
}

int main(int argc, char **argv)
{
	t_img data;
	char *path;

	path = argv[1];
	ft_getsize(&data, path);
	data->matrix = ft_creatematrix(data);
	ft_fillmatrix(&data, path);
}
