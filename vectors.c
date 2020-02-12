/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:14:26 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/12 16:14:27 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float vect_prod(t_cord_f a, t_cord_f b)
{
    return(a.x*b.x + a.y*b.y);
}

t_cord_f vect_scalar_prod(t_cord_f a, float x)
{
    t_cord_f b;

    b.x = x*a.x;
    b.y = x*a.y;
    return(b);
}

t_cord_f vect_add(t_cord_f a, t_cord_f b)
{
    t_cord_f c;

    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return(c);
}

t_cord_f vect_normalize(t_cord_f a)
{
    return(vect_scalar_prod(a, 1 / sqrt(vect_prod(a, a))));
}

void print_vect(t_cord_f a)
{
    printf("x: %f\n", a.x);
    printf("y: %f\n", a.y);
}