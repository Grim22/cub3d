/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_check_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:33:35 by bbrunet           #+#    #+#             */
/*   Updated: 2020/03/05 12:39:04 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_is_position(char c)
{
	if (c == '0' || c == '2' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
		return (0);
}

int	ft_check_mapborders_line(char **map, int len)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		if (ft_is_position(map[i][0]) || ft_is_position(map[i][len - 1]))
			return (-1);
		j = 0;
		while (j + 1 < len)
		{
			if (ft_is_position(map[i][j]))
				if (map[i][j + 1] == ' ')
					return (-1);
			if (map[i][j] == ' ')
				if (ft_is_position(map[i][j + 1]))
					return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_mapborders_col(char **map, int len, int num)
{
	int i;
	int j;

	j = 0;
	while (j < len)
	{
		if (ft_is_position(map[0][j]) || ft_is_position(map[num - 1][j]))
			return (-1);
		i = 0;
		while (i + 1 < num)
		{
			if (ft_is_position(map[i][j]))
				if (map[i + 1][j] == ' ')
					return (-1);
			if (map[i][j] == ' ')
				if (ft_is_position(map[i + 1][j]))
					return (-1);
			i++;
		}
		j++;
	}
	return (1);
}

int	ft_check_mapborders(char **map)
{
	int len;
	int num;

	len = 0;
	while (map[0][len])
		len++;
	num = 0;
	while (map[num])
		num++;
	if (ft_check_mapborders_line(map, len) == -1)
		return (-1);
	if (ft_check_mapborders_col(map, len, num) == -1)
		return (-1);
	return (0);
}
