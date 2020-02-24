/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:21:28 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/24 15:44:14 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_project_sprites(t_sprite *sprite, int *order, t_param params, int i)
{
	float		spritex;
	float		spritey;
	float		inv_det;
	float		transformx;
	t_cord_f	*sprite_tab;

	sprite_tab = params.sprites;
	//translate sprite position to relative to camera
	spritex = sprite_tab[order[i]].x - params.pos.x;
	spritey = sprite_tab[order[i]].y - params.pos.y;
	//transform sprite with the inverse camera matrix
	// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
	// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
	// [ planeY   dirY ]                                          [ -planeY  planeX ]
	inv_det = 1.0 / (params.plane.x * params.dir.y - params.dir.x * params.plane.y); //required for correct matrix multiplication
	transformx = inv_det * (params.dir.y * spritex - params.dir.x * spritey);
	sprite->distance = inv_det * (-params.plane.y * spritex + params.plane.x * spritey); //this is actually the depth inside the screen, that what Z is in 3D
	sprite->middle = (int)((params.res.x / 2) * (1 + transformx / sprite->distance));
}

void	ft_get_start_end(t_param params, t_sprite *sprite)
{
	int w;
	int h;

	w = params.res.x;
	h = params.res.y;
	sprite->height = abs((int)(h / sprite->distance));
	sprite->starty = -sprite->height / 2 + h / 2;
	if (sprite->starty < 0)
		sprite->starty = 0;
	sprite->endy = sprite->height / 2 + h / 2;
	if (sprite->endy >= h)
		sprite->endy = h - 1;
	//sprit_sceen->x = abs((int)(h / (transform_y))); // on part du principe que la texture est carree: a changer
	sprite->width = abs((int)(h / sprite->distance)); // on part du principe que la texture est carree: a changer
	sprite->startx = -sprite->width / 2 + sprite->middle;
	if (sprite->startx < 0)
		sprite->startx = 0;
	sprite->endx = sprite->width / 2 + sprite->middle;
	if (sprite->endx >= w)
		sprite->endx = w - 1;
}

int		draw_vertical_stripe(t_img *img, t_param params, t_sprite sprite, int tex_x, int stripe, int tex_height)
{
	int d;
	int tex_y;
	int y;
	int color;
	
	y = sprite.starty;
	while (y < sprite.endy)
	{
		d = (y * 256 - params.res.y * 128 + sprite.height * 128); //256 and 128 factors to avoid floats
		tex_y = ((d * tex_height) / sprite.height) / 256;
		color = params.tex[SPRIT].tex[tex_height * tex_y + tex_x];
		if ((color & 0x00FFFFFF) != 0) //paint pixel if isnt black, black is the invisible color
			my_mlx_pixel_put(img, stripe, y, color);
		//Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * tex_y + tex_x]; //get current color from the texture
		//if ((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible colorstripe++;
		y++;
	}
	return(1);
}

int		ft_draw_sprites(t_img *img, t_param params, float *buffer, t_sprite *sprite)
{
	//t_sprite	sprite;
	int			stripe;
	int			tex_height;
	int			tex_width;
	int			tex_x; // verticale a dessiner dans la texture

	tex_width = params.tex[SPRIT].dim.x;
	tex_height = params.tex[SPRIT].dim.y;
	ft_get_start_end(params, sprite);
	//loop through every vertical stripe of the sprite on screen
	stripe = sprite->startx;
	while (stripe < sprite->endx)
	{
		tex_x = (int)(256 * (stripe - (-sprite->width / 2 + sprite->middle)) * tex_width / sprite->width) / 256;
		//the conditions in the if are:
		//1) it's in front of camera plane so you don't see things behind you
		//2) it's on the screen (left)
		//3) it's on the screen (right)
		//4) ZBuffer, with perpendicular distance
		if (sprite->distance > 0 && stripe > 0 && stripe < params.res.x && sprite->distance < buffer[stripe])
			draw_vertical_stripe(img, params, *sprite, tex_x, stripe, tex_height);
		stripe++;
	}
	return (0);
}

int		display_sprites(t_img *img, t_param params, float *buffer)
{
	//buffer contient la distance au 1er mur, pour chaque rayon
	int		*order;
	float	*distance;
	int		i;
	t_sprite sprite;
	float	transform_y;
	int		middle_x;
	
	ft_get_distance(&order, &distance, params);
	ft_sort_distance(order, distance, params.sprite_num); // du moins proche au plus proche
	i = 0;
	while (i < params.sprite_num)
	{
		ft_project_sprites(&sprite, order, params, i); //donne middle_x (les coordonees en x du CENTRE du sprite sur lecran) et transform_y (la distance entre le sprit et lecran)
		ft_draw_sprites(img, params, buffer, &sprite);
		i++;
	}
	free(distance);
	free(order);
	return (0);
}