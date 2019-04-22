/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:03:34 by akhossan          #+#    #+#             */
/*   Updated: 2019/04/22 14:42:59 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define ALLOC_LINE(line)		if(!(line = ft_strnew(0))) return (-1)
#define ALLOC_OVERFLOW(over)	if(!(over = ft_strnew(BUFF_SIZE))) return (-1)
#define ALLOC_BUFF(buff)		if(!(buff = ft_strnew(BUFF_SIZE))) return (-1)

int			ft_indexof(int *arr, int fd_val, size_t size);

/*
** Joins s2 to s1 and frees the old s1
*/

static void	ft_strjoinfree(char **s1, char *s2)
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

static void	ft_strdupfree(char **dst, char *src)
{
	char	*tmp;

	if (dst && *dst && src)
	{
		tmp = *dst;
		*dst = ft_strdup(src);
		ft_strdel(&tmp);
	}
}

/*
** Joins the line form previous overflow, to first param
** then update overflow from endl up to the end of overflow
*/

static void	save_line(char **line, char **overflow, char *endl)
{
	endl[0] = 0;
	ft_strjoinfree(line, *overflow);
	ft_strdupfree(overflow, endl + 1);
}

/*
** Reads a line and stores it to line arg
** if there is overflow from previous reading
** it's taken into consideration by joining it with line
*/

static int	read_line(int fd, char **buff, char **line, char **overflow)
{
	int		flag;
	char	*endl;

	while ((flag = read(fd, *buff, BUFF_SIZE)) > 0 || (flag == 0 && **overflow))
	{
		ft_strjoinfree(overflow, *buff);
		if ((endl = ft_strchr(*overflow, '\n')))
		{
			save_line(line, overflow, endl);
			ft_strdel(buff);
			return (1);
		}
		else
		{
			ft_strjoinfree(line, *overflow);
			ft_strclr(*buff);
			ft_strclr(*overflow);
		}
	}
	if (!**overflow)
		ft_strdel(overflow);
	ft_strdel(buff);
	if (flag == 0 && **line)
		return (1);
	return (flag < 0 ? -1 : 0);
}

/* TODO: MOVE TO LIBFT */
void		*ft_realloc(void *mem, size_t old_size, size_t new_size)
{
	void	*new;

	if (new_size == 0)
	{
		ft_memdel(mem);
		return (NULL);
	}
	else if (!mem)
		return (ft_memalloc(new_size));
	else if (new_size <= old_size)
		return (mem);
	else
	{
		new = ft_memalloc(new_size);
		if (new)
		{
			ft_memcpy(new, mem, old_size);
			ft_memdel(mem);
		}
	}
	return (new);
}

/* TODO: MOVE TO LIBFT */
t_filed		*ft_fdinit(int *fds, size_t len)
{
	t_filed		*fd;

	if (!(fd = ft_memalloc(sizeof(t_filed))))
		return (NULL);
	if (!fds || len == 0)
	{
		fd->fd_arr = NULL;
		fd->overflow = (char **)ft_memalloc(sizeof(char *));
	}
	else
		ft_memcpy(fd->fd_arr, fds, sizeof(int) * len);
	fd->size = len;	
	return (fd);
}

int			get_next_line(int fd, char **line)
{
	static t_filed	*fds = NULL;
	char			*buff;
	char			*endl;
	int				fd_index;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (!fds)
		fds = ft_fdinit(NULL, 0);
	/* Is fd already there? */
	/* if not just add it   */
	if (ft_indexof(fds->fd_arr, fd, fds->size) == -1)
	{
		fds->fd_arr = ft_realloc((void *)fds->fd_arr, fds->size, fds->size + 1);
		fds->fd_arr[fds->size] = fd;
		fds->size++;
	}
	fd_index = ft_indexof(fds->fd_arr, fd, fds->size);
	ALLOC_BUFF(buff);
	ALLOC_LINE(*line);
	ft_strclr(*line);
	if (!fds->overflow[fd_index])
		ALLOC_OVERFLOW(fds->overflow[fd_index]);
	if (*fds->overflow[fd_index] && (endl = ft_strchr(fds->overflow[fd_index], '\n')))
	{
		save_line(line, &(fds->overflow[fd_index]), endl);
		return (1);
	}
	return (read_line(fd, &buff, line, &(fds->overflow[fd_index])));
}

int		main(int ac, char **av)
{
	int		fd;
	char	*line;
	int		ret;

	if (ac != 2)
		exit(1);
	fd = open(av[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf(">>[%s]<<\n", line);
		free(line);
	}
	free(line);
	return (0);
}
