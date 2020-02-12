/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:13:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/12 16:13:58 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int ac, char **av)
{
    t_param params;
    t_cord_f plane;
    t_ray ray;
    float FOV;
    int i;
    t_data img;
    char **map;

    if (ac > 3 || ac < 2)
    {
        ft_putstr_fd("Error \n: Wrong number of arguments\n", 1);
        return(1);
    }
    if ((i = ft_init_parse(&map, &ray, &params, av[1])) != 1)
        return(0);
    FOV = 66; // a choisir nous meme
    FOV = FOV * M_PI / 180;
    compute_plane(ray.dir, FOV, &plane);

    init_mlx(&img, params.res.x, params.res.y);
    fill_screen(&img, params.res.x, params.res.y); // background color
    i = 0;
    while(i < params.res.x)
    {
        init_ray(i, params.res.x, plane, &ray);
        compute_sideDist_step(&ray);
        perform_DDA(map, &ray);
        //printf("i: %d\n", i);
        compute_wall(params.res.y, &ray);
        display_wall(&img, ray, i);
        //if (i % 25 == 0)
            //print_ray_info(ray);
        i++;
    }
    ft_free_map(map);
    mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_loop(img.mlx);
}
