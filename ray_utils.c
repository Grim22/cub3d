/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:00:44 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/19 14:22:04 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void compute_texX(t_ray *ray)
{
    if (ray->side == 0) 
        ray->wallX = ray->pos.y + ray->wallDist * ray->vect.y;
    else
	    ray->wallX = ray->pos.x + ray->wallDist * ray->vect.x;
    ray->wallX = ray->wallX - (int)ray->wallX;

    ray->texX = (int)(ray->wallX * (float)texW);
    // selon la direction du rayon, le texX = 0 est soit en a tout a gauche (en bas) du carre soit tout a droite (en haut)
    if(ray->side == 0 && ray->vect.x > 0) 
        ray->texX = texW - ray->texX - 1;
    if(ray->side == 1 && ray->vect.y < 0) 
        ray->texX = texW - ray->texX - 1;
}


void set_pos_dir_in_ray(t_ray *ray, t_param params)
{
    ray->pos = params.pos;
    ray->dir = params.dir;
}

void display_wall(t_img *img, t_ray ray, int x, t_param params)
{
    int j;
    float step;
    float texY;
    int *tex;
    // coordonnee en y dans la texture pour chaque pour chaque point de la ligne verticale correspondant au ray)
    if (ray.side == 0 && ray.vect.x > 0)
        tex = params.tex1;
    else if (ray.side == 0 && ray.vect.x < 0)
        tex = params.tex2;
    else if (ray.side == 1 && ray.vect.y > 0)
        tex = params.tex3;
    else if (ray.side == 1 && ray.vect.y < 0)
        tex = params.tex4;
    step = (float)texH / (float)ray.lineHeight;
    texY = 0; 
    j = ray.drawStart;
    while (j < ray.drawEnd)
    {
        if ((int)texY > texH - 1)
            texY = texH - 1;
        my_mlx_pixel_put(img, x, j, tex[texW * (int)texY + ray.texX]);
	    texY = texY + step;
        j++;
    }
}

void fill_ceiling_floor(t_img *img, t_param params)
{
    int i;
    int j;
    
    i = 0;
    while(i < params.res.x)
    {
        j = 0;
        while(j< params.res.y)
        {
            if(j < params.res.y / 2)
                my_mlx_pixel_put(img, i, j, params.col_F);
            else
                my_mlx_pixel_put(img, i, j, params.col_C);
            j++;
        }
        i++;
    }
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
