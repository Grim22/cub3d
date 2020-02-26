/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:14:08 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/26 18:00:19 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_convert_maptoint(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 48 || map[i][j] == 49 || map[i][j] == 50)
				map[i][j] = map[i][j] - 48;
			j++;
		}
		i++;
	}
}

int		ft_check_mapborders(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (map[i++][j - 1] != '1')
			return (-1);
	}
	j = 0;
	while (map[0][j])
	{
		if (map[0][j++] != '1')
			return (-1);
	}
	j = 0;
	while (map[i - 1][j])
	{
		if (map[i - 1][j++] != '1')
			return (-1);
	}
	return (0);
}

int		ft_check_mapcars(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 48 && map[i][j] != 49 && map[i][j] != 50
			&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
			&& map[i][j] != 'W')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int		ft_check_mapdir(char **map)
{
	int i;
	int j;
	int dir;

	i = 0;
	dir = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				dir = dir + 1;
			j++;
		}
		i++;
	}
	if (dir != 1)
		return (-1);
	return (0);
}

int		ft_check_map(char **map)
{
	if (ft_check_mapdir(map) == -1)
	{
		ft_putstr_fd("Error\nPlease specify one (and only one) direction", 1);
		return (-1);
	}
	if (ft_check_mapcars(map) == -1)
	{
		ft_putstr_fd("Error\nWrong char on map", 1);
		return (-1);
	}
	if (ft_check_mapborders(map) == -1)
	{
		ft_putstr_fd("Error\nBorders should be only '1'", 1);
		return (-1);
	}
	return (0);
}
