/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:13:57 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/19 19:06:37 by bbrunet          ###   ########.fr       */
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

    // initialiasation des textures //
    int i;
    int j;
	i = 0;
    while(i < texW)
    {
		j = 0;
		while(j < texH)
		{
			ycolor = i * 256 / texH;
    		xycolor = j * 128 / texH + i * 128 / texW;
			tex[texW * j + i] = 65536 * 254 * (i != j && i != texW - j); // red with black cross
			tex1[texW * j + i] = 65536 * 192 * (i % 16 && j % 16); // red bricks
			tex2[texW * j + i] = 256 * ycolor; // green gradient
			tex3[texW * j + i] = 256 * xycolor + 65536 * xycolor; // sloped yellow gradient
			j++;
		}
		i++;
    }
    game.params.tex1 = tex;
    game.params.tex2 = tex1;
    game.params.tex3 = tex2;
    game.params.tex4 = tex3;
	////////////////////////////////

	
	game.save = 0;
	if (ac > 3 || ac < 2)
    {
        ft_putstr_fd("Error \n: Wrong number of arguments\n", 1);
        return(0);
    }
    if ((ret = ft_init_parse(&game.params, av[1])) != 1)
        return(0);
    init_mlx(&game.img, game.params.res.x, game.params.res.y);


	//texture to image to int */////////////////////
	int xpm_text_W;
	int xpm_text_H;
	void *xpm_img;
	void *xpm_win;
	char *address;
	int *tex_eagle;
	int e_bpp;
	int e_line_size;
	int e_endian;
	char *tmp;
	int *tmp_i;

	// optimiser: mettre dans une structure de type t_img 
		
	xpm_img = mlx_xpm_file_to_image(game.img.mlx, "eagle.xpm", &xpm_text_W, &xpm_text_H);
	tex_eagle = malloc(xpm_text_W * xpm_text_H * sizeof(int));
	address = mlx_get_data_addr(xpm_img, &e_bpp, &e_line_size, &e_endian);
	i = 0;
	while(i < xpm_text_W)
	{
		j = 0;
		while(j < xpm_text_H)
		{
            tmp = address + (j * e_line_size + i * (e_bpp / 8)); // utiliser my_mlx_pixel_get (prend un t_img)
			tmp_i = (int *)tmp;
			tex_eagle[xpm_text_W * j + i] = *tmp_i;
			j++;
		}
		i++;
	}
	game.params.tex4 = tex_eagle;
	///////////////////////////////////////////////////

	
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
