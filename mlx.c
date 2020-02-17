/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:13:35 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/13 205:49 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color; // marche aussi avec int. Pas compris pourquoi unsigned
}

void my_mlx_pixel_get(t_img *data, int x, int y, int *color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    color = (int *)dst;
}


int encode_color(int R, int G, int B)
{
    int r;
    int g;
    int b;
    int color;

    r = (R & 255) << 16;
    g = (G & 255) << 8;
    b = (B & 255);
    color = r | g | b;
    //color = (0 & 0xff) << 24 | color;
    return (color);
}

void init_mlx(t_img *img, int xres, int yres)
// inits mlx, creates a window and an image
{
    img->mlx = mlx_init();
    img->win = mlx_new_window(img->mlx, xres, yres, "Test");
    img->img = mlx_new_image(img->mlx, xres, yres);
    img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
}
