/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:06:35 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/28 14:31:52 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_key_left(t_cord_f *dir, t_cord_f *plane)
{
	//rotate_dir(dir, -SPEED_R); // original
	//rotate_dir(plane, -SPEED_R); // original
	rotate_dir(dir, SPEED_R);
	rotate_dir(plane, SPEED_R);
}

void	ft_key_right(t_cord_f *dir, t_cord_f *plane)
{
	//rotate_dir(dir, SPEED_R); // original
	//rotate_dir(plane, SPEED_R); // original
	rotate_dir(dir, -SPEED_R);
	rotate_dir(plane, -SPEED_R);
}

int		ft_key_esc(void)
{
	printf("Bye !\n");
	exit(0);
}
