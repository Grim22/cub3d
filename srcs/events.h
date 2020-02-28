/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:15:44 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/27 10:15:53 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "parsing.h"

int				ft_press_close(void *param);
int				ft_set_events_params(t_game *game);
int				ft_press_events(int key, t_param *params);
int				ft_release_events(int key, t_param *params);
void			ft_key_a(t_game *game, t_cord_f norm, t_cord_f *pos);
void			ft_key_d(t_game *game, t_cord_f norm, t_cord_f *pos);
void			ft_key_w(t_game *game, t_cord_f dir, t_cord_f *pos);
void			ft_key_s(t_game *game, t_cord_f dir, t_cord_f *pos);
void			ft_key_left(t_cord_f *dir, t_cord_f *plane);
void			ft_key_right(t_cord_f *dir, t_cord_f *plane);
int				ft_key_esc(void);

#endif
