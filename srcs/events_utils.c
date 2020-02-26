/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:27:04 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/24 18:30:03 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_key_a(t_game *game, t_cord_f norm, t_cord_f *pos)
{
	if (game->params.map[(int)(pos->x - norm.x / SPEED_M)][(int)(pos->y - norm.y / SPEED_M)] == '0')
	{
		pos->x += -(norm.x / SPEED_M);
		pos->y += -(norm.y / SPEED_M);
	}
}

void	ft_key_d(t_game *game, t_cord_f norm, t_cord_f *pos)
{
	if (game->params.map[(int)(pos->x + norm.x / SPEED_M)]
		[(int)(pos->y + norm.y / SPEED_M)] == '0')
	{
		pos->x += (norm.x / SPEED_M);
		pos->y += (norm.y / SPEED_M);
	}
}

void	ft_key_w(t_game *game, t_cord_f dir, t_cord_f *pos)
{
	if (game->params.map[(int)(pos->x + dir.x / SPEED_M)]
		[(int)(pos->y + dir.y / SPEED_M)] == '0')
	{
		pos->x += dir.x / SPEED_M;
		pos->y += dir.y / SPEED_M;
	}
}

void	ft_key_s(t_game *game, t_cord_f dir, t_cord_f *pos)
{
	if (game->params.map[(int)(pos->x - dir.x / SPEED_M)]
		[(int)(pos->y - dir.y / SPEED_M)] == '0')
	{
		pos->x += -(dir.x / SPEED_M);
		pos->y += -(dir.y / SPEED_M);
	}
}
