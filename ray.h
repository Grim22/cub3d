/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:09:10 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/26 11:43:19 by bbrunet          ###   ########.fr       */
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
	int		middle; // projection du sprite sur laxe des x. Milieu entre startx et endx
	int		startx;
	int		endx;
	int		starty;
	int		endy;
	float	distance; // distance entre le sprit et la pos
	int		tex_x;		// position dans la texture (sur laxe horizontal) correspondant au stripe a dessiner
	int		tex_height;
	int		tex_width;
}				t_sprite;

typedef struct		s_floor
{
	t_cord_f	floor;
	t_cord_f	x0;
	t_cord_f	x1;
	t_cord_f	step;
	int		y;
	int		p;
}			t_floor;


typedef struct	s_ray
{
	//position du player
	t_cord_f	pos;
	//direction du player
	t_cord_f	dir;
	//rayon
	t_cord_f	vect;
	//distance (fixe): en X entre deux intersections vecticales a des carres, en Y entre deux intersections horizontales a des carres
	t_cord_f	deltaDist;
	//distance initale + incrementee a chaque intersection avec un carre (X est incrementee de deltadistX si intersection verticale, sinon Y est incremente de deltadistY). Permet de savoir si la prochaine intersection sera verticale ou horizontale
	t_cord_f	sideDist;
	//carre dans lequel le rayon se trouve
	int			mapX;
	int			mapY;
	//direction (+1 / -1) du rayon sur laxe des X et sur l'axe des Y
	int			stepX;
	int			stepY;
	//cote du carré touché (vertical 0 ou horizontal 1)
	int			side;
	int			hit;
	// distance (projection normale) entre pos et le mur
	float		wallDist;
	// coordonnee x ou y (en fonction du side) du point ou le mur a ete touche moins cordonnee x ou y du mur touche --> nombre entre 0 et 1
	float		wallX;
	// coordonnee en x dans la texture correspondant a wallX: texX = wallX * texw. Fixe pour chaque ray
	int			texX;
	// coordonnee en y dans la texture pour chaque pour chaque point de la ligne verticale correspondant au ray)
	int			texY;
	//hauteur du mur
	int			lineHeight;
	//lowest and highest pixel to fill (du mur) in current stripe
	int			drawStart;
	int			drawEnd;
	int			color;
}				t_ray;

int				init_ray(int i, int resX, t_cord_f plane, t_ray *ray);
void			set_pos_dir_in_ray(t_ray *ray, t_param params);
int				compute_sideDist_step(t_ray *ray);
int				perform_dda(char **map, t_ray *ray);
int				compute_wall(int resY, t_ray *ray);
void			print_ray_info(t_ray ray);
int				compute_plane(t_cord_f dir, float FOV, t_cord_f *plane);
void			display_wall(t_img *img, t_ray *ray, int x, t_param params);
void			fill_ceiling_floor(t_img *img, t_param params);
void			compute_texX(t_ray *ray, t_tex tex);
int				display_sprites(t_img *img, t_param params, float *buffer);
void			ft_get_distance(int **order, float **distance, t_param params);
void			ft_sort_distance(int *order, float *distance, int num);
int			compute_floor_ceiling(t_img *img, t_param params);

#endif
