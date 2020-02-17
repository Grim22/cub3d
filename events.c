/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:25:12 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/14 12:54:45 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void ft_key_A(int key, t_game *game, t_cord_f norm, t_cord_f *pos)
{
   if (key == KEY_A && game->params.map[(int)(pos->x - norm.x / SPEED_M)][(int)(pos->y - norm.y / SPEED_M)] != '1')
   {
       pos->x += -(norm.x / SPEED_M); 
       pos->y += -(norm.y / SPEED_M); 
       cast_rays(game);
   }
}

void ft_key_D(int key, t_game *game, t_cord_f norm, t_cord_f *pos)
{
if (key == KEY_D && game->params.map[(int)(pos->x + norm.x / SPEED_M)][(int)(pos->y + norm.y / SPEED_M)] != '1')
    {
       pos->x += (norm.x / SPEED_M); 
       pos->y += (norm.y / SPEED_M); 
       cast_rays(game);
    }
}

void ft_key_W(int key, t_game *game, t_cord_f dir, t_cord_f *pos)
{
  if (key == KEY_W && game->params.map[(int)(pos->x + dir.x / SPEED_M)][(int)(pos->y + dir.y / SPEED_M)] != '1')
    {
       pos->x += dir.x / SPEED_M; 
       pos->y += dir.y / SPEED_M; 
       cast_rays(game);
    } 
}
void ft_key_S(int key, t_game *game, t_cord_f dir, t_cord_f *pos)
{
   if (key == KEY_S && game->params.map[(int)(pos->x - dir.x / SPEED_M)][(int)(pos->y - dir.y / SPEED_M)] != '1')
   {
       pos->x += -(dir.x / SPEED_M); 
       pos->y += -(dir.y / SPEED_M); 
       cast_rays(game);
   }
}

void ft_key_LEFT(int key, t_game *game, t_cord_f *dir, t_cord_f *plane)
{
  if (key == KEY_LEFT)
    {
       rotate_dir(dir, -SPEED_R);
       rotate_dir(plane, -SPEED_R);
       cast_rays(game);
    } 
}

void ft_key_RIGHT(int key, t_game *game, t_cord_f *dir, t_cord_f *plane)
{
  if (key == KEY_RIGHT)
    {
       rotate_dir(dir, SPEED_R);
       rotate_dir(plane, SPEED_R);
       cast_rays(game);
    }
}

void ft_key_ESC(int key)
{
    if (key == 53)
    {
	    printf("Bye !\n");
        exit(0);
    }
}

int ft_key_events(int key, t_game *game)
{
    t_cord_f norm;
    
    norm.x = -game->params.dir.y;
    norm.y = game->params.dir.x;
    ft_key_A(key, game, norm, &(game->params.pos));
    ft_key_D(key, game, norm, &(game->params.pos));
    ft_key_W(key, game, game->params.dir, &(game->params.pos));
    ft_key_S(key, game, game->params.dir, &(game->params.pos));
    ft_key_LEFT(key, game, &(game->params.dir), &(game->params.plane));
    ft_key_RIGHT(key, game, &(game->params.dir), &(game->params.plane));
    ft_key_ESC(key);
    if (key == KEY_ESC)
    {
	    printf("Bye !\n");
        exit(0);
    }
    //mlx_destroy_image(game->img.mlx, game->img.img);
    return(0);
}

int ft_press_close(void *param)
{
	printf("Bye !\n");
	(void)param;
	exit(0);
}
