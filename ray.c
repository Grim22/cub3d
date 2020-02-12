/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:14:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/12 16:14:20 by bbrunet          ###   ########.fr       */
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

//int perform_DDA(int map[24][24], t_ray *ray)
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
        ray->color = 0xFFFF00;
    else
        ray->color = 0x5FFFFF00;
    return(0);
}
int compute_plane(t_cord_f dir, float FOV, t_cord_f *plane)
{
    // determination du vecteur plan image:
        // dir: perpendiculaire a direction du joueur = dir.
        // valeur: plane / 2
    int bool_x = 0;
    int bool_y = 0;
    
    if (dir.x)
        bool_y = 1;
    else
        bool_x = 1;
    plane->x = bool_x * tan(FOV/2);
    plane->y = bool_y * tan(FOV / 2);
    //printf("py: %f\n", plane->y);
    //printf("px: %f\n", plane->x);
    return(0);
}
void print_ray_info(t_ray ray)
{
    printf("mapX %d\n", ray.mapX);
    printf("mapY %d\n", ray.mapY);
     printf("posX %f\n", ray.pos.x);
    printf("posY %f\n", ray.pos.y);
     printf("dirX %f\n", ray.dir.x);
    printf("dirY %f\n", ray.dir.y);
    printf("sided.x %f\n", ray.sideDist.x);
    printf("sided.y %f\n", ray.sideDist.y);
    printf("deltad.x %f\n", ray.deltaDist.x);
    printf("deltad.y %f\n", ray.deltaDist.y);
    printf("dist %f\n", ray.wallDist);
    printf("height %d\n", ray.lineHeight);
    printf("start %d\n", ray.drawStart);
    printf("end %d\n", ray.drawEnd);
}
