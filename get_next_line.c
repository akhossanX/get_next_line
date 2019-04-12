/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:03:34 by akhossan          #+#    #+#             */
/*   Updated: 2019/04/10 18:19:22 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"
#include <fcntl.h>
#include <unistd.h>


void	memdisp(void *mem, int size)
{
	int		i;

	i = 0;
	while (i < size)
		ft_putchar(((const char *)mem)[i++]);
}

int		get_next_line(int fd, char **line)
{
	char			*buff;
	int				bytes;
	char			*tmp;
	int				i;

	if (!(*line = ft_strnew(BUFF_SIZE)) || fd < 0)
			return (-1);
	buff = ft_strnew(BUFF_SIZE);
	ft_memset(*line, 0, ft_strlen(*line));
	tmp = NULL;
	bytes = 1;
	while (bytes > 0)
	{
		i = 0;
		while ((bytes = read(fd, &buff[i], BUFF_SIZE)) > 0 && i < BUFF_SIZE  && buff[i] != '\n')
			i++;	
		if (bytes == 0)
			break ;
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		ft_memdel((void **)(&tmp));
		if (buff[i] == '\n')
		{
			tmp = *line;
			*line = ft_strsplit(*line, '\n')[0];
			ft_memdel((void **)(&tmp));
			break ;
		}
		ft_memset(buff, 0, BUFF_SIZE);
	}
	ft_memdel((void **)(&buff));
	if (bytes == 0)
		return (0);
	if (bytes == -1)
		return (-1);
	return (1);
}
/*
int		main(int ac, char **av)
{
	char	*line = ft_strnew(1);
	if (ac != 2)
		exit(1);	
	int fd = open(av[1], O_RDONLY);
	if (fd <= 0)
	{
		printf("Invalid file\n");
		exit(1);
	}
	//get_next_line(fd, &line);
	//if (!line)
	//	printf("NULL POINTER RETURNED\n");
	//printf("%s\n", line);
	//get_next_line(fd, &line);
	//if (!line)
	//	printf("NULL POINTER RETURNED\n");
	//printf("%s\n", line);
	while (get_next_line(fd, &line) > 0)
		printf("%s\n", line);
	memdisp(line, 16);
	close(fd);
	free(line);
}
*/
