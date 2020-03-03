/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_check_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:33:35 by bbrunet           #+#    #+#             */
/*   Updated: 2020/03/03 16:07:35 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_check_mapborders_line(char **map)
{
	int i;
	int j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j + 1])
		{
			if (map[i][j] == '0')
				if(map[i][j + 1] == '8')
					return(-1);
			if (map[i][j + 1] == '8')
				if (map[i][j] == '0')
					return(-1);
			j++;
		}
		i++;
	}
	return(1);
}

int	ft_check_mapborders_col(char **map)
{
	int i;
	int j;
	int len;
	int num;

	len = 0;
	while (map[0][len])
		len++;
	num = 0;
	while(map[num])
		num++;
	j = 0;
	while(j < len)
	{
		i = 0;
		while(i + 1 < num)
		{
			if (map[i][j] == '0')
				if (map[i + 1][j] == '8')
					return (-1);
			if (map[i + 1][j] == '0')
				if (map[i][j] == '8')
					return (-1);
			i++;
		}
	j++;
	}
	return(1);
}
	