/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_check_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:33:35 by bbrunet           #+#    #+#             */
/*   Updated: 2020/03/02 15:59:09 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_full(char *a, int diff)
{
	int i;

	i = ft_strlen(a) - diff;
	while (a[i])
	{
		if (a[i] != '1')
			return (-1);
		i++;
	}
	return (1);
}

int	ft_check_mapborders_full(char **map)
{
	int i;
	int diff;

	i = 0;
	while (map[i + 1])
	{
		if ((diff = ft_strlen(map[i + 1]) - ft_strlen(map[i])) > 0)
		{
			if (check_full(map[i + 1], diff) == -1)
				return (-1);
		}
		if ((diff = ft_strlen(map[i + 1]) - ft_strlen(map[i])) < 0)
		{
			if (check_full(map[i], -diff) == -1)
				return (-1);
		}
		i++;
	}
	return (1);
}
