/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:11:44 by akhossan          #+#    #+#             */
/*   Updated: 2019/04/16 15:01:20 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int		check_line(char *buff, char **line, char **static_line);

int		get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	static char	*static_line = NULL;
	int			bytes;
	char		*tmp;

	if (!static_line)
		static_line = (char *)malloc(0);
	//if (!*line)
		//if(!(*line = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
	if (!(*line = ft_strdup(static_line)))
			return (-1);
	ft_bzero(buff, BUFF_SIZE + 1);
	while ((bytes = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (check_line(buff, line, &static_line) == 1)
			return (1);
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		free(tmp);
	}
	if (bytes == 0)
	{
		printf("end buff:[%s]", buff);
		printf("end line:[%s]", *line);
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		free(tmp);
		return (0);
	}
	return (-1);
}

int		check_line(char *buff, char **line, char **static_line)
{
	char	*tmp;
	char	*endl;

	/* A line has been read */
	if ((endl = ft_strchr(buff, '\n')))
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
		//printf("over: [%s]", *static_line);
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
	int		i = 1;

	if (ac != 2)
		exit(1);
	line = NULL;
	if ((fd = open(av[1], O_RDONLY)) < 0)
		exit(1);
	flag = 1;
	while (flag > 0)
	{
		flag = get_next_line(fd, &line);
		printf("line%d:[%s]", i++, line);
	}
	close(fd);
}
