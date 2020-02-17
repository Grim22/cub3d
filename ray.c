/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:14:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/14 19:24:38 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int init_ray(int i, int resX, t_cord_f plane, t_ray *ray)
{
    float pos_plane_i;

    ray->mapX = (int)ray->pos.x;
    ray->mapY = (int)ray->pos.y;
    ray->hit = 0;
    pos_plane_i = 2 * i / (float)resX - 1; //coordonnees du pixel sur le plan image, dans le range [-1,1]
    ray->vect = vect_add(ray->dir, vect_scalar_prod(plane, pos_plane_i));

    ray->deltaDist.x = sqrtf(1 + (ray->vect.y * ray->vect.y) / (ray->vect.x * ray->vect.x));
    ray->deltaDist.y = sqrtf(1 + (ray->vect.x * ray->vect.x) / (ray->vect.y * ray->vect.y));
    return(0);
}

int compute_sideDist_step(t_ray *ray)
{
  if (ray->vect.x < 0)
    {
        ray->stepX = -1;
        ray->sideDist.x = (ray->pos.x - (float)ray->mapX) * ray->deltaDist.x;
    }
    else
    {
        ray->stepX = 1;
        ray->sideDist.x = (ray->mapX + 1.0 - (float)ray->pos.x) * ray->deltaDist.x;
    }
    if (ray->vect.y < 0)
    {
        ray->stepY = -1;
        ray->sideDist.y = (ray->pos.y - (float)ray->mapY) * ray->deltaDist.y;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDist.y = (ray->mapY + 1.0 - (float)ray->pos.y) * ray->deltaDist.y;
    }
    return(0);
}

int perform_DDA(char **map, t_ray *ray)
{
    int count = 0;
    //printf("DDA\n");
    while (ray->hit == 0)
    {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (ray->sideDist.x < ray->sideDist.y)
        {
            //printf("X\n");
            ray->sideDist.x = ray->sideDist.x + ray->deltaDist.x;
            ray->mapX = ray->mapX + ray->stepX;
            //printf("mapY: %d\n", ray->mapY);
            ray->side = 0;
        }
        else
        {
            //printf("Y\n");
            ray->sideDist.y = ray->sideDist.y + ray->deltaDist.y;
            ray->mapY = ray->mapY + ray->stepY;
            //printf("mapY: %d\n", ray->mapY);
            ray->side = 1;
        }
        //Check if ray has hit a wall
        if (map[ray->mapX][ray->mapY] == '1' || map[ray->mapX][ray->mapY] == '2') 
            ray->hit = 1;
        count++;
    }
    return(0);
}

int compute_wall(int resY, t_ray *ray)
{
    if (ray->side == 0) 
        ray->wallDist = (ray->mapX - ray->pos.x + (1 - ray->stepX) / 2) / ray->vect.x;
    else
        ray->wallDist = (ray->mapY - ray->pos.y + (1 - ray->stepY) / 2) / ray->vect.y;
    ray->lineHeight = (int)(resY / ray->wallDist);
    ray->drawStart = -ray->lineHeight / 2 + resY / 2;
    if (ray->drawStart < 0)
        ray->drawStart = 0;
    ray->drawEnd = ray->lineHeight / 2 + resY / 2;
    if(ray->drawEnd >= resY)
        ray->drawEnd = resY - 1;
    if(ray->side == 1)
        ray->color = 0x013300;
    else
        ray->color = 0x016400;
    return(0);
}

int cast_rays(t_game *game)
{
    t_ray ray;
    int i;

    set_pos_dir_plane(&ray, game->params);
    //ft_print_map(game->params.map);
    //compute_plane(ray.dir, FOV, &plane);
    //fill_screen(&game->img, game->params.res.x, game->params.res.y); // background color
    fill_ceiling_floor(&game->img, game->params); // background color
    i = 0;
    while(i < game->params.res.x)
    {
        init_ray(i, game->params.res.x, game->params.plane, &ray);
        compute_sideDist_step(&ray);
        //print_ray_info(ray);
        perform_DDA(game->params.map, &ray);
        //printf("Hello\n");
        compute_wall(game->params.res.y, &ray);
        display_wall(&game->img, ray, i);
        //if (i % 25 == 0)
            //print_ray_info(ray);
        i++;
    }
    //mlx_destroy_image(game->img.mlx, game->img.win);
    mlx_put_image_to_window(game->img.mlx, game->img.win, game->img.img, 0, 0);
    return(1);
}