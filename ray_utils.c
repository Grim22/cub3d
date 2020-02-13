/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:00:44 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/13 13:02:01 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void set_pos_dir(t_ray *ray, t_param params)
{
    ray->pos = params.pos;
    ray->dir = params.dir;
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