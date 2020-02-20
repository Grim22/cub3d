/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:13:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/20 15:14:38 by bbrunet          ###   ########.fr       */
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


int main(int ac, char **av)
{
    t_game game;
    int ret;
    int tex[texH * texH];
    int tex1[texH * texH];
    int tex2[texH * texH];
    int tex3[texH * texH];
	int xycolor;
	int ycolor;

	game.save = 0;
	if (ac > 3 || ac < 2)
    {
        ft_putstr_fd("Error \n: Wrong number of arguments\n", 1);
        return(0);
    }
    if ((ret = ft_init_parse(&game.params, av[1])) != 1)
        return(0);
    init_mlx(&game.img, game.params.res.x, game.params.res.y);
	if (ft_get_textures(&game) == -1)
		return(0);
	
    if (ac == 3)
    {
    	if (ft_check_save(av[2], &game) == -1)
	    	return(0);
		cast_rays(&game); //verifier que ca n'affiche pas limage
    	save_bmp(&game);
		return (1);
    }
    mlx_hook(game.img.win, X_EVENT_EXIT, 0, &ft_press_close, 0);
    mlx_hook(game.img.win, X_EVENT_KEY_PRESS, 0, &ft_key_events, &game);
    mlx_loop_hook(game.img.mlx, &cast_rays, &game);
    mlx_loop(game.img.mlx);
    ft_free_params(game.params);
}
