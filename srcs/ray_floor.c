/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_floor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:08:15 by bbrunet           #+#    #+#             */
/*   Updated: 2020/03/05 12:34:17 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		draw_floor(t_img *img, t_floor floor, t_tex tex, int resx)
{
	int x;
	int tx;
	int ty;
	int color;

	x = 0;
	while (x < resx)
	{
		tx = (int)floor.floor.x;
		ty = (int)floor.floor.y;
		tx = (int)(tex.dim.x * (floor.floor.x - tx)) & (tex.dim.x - 1);
		ty = (int)(tex.dim.y * (floor.floor.y - ty)) & (tex.dim.y - 1);
		color = tex.tex[tex.dim.y * ty + tx];
		my_mlx_pixel_put(img, resx - x - 1, floor.y, color);
		floor.floor = vect_add(floor.floor, floor.step);
		x++;
	}
	return (1);
}

void	fill_ceiling_floor(t_img *img, t_param params)
{
	int i;
	int j;

	i = 0;
	while (i < params.res.x)
	{
		j = 0;
		while (j < params.res.y)
		{
			if (j < params.res.y / params.jump)
				my_mlx_pixel_put(img, i, j, params.col_f);
			else
				my_mlx_pixel_put(img, i, j, params.col_c);
			j++;
		}
		i++;
	}
}

int		ft_texture_floor(t_img *img, t_param params)
{
	t_floor	floor;
	float	posz;
	float	rowdist;

	floor.y = 0;
	while (floor.y < params.res.y)
	{
		floor.x0 = vect_add(params.dir, vect_scalar_prod(params.plane, -1));
		floor.x1 = vect_add(params.dir, params.plane);
		floor.p = (int)(floor.y - (float)params.res.y / params.jump);
		posz = (float)params.res.y / params.jump;
		rowdist = posz / floor.p;
		floor.step = vect_add(floor.x1, vect_scalar_prod(floor.x0, -1));
		floor.step = vect_scalar_prod(floor.step, rowdist / params.res.x);
		floor.floor = vect_add(params.pos, vect_scalar_prod(floor.x0, rowdist));
		if (floor.y < params.res.y / params.jump)
			draw_floor(img, floor, params.ceiling, params.res.x);
		else
			draw_floor(img, floor, params.floor, params.res.x);
		floor.y++;
	}
	return (1);
}

int		compute_floor_ceiling(t_img *img, t_param params)
{
	if (params.texture_floor)
		ft_texture_floor(img, params);
	else
		fill_ceiling_floor(img, params);
	return (1);
}
