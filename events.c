/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:25:12 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/24 18:30:50 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_key_left(int key, t_game *game, t_cord_f *dir, t_cord_f *plane)
{
	if (key == KEY_LEFT)
	{
		rotate_dir(dir, -SPEED_R);
		rotate_dir(plane, -SPEED_R);
		cast_rays(game);
	}
}

void	ft_key_right(int key, t_game *game, t_cord_f *dir, t_cord_f *plane)
{
	if (key == KEY_RIGHT)
	{
		rotate_dir(dir, SPEED_R);
		rotate_dir(plane, SPEED_R);
		cast_rays(game);
	}
}

void	ft_key_esc(int key)
{
	if (key == 53)
	{
		printf("Bye !\n");
		exit(0);
	}
}

int		ft_key_events(int key, t_game *game)
{
	t_cord_f norm;

	norm.x = -game->params.dir.y;
	norm.y = game->params.dir.x;
	ft_key_a(key, game, norm, &(game->params.pos));
	ft_key_d(key, game, norm, &(game->params.pos));
	ft_key_w(key, game, game->params.dir, &(game->params.pos));
	ft_key_s(key, game, game->params.dir, &(game->params.pos));
	ft_key_left(key, game, &(game->params.dir), &(game->params.plane));
	ft_key_right(key, game, &(game->params.dir), &(game->params.plane));
	ft_key_esc(key);
	//mlx_destroy_image(game->img.mlx, game->img.img);
	return (0);
}

int		ft_press_close(void *param)
{
	printf("Bye !\n");
	(void)param;
	exit(0);
}
