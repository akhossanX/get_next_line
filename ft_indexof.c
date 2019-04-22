/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indexof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 16:42:15 by akhossan          #+#    #+#             */
/*   Updated: 2019/04/22 13:23:55 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_indexof(int *arr, int val, size_t size)
{
	int		i;

	if (!arr)
		return (-1);
	i = -1;
	while (++i < (int)size)
	{
		if (arr[i] == val)
			return (i);
	}
	return (-1);
}
