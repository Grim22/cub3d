/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:13:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/13 12:58:43 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int ac, char **av)
{
    t_param params;
    int ret;
    t_img img;

    if (ac > 3 || ac < 2)
    {
        ft_putstr_fd("Error \n: Wrong number of arguments\n", 1);
        return(0);
    }
    if ((ret = ft_init_parse(&params, av[1])) != 1)
        return(0);
    init_mlx(&img, params.res.x, params.res.y);
    if (cast_rays(&img, params) == -1)
        return(0);
    mlx_hook(img.win, 17, 0, &ft_close, 0);
    mlx_key_hook(img.win, &change_pos, &img);
    mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    //mlx_destroy_image(img.mlx, img.img);
    mlx_loop(img.mlx);
    ft_free_map(params.map);
}
