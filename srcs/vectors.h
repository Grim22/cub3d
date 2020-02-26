/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:02:49 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/26 18:08:16 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <math.h>

typedef struct	s_cord_f
{
	float	x;
	float	y;
}				t_cord_f;

float			vect_prod(t_cord_f a, t_cord_f b);
t_cord_f		vect_scalar_prod(t_cord_f a, float x);
t_cord_f		vect_add(t_cord_f a, t_cord_f b);
t_cord_f		vect_normalize(t_cord_f a);
void			print_vect(t_cord_f a);
void			rotate_dir(t_cord_f *vec, float angle);
void			ft_get_normal(t_cord_f *normal, t_cord_f *dir);

#endif
