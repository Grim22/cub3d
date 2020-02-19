/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:13:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/19 10:48:14 by bbrunet          ###   ########.fr       */
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

    // initialiasation dune texture correspondant a une croix rouge sur fond noir
    int i;
    int j;
	i = 0;
    while(i < texW)
    {
	j = 0;
	while(j < texH)
	{
    	    tex[texW * j + i] = 65536 * 254 * (i != j && i != texW - j);
	    j++;
	}
	i++;
    }
    if (ac > 3 || ac < 2)
    {
        ft_putstr_fd("Error \n: Wrong number of arguments\n", 1);
        return(0);
    }
	game.save = 0;
    if ((ret = ft_init_parse(&game.params, av[1])) != 1)
        return(0);
    game.params.tex = tex;
    init_mlx(&game.img, game.params.res.x, game.params.res.y);
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
    //mlx_destroy_image(img.mlx, img.img);
    mlx_loop(game.img.mlx);
    ft_free_map(game.params.map);
}

/*
void fill_image(t_img *img, int x, int y)
{
	int i;
	int j;
	
	i = 0;
	while(i < x)
	{
		j = 0;
		while(j < y)
		{
			if (i <= (int)((float)x / 2) && j <= (int)((float)y / 2))
				my_mlx_pixel_put(img, i, j, 0xFF0000); //rouge
			if (i <= (int)((float)x / 2) && j >= (int)((float)y / 2))
				my_mlx_pixel_put(img, i, j, 0xFF0000); // jaune
			if (i >= (int)((float)x / 2) && j >= (int)((float)y / 2))
				my_mlx_pixel_put(img, i, j, 0x0000CC); // vert
			if (i >= (int)((float)x / 2) && j <= (int)((float)y / 2))
				my_mlx_pixel_put(img, i, j, 0x0000CC); // bleu
			j++;
		}
	i++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);	
}
*/
