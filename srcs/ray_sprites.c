/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:21:28 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/28 15:46:03 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_project_sprite(t_sprite *sprite, int *order, t_param params, int i)
{
	float		spritex;
	float		spritey;
	float		inv_det;
	float		transformx;
	t_cord_f	*sprite_tab;

	sprite_tab = params.sprites;
	spritex = sprite_tab[order[i]].x - params.pos.x;
	spritey = sprite_tab[order[i]].y - params.pos.y;
	inv_det = 1.0 / (params.plane.x * params.dir.y
		- params.dir.x * params.plane.y);
	transformx = -inv_det * (params.dir.y * spritex // multiplication par -1
		- params.dir.x * spritey);
	sprite->distance = inv_det * (-params.plane.y * spritex
		+ params.plane.x * spritey);
	sprite->middle = (int)((params.res.x / 2)
		* (1 + transformx / sprite->distance));
}

void	ft_get_start_end(t_param params, t_sprite *sprite)
{
	int w;
	int h;

	w = params.res.x;
	h = params.res.y;
	sprite->height = abs((int)(h / sprite->distance));
	sprite->starty = -sprite->height / 2 + h / params.jump;
	if (sprite->starty < 0)
		sprite->starty = 0;
	sprite->endy = sprite->height / 2 + h / params.jump;
	if (sprite->endy >= h)
		sprite->endy = h - 1;
	sprite->width = abs((int)(h / sprite->distance))
		* sprite->tex_width / sprite->tex_height;
	sprite->startx = -sprite->width / 2 + sprite->middle;
	if (sprite->startx < 0)
		sprite->startx = 0;
	sprite->endx = sprite->width / 2 + sprite->middle;
	if (sprite->endx >= w)
		sprite->endx = w - 1;
}

int		draw_vertical_stripe(t_img *img, t_param params, t_sprite sprite, int x)
{
	int d;
	int tex_y;
	int y;
	int color;
	int *texture;

	texture = params.tex[SPRIT].tex;
	y = sprite.starty;
	while (y < sprite.endy)
	{
		d = (y * 256 - params.res.y / params.jump * 256
			+ sprite.height / 2 * 256);
		tex_y = ((d * sprite.tex_height) / sprite.height) / 256;
		color = texture[sprite.tex_height * tex_y + sprite.tex_x];
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(img, x, y, color);
		y++;
	}
	return (1);
}

int		ft_draw_sprite(t_img *img, t_param params, float *buf, t_sprite *sprite)
{
	int			stripe;

	sprite->tex_width = params.tex[SPRIT].dim.x;
	sprite->tex_height = params.tex[SPRIT].dim.y;
	ft_get_start_end(params, sprite);
	stripe = sprite->startx;
	while (stripe < sprite->endx)
	{
		sprite->tex_x = (int)(256 * (stripe
			- (sprite->middle - sprite->width / 2))
			* sprite->tex_width / sprite->width) / 256;
		if (sprite->distance > 0 && stripe > 0
			&& stripe < params.res.x && sprite->distance < buf[stripe])
			draw_vertical_stripe(img, params, *sprite, stripe);
		stripe++;
	}
	return (0);
}

int		display_sprites(t_img *img, t_param params, float *buf)
{
	int			*order;
	float		*distance;
	int			i;
	t_sprite	sprite;

	ft_get_distance(&order, &distance, params);
	ft_sort_distance(order, distance, params.sprite_num);
	i = 0;
	while (i < params.sprite_num)
	{
		ft_project_sprite(&sprite, order, params, i);
		ft_draw_sprite(img, params, buf, &sprite);
		i++;
	}
	free(distance);
	free(order);
	return (0);
}
