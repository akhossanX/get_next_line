#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include "libft.h"

int		main(int ac, char **av)
{
	int		fd1;
	int		fd2;
	int		fd3;
	int		fd4;
	char	*line;

	if (ac != 5)
		exit(1);
	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[2], O_RDONLY);
	fd3 = open(av[3], O_RDONLY);
	fd4 = open(av[4], O_RDONLY);
	//while ((ret = get_next_line(fd, &line)) > 0)
	//{
	//	printf("%s\n", line);
	//	free(line);
	//}
	get_next_line(fd1, &line);
	printf("fd1: %s\n", line);
	ft_strdel(&line);
	get_next_line(fd2, &line);
	printf("fd2: %s\n", line);
	ft_strdel(&line);
	get_next_line(fd1, &line);
	printf("fd1: %s\n", line);
	ft_strdel(&line);
	get_next_line(fd3, &line);
	printf("fd3: %s\n", line);
	ft_strdel(&line);
	get_next_line(fd4, &line);
	printf("fd4: %s\n", line);
	ft_strdel(&line);
	while (get_next_line(fd4, &line) > 0)
	{
		printf("fd4: %s\n", line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (0);
}

