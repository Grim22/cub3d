/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:13:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/13 19:48:04 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int ac, char **av)
{
    t_game game;
    int ret;

    if (ac > 3 || ac < 2)
    {
        ft_putstr_fd("Error \n: Wrong number of arguments\n", 1);
        return(0);
    }
    if ((ret = ft_init_parse(&game.params, av[1])) != 1)
        return(0);
    init_mlx(&game.img, game.params.res.x, game.params.res.y);
    mlx_hook(game.img.win, X_EVENT_EXIT, 0, &ft_close, 0);
    mlx_hook(game.img.win, X_EVENT_KEY_PRESS, 0, &change_pos, &game);
    //mlx_put_image_to_window(game.img.mlx, game.img.win, game.img.img, 0, 0);
    mlx_loop_hook(game.img.mlx, &cast_rays, &game);
    //mlx_destroy_image(img.mlx, img.img);
    mlx_loop(game.img.mlx);
    ft_free_map(game.params.map);
}
