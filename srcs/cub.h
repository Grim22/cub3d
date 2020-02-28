/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:45:42 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/27 14:32:23 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx_h.h"
# include "parsing.h"
# include "vectors.h"
# include "ray.h"
# include "events.h"

# define RES_MAX_X 2560
# define RES_MAX_Y 1440
# define FOV 66
# define SPEED_M 6
# define SPEED_R 3
# define ERROR -1
# define SUCCESS 1
# define CEILING "./textures/sky_1.xpm"
# define FLOOR "./textures/floor_1.xpm"

int				cast_rays(t_game *game);
int				save_bmp(t_game *game);
int				exit_game(int ret, char *message, int parse, t_game *game);
int				ft_check_save(char *arg, t_game *game);
#endif
