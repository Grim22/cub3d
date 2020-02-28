/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 11:32:14 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/28 15:46:25 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_print_map(char **map)
{
	int i;
	int j;

	printf("Hello\n");
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("  len: %d\n", j);
		i++;
	}
}

int		ft_count_sprites(char **map)
{
	int i;
	int j;
	int count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int		ft_fill_sprites(t_cord_f **sprites, int *num, char **map)
{
	int count;
	int i;
	int j;

	*num = ft_count_sprites(map);
	*sprites = malloc(*num * sizeof(**sprites));
	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
			{
				sprites[0][count].x = i + 0.5;
				sprites[0][count].y = j + 0.5;
				count++;
			}
			j++;
		}
		i++;
	}
	return (1);
}
