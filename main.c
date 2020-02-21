/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:13:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/21 15:49:46 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int ft_check_save(char *arg, t_game *game)
{
	if (ft_strncmp(arg, "--save", 7))
    {
		ft_putstr_fd("Error\nWrong second argument", 1);
		return (-1);
    }
	game->save = 1;
    return(0);
}

int exit_game(int ret, char *message, int parse, t_game *game)
{
    if (message)
    {
        ft_putstr_fd("Error\n", 1);
        ft_putstr_fd(message, 1);
        
    }
    if (parse)
        ft_free_params(game->params);
    return(ret);
}


int main(int ac, char **av)
{
    t_game game;

	game.save = 0;
	if ((ac > 3 || ac < 2))
        return(exit_game(ERROR, "Wrong number of arguments\n", 0, 0));
    if (ft_init_parse(&game.params, av[1]) == ERROR)
        return(exit_game(ERROR, 0, 1, &game));
    if (init_mlx(&game.img, game.params.res.x, game.params.res.y) == ERROR)
        return(exit_game(ERROR, "Mlx init failed", 1, &game));
	if (ft_get_textures(&game) == ERROR)
        return(exit_game(ERROR, 0, 1, &game));
    if (ac == 3)
    {
    	if (ft_check_save(av[2], &game) == -1)
            return(exit_game(ERROR, 0, 1, &game));
		cast_rays(&game); //verifier que ca n'affiche pas limage
    	save_bmp(&game);
        return(exit_game(SUCCESS, 0, 1, &game));
    }
    mlx_hook(game.img.win, X_EVENT_EXIT, 0, &ft_press_close, 0);
    mlx_hook(game.img.win, X_EVENT_KEY_PRESS, 0, &ft_key_events, &game);
    cast_rays(&game);
    //mlx_loop_hook(game.img.mlx, &cast_rays, &game);
    mlx_loop(game.img.mlx);
    return(exit_game(SUCCESS, 0, 1, &game));
}
