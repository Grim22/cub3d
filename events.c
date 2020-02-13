/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:25:12 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/13 12:22:52 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int change_pos(int key, t_img *img)
{
    if (key == KEY_A) //'a'
    {
       printf("Hello\n");
    }
    if (key == KEY_ESC)
    {
	    printf("Bye !\n");
        exit(0);
    }
    return(0);
}

int ft_close(void *param)
{
	printf("Bye !\n");
	(void)param;
	exit(0);
}

int close_on_ESC(int key)
{
    if (key == 53)
    {
	    printf("Bye !\n");
        exit(0);
    }
    return(0);
}
/*
int print_square_on_click(int key, int x, int y, t_data *img)
{
    static int count;
    
    printf("keycode: %d, x: %d, y: %d\n", key, x, y);
    if (key == 1)
    {
        print_square(*img, 10*count, 20, 50, 0xFF00FF);
        mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
        count++;
    }
    return(0);
}

int try_loop_hook(t_data *img)
{   
    print_square(*img, 10, 20, 50, 0xFF00FF);
    mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
    return(0);
}*/