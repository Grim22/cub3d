/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:14:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/26 11:59:53 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	init_ray(int i, int resx, t_cord_f plane, t_ray *ray)
{
	float pos_plane_i;

	ray->mapX = (int)ray->pos.x;
	ray->mapY = (int)ray->pos.y;
	ray->hit = 0;
	pos_plane_i = 2 * i / (float)resx - 1; //coordonnees du pixel sur le plan image, dans le range [-1,1]
	ray->vect = vect_add(ray->dir, vect_scalar_prod(plane, pos_plane_i));
	ray->deltaDist.x = sqrtf(1 + (ray->vect.y * ray->vect.y)
		/ (ray->vect.x * ray->vect.x));
	ray->deltaDist.y = sqrtf(1 + (ray->vect.x * ray->vect.x)
		/ (ray->vect.y * ray->vect.y));
	return (0);
}

int	compute_sidedist_step(t_ray *ray)
{
	if (ray->vect.x < 0)
	{
		ray->stepX = -1;
		ray->sideDist.x = (ray->pos.x - (float)ray->mapX)
			* ray->deltaDist.x;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDist.x = (ray->mapX + 1.0 - (float)ray->pos.x)
			* ray->deltaDist.x;
	}
	if (ray->vect.y < 0)
	{
		ray->stepY = -1;
		ray->sideDist.y = (ray->pos.y - (float)ray->mapY)
			* ray->deltaDist.y;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDist.y = (ray->mapY + 1.0 - (float)ray->pos.y)
			* ray->deltaDist.y;
	}
	return (0);
}

int	perform_dda(char **map, t_ray *ray)
{
	int count;

	count = 0;
	while (ray->hit == 0)
	{
		if (ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x = ray->sideDist.x + ray->deltaDist.x;
			ray->mapX = ray->mapX + ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDist.y = ray->sideDist.y + ray->deltaDist.y;
			ray->mapY = ray->mapY + ray->stepY;
			ray->side = 1;
		}
		if (map[ray->mapX][ray->mapY] == '1')
			ray->hit = 1;
		count++;
	}
	return (0);
}

int	compute_wall_height(int resy, t_ray *ray, float jump)
{
	if (ray->side == 0)
		ray->wallDist = (ray->mapX - ray->pos.x +
			(1 - ray->stepX) / 2) / ray->vect.x;
	else
		ray->wallDist = (ray->mapY - ray->pos.y +
			(1 - ray->stepY) / 2) / ray->vect.y;
	ray->lineHeight = (int)(resy / ray->wallDist);
	ray->drawStart = -ray->lineHeight / 2 + resy / jump;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + resy / jump;
	if (ray->drawEnd >= resy)
		ray->drawEnd = resy - 1;
	return (0);
}

int	cast_rays(t_game *game)
{
	t_ray	ray;
	float	buffer[game->params.res.x];
	int		i;
	t_img	img;
	float jump;

	jump = game->params.jump;
	img = game->img;
	ft_set_events_params(game);
	set_pos_dir_in_ray(&ray, game->params); // pos et dir sont initialises dans param, on les copie ici dans ray car certains calculs ci dessous sont effectues a partir de ray
	compute_floor_ceiling(&img, game->params);
	i = 0;
	while (i < game->params.res.x)
	{
		init_ray(i, game->params.res.x, game->params.plane, &ray);
		compute_sidedist_step(&ray);
		perform_dda(game->params.map, &ray);
		compute_wall_height(game->params.res.y, &ray, jump);
		display_wall(&game->img, &ray, i, game->params);
		buffer[i] = ray.wallDist;
		i++;
	}
	display_sprites(&game->img, game->params, buffer);
	if (!game->save)
		mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	return (1);
}
