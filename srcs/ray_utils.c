/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:00:44 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/28 11:56:57 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	compute_tex_x(t_ray *ray, t_tex *tex, t_param params)
{
	if (ray->side == 0 && ray->vect.x > 0)
		*tex = params.tex[SO];
	else if (ray->side == 0 && ray->vect.x < 0)
		*tex = params.tex[NO];
	else if (ray->side == 1 && ray->vect.y > 0)
		*tex = params.tex[EA];
	else
		*tex = params.tex[WE];
	if (ray->side == 0)
		ray->wallx = ray->pos.y + ray->wall_dist * ray->vect.y;
	else
		ray->wallx = ray->pos.x + ray->wall_dist * ray->vect.x;
	ray->wallx = ray->wallx - (int)ray->wallx;
	ray->tex_x = (int)(ray->wallx * (float)tex->dim.x);
	if (ray->side == 0 && ray->vect.x > 0)
		ray->tex_x = tex->dim.x - ray->tex_x - 1;
	if (ray->side == 1 && ray->vect.y < 0)
		ray->tex_x = tex->dim.x - ray->tex_x - 1;
}

void	set_pos_dir_in_ray(t_ray *ray, t_param params)
{
	ray->pos = params.pos;
	ray->dir = params.dir;
}

void	display_wall(t_img *img, t_ray *ray, int x, t_param params)
{
	int		j;
	float	step;
	float	tex_y;
	float	tex_pos;
	t_tex	tex;

	compute_tex_x(ray, &tex, params);
	step = (float)tex.dim.y / (float)ray->line_height;
	tex_pos = (ray->draw_start - params.res.y / params.jump + ray->line_height / 2) * step;	
	j = ray->draw_start;
	while (j < ray->draw_end)
	{
		//tex_y = (int)tex_pos & (tex.dim.y - 1);
		tex_y = (int)tex_pos;
		my_mlx_pixel_put(img, x, j,
			tex.tex[tex.dim.x * (int)tex_y + ray->tex_x]);
		tex_pos = tex_pos + step;
		j++;
	}
}

void	print_ray_info(t_ray ray)
{
	printf("mapx %d\n", ray.mapx);
	printf("mapy %d\n", ray.mapy);
	printf("posX %f\n", ray.pos.x);
	printf("posY %f\n", ray.pos.y);
	printf("dirX %f\n", ray.dir.x);
	printf("dirY %f\n", ray.dir.y);
	printf("sided.x %f\n", ray.side_dist.x);
	printf("sided.y %f\n", ray.side_dist.y);
	printf("deltad.x %f\n", ray.delta_dist.x);
	printf("deltad.y %f\n", ray.delta_dist.y);
	printf("dist %f\n", ray.wall_dist);
	printf("height %d\n", ray.line_height);
	printf("start %d\n", ray.draw_start);
	printf("end %d\n", ray.draw_end);
}
