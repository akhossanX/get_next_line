/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:11:44 by akhossan          #+#    #+#             */
/*   Updated: 2019/04/13 23:08:30 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>

int		check_line(char *buff, char **line, char **static_line);

int		get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	static char	*static_line;
	int			bytes;
	char		*tmp;

	static_line = (char *)malloc(0);
	if (!line || !*line)
	{
		if(!(*line = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
			return (-1);
	}
	ft_bzero(buff, BUFF_SIZE + 1);
	ft_bzero(*line, BUFF_SIZE + 1);
	while ((bytes = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (check_line(buff, line, &static_line) == 1)
		{
			printf("byte: %d\n", bytes);
			printf("buff: %s\n", buff);
			printf("over: %s\n", static_line);
			return (1);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		free(tmp);
	}
	//printf("line inside gnl: %s\n", *line);
	return (bytes < 0 ? -1: 0);
}

int		check_line(char *buff, char **line, char **static_line)
{
	char	*tmp;
	char	*endl;

	/* A line has been read */
	if ((endl = ft_strchr(buff, '\n')) != NULL)
	{
		/* is '\n' found before the end of buff? */
		/* if so save the overflow to static line */ 
		//if (endl < buff + ft_strlen(buff) - 1)
		//{
		//	endl[0] = '\0';
		//	tmp = *static_line;
		//	*static_line = ft_strdup(endl + 1);
		//	free(tmp);
		//}
		/* copy the line string into *line */
		endl[0] = '\0';
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		/* copy the overflow to static_lin */
		tmp = *static_line;
		*static_line = ft_strdup(endl + 1);
		//printf("line inside chk: %s\n", *line);
		//printf("buff inside chk: %s\n", buff);
		free(tmp);
		return (1);
	}
	return (0);	
}

int		main(int ac, char **av)
{
	int		fd;
	char	*line;
	int		flag;

	if (ac != 2)
		exit(1);
	if ((fd = open(av[1], O_RDONLY)) < 0)
		exit(1);
	if ((flag = get_next_line(fd, &line)) > 0)
		printf("line: %s\n", line);
	close(fd);
}
