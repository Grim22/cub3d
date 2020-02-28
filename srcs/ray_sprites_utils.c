/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:22:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/24 15:24:42 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_sort_distance(int *order, float *distance, int num)
{
	int j;

	j = 0;
	while (j < num - 1)
	{
		if (distance[j] < distance[j + 1])
		{
			ft_swap_i(&order[j], &order[j + 1]);
			ft_swap_f(&distance[j], &distance[j + 1]);
			j = 0;
		}
		else
			j++;
	}
}

void	ft_get_distance(int **order, float **distance, t_param params)
{
	int			i;
	int			num;
	t_cord_f	*sprite;
	t_cord_f	pos;

	num = params.sprite_num;
	pos = params.pos;
	sprite = params.sprites;
	*order = malloc(num * sizeof(int));
	*distance = malloc(num * sizeof(float));
	i = 0;
	while (i < num)
	{
		order[0][i] = i;
		distance[0][i] = (pos.x - sprite[i].x) * (pos.x - sprite[i].x) +
			(pos.y - sprite[i].y) * (pos.y - sprite[i].y);
		i++;
	}
}
