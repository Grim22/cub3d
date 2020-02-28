/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:14:19 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/28 15:42:46 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	init_ray(int i, int resx, t_cord_f plane, t_ray *ray)
{
	float pos_plane_i;

	ray->mapx = (int)ray->pos.x;
	ray->mapy = (int)ray->pos.y;
	ray->hit = 0;
	pos_plane_i = 2 * i / (float)resx - 1;
	ray->vect = vect_add(ray->dir, vect_scalar_prod(plane, pos_plane_i));
	ray->delta_dist.x = sqrtf(1 + (ray->vect.y * ray->vect.y)
		/ (ray->vect.x * ray->vect.x));
	ray->delta_dist.y = sqrtf(1 + (ray->vect.x * ray->vect.x)
		/ (ray->vect.y * ray->vect.y));
	return (0);
}

int	compute_side_dist_step(t_ray *ray)
{
	if (ray->vect.x < 0)
	{
		ray->stepx = -1;
		ray->side_dist.x = (ray->pos.x - (float)ray->mapx)
			* ray->delta_dist.x;
	}
	else
	{
		ray->stepx = 1;
		ray->side_dist.x = (ray->mapx + 1.0 - (float)ray->pos.x)
			* ray->delta_dist.x;
	}
	if (ray->vect.y < 0)
	{
		ray->stepy = -1;
		ray->side_dist.y = (ray->pos.y - (float)ray->mapy)
			* ray->delta_dist.y;
	}
	else
	{
		ray->stepy = 1;
		ray->side_dist.y = (ray->mapy + 1.0 - (float)ray->pos.y)
			* ray->delta_dist.y;
	}
	return (0);
}

int	perform_dda(char **map, t_ray *ray)
{
	int count;

	count = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x = ray->side_dist.x + ray->delta_dist.x;
			ray->mapx = ray->mapx + ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y = ray->side_dist.y + ray->delta_dist.y;
			ray->mapy = ray->mapy + ray->stepy;
			ray->side = 1;
		}
		if (map[ray->mapx][ray->mapy] == '1')
			ray->hit = 1;
		count++;
	}
	return (0);
}

int	compute_wall_height(int resy, t_ray *ray, float jump)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->mapx - ray->pos.x +
			(1 - ray->stepx) / 2) / ray->vect.x;
	else
		ray->wall_dist = (ray->mapy - ray->pos.y +
			(1 - ray->stepy) / 2) / ray->vect.y;
	ray->line_height = (int)(resy / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + resy / jump;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + resy / jump;
	if (ray->draw_end >= resy)
		ray->draw_end = resy - 1;
	return (0);
}

int	cast_rays(t_game *g)
{
	t_ray	ray;
	float	buffer[g->params.res.x];
	int		i;
	t_img	img;
	float	jump;

	jump = g->params.jump;
	img = g->img;
	ft_set_events_params(g);
	set_pos_dir_in_ray(&ray, g->params);
	compute_floor_ceiling(&img, g->params);
	i = -1;
	while (++i < g->params.res.x)
	{
		init_ray(i, g->params.res.x, g->params.plane, &ray);
		compute_side_dist_step(&ray);
		perform_dda(g->params.map, &ray);
		compute_wall_height(g->params.res.y, &ray, jump);
		// deux prochaines lignes: on remplace i par g->params.res.x - i + 1
		display_wall(&g->img, &ray, g->params.res.x - i - 1, g->params);
		buffer[g->params.res.x - i - 1] = ray.wall_dist;
	}
	display_sprites(&g->img, g->params, buffer);
	if (!g->save)
		mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	return (1);
}
