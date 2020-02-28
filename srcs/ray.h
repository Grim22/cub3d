/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:09:10 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/27 10:03:56 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vectors.h"
# include "mlx_h.h"
# include "parsing.h"

typedef struct	s_sprite
{
	int		height;
	int		width;
	int		middle;
	int		startx;
	int		endx;
	int		starty;
	int		endy;
	float	distance;
	int		tex_x;
	int		tex_height;
	int		tex_width;
}				t_sprite;

typedef struct	s_floor
{
	t_cord_f	floor;
	t_cord_f	x0;
	t_cord_f	x1;
	t_cord_f	step;
	int			y;
	int			p;
}				t_floor;

typedef struct	s_ray
{
	t_cord_f	pos;
	t_cord_f	dir;
	t_cord_f	vect;
	t_cord_f	delta_dist;
	t_cord_f	side_dist;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			side;
	int			hit;
	float		wall_dist;
	float		wallx;
	int			tex_x;
	int			tex_y;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			color;
}				t_ray;

int				init_ray(int i, int res_x, t_cord_f plane, t_ray *ray);
void			set_pos_dir_in_ray(t_ray *ray, t_param params);
int				compute_side_dist_step(t_ray *ray);
int				perform_dda(char **map, t_ray *ray);
int				compute_wall(int res_y, t_ray *ray);
void			print_ray_info(t_ray ray);
int				compute_plane(t_cord_f dir, float fov, t_cord_f *plane);
void			display_wall(t_img *img, t_ray *ray, int x, t_param params);
void			fill_ceiling_floor(t_img *img, t_param params);
void			compute_tex_x(t_ray *ray, t_tex *tex, t_param params);
int				display_sprites(t_img *img, t_param params, float *buffer);
void			ft_get_distance(int **order, float **distance, t_param params);
void			ft_sort_distance(int *order, float *distance, int num);
int				compute_floor_ceiling(t_img *img, t_param params);

#endif
