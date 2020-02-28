/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:25:12 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/28 11:02:28 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_set_events_params(t_game *game)
{
	t_cord_f norm;

	norm.x = game->params.dir.y;
	norm.y = -game->params.dir.x;
	if (game->params.key_a)
		ft_key_a(game, norm, &(game->params.pos));
	if (game->params.key_d)
		ft_key_d(game, norm, &(game->params.pos));
	if (game->params.key_w)
		ft_key_w(game, game->params.dir, &(game->params.pos));
	if (game->params.key_s)
		ft_key_s(game, game->params.dir, &(game->params.pos));
	if (game->params.key_left)
		ft_key_left(&(game->params.dir), &(game->params.plane));
	if (game->params.key_right)
		ft_key_right(&(game->params.dir), &(game->params.plane));
	if (game->params.key_up)
		game->params.jump = 1.2;
	else if (game->params.key_down)
		game->params.jump = 4;
	else
		game->params.jump = 2;
	if (game->params.key_esc)
		ft_key_esc();
	return (1);
}

int		ft_press_close(void *param)
{
	printf("Bye !\n");
	(void)param;
	exit(0);
}

int		ft_press_events(int key, t_param *params)
{
	if (key == KEY_A)
		params->key_a = 1;
	if (key == KEY_S)
		params->key_s = 1;
	if (key == KEY_D)
		params->key_d = 1;
	if (key == KEY_W)
		params->key_w = 1;
	if (key == KEY_RIGHT)
		params->key_right = 1;
	if (key == KEY_LEFT)
		params->key_left = 1;
	if (key == KEY_ESC)
		params->key_esc = 1;
	if (key == KEY_UP)
		params->key_up = 1;
	if (key == KEY_DOWN)
		params->key_down = 1;
	if (key == KEY_SPACE)
		params->texture_floor = 1;
	return (1);
}

int		ft_release_events(int key, t_param *params)
{
	if (key == KEY_A)
		params->key_a = 0;
	if (key == KEY_S)
		params->key_s = 0;
	if (key == KEY_D)
		params->key_d = 0;
	if (key == KEY_W)
		params->key_w = 0;
	if (key == KEY_RIGHT)
		params->key_right = 0;
	if (key == KEY_LEFT)
		params->key_left = 0;
	if (key == KEY_ESC)
		params->key_esc = 0;
	if (key == KEY_UP)
		params->key_up = 0;
	if (key == KEY_DOWN)
		params->key_down = 0;
	return (1);
}
