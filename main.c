#include "fdf.h"

int ft_hextodc(char *hex)
{
	int	exp;
	int	dec;
	int	index;

	exp = 0;
	dec = 0;
	index = ft_strlen(hex);
	while(index >= 0)
	{
		if (hex[index] >= '0' && hex[index] <= '9')
			dec += ((hex[index] - '0') * pow(16, exp));
		else
			dec += ((hex[index] - 'a' + 10) * pow(16, exp));
		exp++;
		index--;
	}
	return (dec);
}

void ft_getsize(t_img *data, char *path)
{
	int		fd;
	char	*line;
	char	**splited;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	splited = ft_split(line, ' ');
	data->width = ft_matrixlen((void **)splited);
	data->height = 0;
	while (line)
	{
		data->height++;
		ft_freeptr((void *)line);
		line = get_next_line(fd);
	}
	ft_freearray((void **)splited);
	close(fd);
}

char **ft_creatematrix(t_img data)
{
	int		column;
	int		fd;
	char	row;
	char	**line;

	if (data.width < 1)
		return (NULL);
	line = malloc(sizeof(*line) * data.width + 1);
	if (!line)
		return (NULL);
	column = 0;
	fd = open(data.path, O_RDONLY);
	while (column <= data.height)
	{
		line[column] = get_next_line(fd);
		column++;
	}
	close(fd);
	return (line);
}

int main(int argc, char **argv)
{
	t_img data;

	data.path = argv[1];
	ft_getsize(&data, data.path);
	data.matrix = ft_creatematrix(data);
	int x = 0;
	while(data.matrix[x])
	{
		printf("%s", data.matrix[x]);
		x++;
	}
}
