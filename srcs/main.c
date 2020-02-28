/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:13:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/28 15:48:05 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_init_game(t_game *game, char *filename)
{
	if (ft_init_parse(&game->params, filename) == -1)
		return (-1);
	if (init_mlx(&game->img, game->params.res.x, game->params.res.y) == -1)
	{
		ft_putstr_fd("Mlx init failed", 1);
		return (-1);
	}
	if (ft_get_textures(game) == -1)
		return (-1);
	return (1);
}

int	main(int ac, char **av)
{
	t_game game;

	if ((ac > 3 || ac < 2))
		return (exit_game(ERROR, "Wrong number of arguments\n", 0, 0));
	if (ft_init_game(&game, av[1]) == ERROR)
		return (exit_game(ERROR, 0, 1, &game));
	if (ac == 3)
	{
		if (ft_check_save(av[2], &game) == -1)
			return (exit_game(ERROR, 0, 1, &game));
		cast_rays(&game);
		save_bmp(&game);
		return (exit_game(SUCCESS, 0, 1, &game));
	}
	mlx_hook(game.img.win, X_EVENT_EXIT, 1L << 17, &ft_press_close, 0);
	mlx_hook(game.img.win, X_EVENT_KEY_PRESS, 1L << 0,
		&ft_press_events, &game.params);
	mlx_hook(game.img.win, X_EVENT_KEY_RELEASE, 1L << 1,
		&ft_release_events, &game.params);
	mlx_loop_hook(game.img.mlx, &cast_rays, &game);
	mlx_loop(game.img.mlx);
	return (exit_game(SUCCESS, 0, 1, &game));
}
