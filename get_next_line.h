/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:04:56 by akhossan          #+#    #+#             */
/*   Updated: 2019/04/22 21:44:34 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define ALLOC_LINE(line)		if(!(line = ft_strnew(0))) return (-1)
# define ALLOC_OVERFLOW(over)	if(!(over = ft_strnew(BUFF_SIZE))) return (-1)
# define BUFF_SIZE	10000000
# define FD_MAX	4864

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int					get_next_line(int fd, char **line);

#endif
