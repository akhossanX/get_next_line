/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:03:34 by akhossan          #+#    #+#             */
/*   Updated: 2019/04/17 22:01:30 by abkh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define	ALLOC_LINE(line)		if(!(line = ft_strnew(0))) return (-1)
#define	ALLOC_OVERFLOW(over)	if(!(over = ft_strnew(BUFF_SIZE))) return (-1)

/*
** Joins s2 to s1 and frees the old s1
*/
void	ft_strjoinfree(char **s1, char *s2)
{
	char	*tmp;

	if (s1 && *s1 && s2)
	{
		tmp = *s1;
		*s1 = ft_strjoin(*s1, s2);
		ft_strdel(&tmp);
	}
}

/*
** Duplicates the string src into dst,
** and frees the old dst
*/
void	ft_strdupfree(char **dst, char *src)
{
	char	*tmp;

	if (dst && *dst && src)
	{
		tmp = *dst;
		*dst = ft_strdup(src);
		ft_strdel(&tmp);
	}
}

int		get_next_line(int fd, char **line)
{
	static char		*overflow;
	char			buff[BUFF_SIZE + 1];
	int				bytes;
	char			*endl;

	if (fd < 0 || !line)
		return (-1);
	ft_bzero(buff, BUFF_SIZE + 1);
	ALLOC_LINE(*line);
	ft_strclr(*line);
	if (!overflow)
		ALLOC_OVERFLOW(overflow);
	/* Is there overflow from previous reading ? */
	if (*overflow)
	{
		if ((endl = ft_strchr(overflow, '\n')))
		{
			/* Duplicate code here: DRY /!\ */
			endl[0] = 0;
			ft_strjoinfree(line, overflow); 
			ft_strdupfree(&overflow, endl + 1); 
			return (1);
		}
	}
	while ((bytes = read(fd, buff, BUFF_SIZE)) > 0 || (bytes == 0 && *overflow))
	{
		ft_strjoinfree(&overflow, buff);	
		if ((endl = ft_strchr(overflow, '\n')))
		{
			/* Duplicate code here: DRY /!\ */
			endl[0] = 0;
			ft_strjoinfree(line, overflow); 
			ft_strdupfree(&overflow, endl + 1); 
			return (1);
		}
		else
		{
			/* Join overflow with line */
			ft_strjoinfree(line, overflow);
			ft_strclr(buff);
			ft_strclr(overflow);
			//if (!bytes)
			//	return (1);
		}
	}
	if (bytes == 0 && **line)
		return (1);
	return (bytes < 0 ? -1: 0);
}

int		main(int ac, char **av)
{
	int		fd;
	char	*line;
	int		ret;

	if (ac != 2)
		exit(1);
	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		printf(">>[%s]<<\n", line);
	//printf(">>last[%d]read<<\n", ret);
	//printf(">>last[%s]read<<\n", line);
	return (0);
}
