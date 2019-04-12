/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:11:44 by akhossan          #+#    #+#             */
/*   Updated: 2019/04/12 22:53:02 by akhossan         ###   ########.fr       */
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
	while ((bytes = read(fd, buff, BUFF_SIZE)) > 0)
	{
		printf("buff inside gnl : %s\n", buff);
		if (check_line(buff, line, &static_line) == 1)
			return (1);
		tmp = static_line;
		static_line = ft_strjoin(static_line, buff);
		printf("overflow buffer : %s\n", static_line);
		free(tmp);
	}
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
		if (endl < buff + ft_strlen(buff) - 1)
		{
			tmp = *static_line;
			*static_line = ft_strdup(endl + 1);
			free(tmp);
		}
		/* copy the line string into *line */
		endl[0] = '\0';
		tmp = *line;
		*line = ft_strdup(buff);
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
	{
		printf("Successful reading performed\n");
		printf("%s", line);
	}
}
