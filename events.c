/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:25:12 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/13 20:53:37 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int change_pos(int key, t_game *game) //utilser les fonctions daddition de vecteurs et faire des ss fonctions
{
    float *x;
    float *y;
    t_cord_f *pos;
    t_cord_f *dir;
    t_cord_f norm;
    
    pos = &(game->params.pos);
    dir = &(game->params.dir);
    norm.x = -dir->y;
    norm.y = dir->x;
    if (key == KEY_A && game->params.map[(int)(pos->x - norm.x / SPEED_M)][(int)(pos->y - norm.y / SPEED_M)] != '1')
    {
       pos->x += -(norm.x / SPEED_M); 
       pos->y += -(norm.y / SPEED_M); 
        cast_rays(game);
    }
    if (key == KEY_D && game->params.map[(int)(pos->x + norm.x / SPEED_M)][(int)(pos->y + norm.y / SPEED_M)] != '1')
    {
       pos->x += (norm.x / SPEED_M); 
       pos->y += (norm.y / SPEED_M); 
       cast_rays(game);
    }
    if (key == KEY_W && game->params.map[(int)(pos->x + dir->x / SPEED_M)][(int)(pos->y + dir->y / SPEED_M)] != '1')
    {
       pos->x += dir->x / SPEED_M; 
       pos->y += dir->y / SPEED_M; 
       cast_rays(game);
    }
    if (key == KEY_S && game->params.map[(int)(pos->x - dir->x / SPEED_M)][(int)(pos->y - dir->y / SPEED_M)] != '1')
    {
       pos->x += -(dir->x / SPEED_M); 
       pos->y += -(dir->y / SPEED_M); 
       cast_rays(game);
    }
    if (key == KEY_LEFT)
    {
       rotate_dir(&game->params.dir.x, &game->params.dir.y, -SPEED_R);
       rotate_dir(&game->params.plane.x, &game->params.plane.y, -SPEED_R);
       cast_rays(game);
    }
    if (key == KEY_RIGHT)
    {
       rotate_dir(&game->params.dir.x, &game->params.dir.y, SPEED_R);
       rotate_dir(&game->params.plane.x, &game->params.plane.y, SPEED_R);
       cast_rays(game);
    }
    if (key == KEY_ESC)
    {
	    printf("Bye !\n");
        exit(0);
    }
    //mlx_destroy_image(game->img.mlx, game->img.img);
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