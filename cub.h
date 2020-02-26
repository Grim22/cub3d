/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:45:42 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/26 12:27:17 by bbrunet          ###   ########.fr       */
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

# define RES_MAX_X 2560
# define RES_MAX_Y 1440
# define FOV 66
# define SPEED_M 6 // mvmt speed (plus cest grand MOINS on va vite)
# define SPEED_R 3 // rotation speed (plus cest grand PLUS on tourne vite)
# define ERROR -1
# define SUCCESS 1
# define CEILING "./textures/sky_1.xpm"
# define FLOOR "./textures/floor_1.xpm"

typedef struct	s_game
{
	t_param	params;
	t_img	img;
	int		save;
}				t_game;

int				cast_rays(t_game *game);
int				ft_press_close(void *param);
int				ft_set_events_params(t_game *game);
int				ft_press_events(int key, t_param *params);
int				ft_release_events(int key, t_param *params);
void			ft_key_a(t_game *game, t_cord_f norm, t_cord_f *pos);
void			ft_key_d(t_game *game, t_cord_f norm, t_cord_f *pos);
void			ft_key_w(t_game *game, t_cord_f dir, t_cord_f *pos);
void			ft_key_s(t_game *game, t_cord_f dir, t_cord_f *pos);
int				save_bmp(t_game *game);
int				ft_get_textures(t_game *game);
int				exit_game(int ret, char *message, int parse, t_game *game);
int				ft_check_save(char *arg, t_game *game);
#endif
