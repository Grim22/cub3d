/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:14:26 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/14 12:41:34 by bbrunet          ###   ########.fr       */
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

void ft_get_normal(t_cord_f *normal, t_cord_f *dir)
{
    printf("normal\n");
    printf("diry %f\n", dir->y);
    printf("dirx %f\n", dir->x);
    normal->x = -dir->y;
    normal->y = dir->x;
}


void print_vect(t_cord_f a)
{
    printf("x: %f\n", a.x);
    printf("y: %f\n", a.y);
}

void rotate_dir(t_cord_f *vec, float angle)
{
    float tmpx;
    float tmpy;

    //printf("initial x: %f\n", *x);
    //printf("initial y: %f\n", *y);
    angle = angle * M_PI / 180;
    tmpx = vec->x;
    tmpy = vec->y;
    vec->x = cos(angle) * tmpx - sin(angle) * tmpy;
    vec->y = sin(angle) * tmpx + cos(angle) * tmpy;
    //printf("final x: %f\n", *x);
    //printf("final y: %f\n", *y);
}