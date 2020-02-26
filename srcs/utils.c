/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:48:47 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/26 13:57:23 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_check_save(char *arg, t_game *game)
{
	if (ft_strncmp(arg, "--save", 7))
	{
		ft_putstr_fd("Error\nWrong second argument", 1);
		return (-1);
	}
	game->save = 1;
	return (0);
}

int		exit_game(int ret, char *message, int parse, t_game *game)
{
	if (message)
	{
		ft_putstr_fd("Error\n", 1);
		ft_putstr_fd(message, 1);
	}
	if (parse)
		ft_free_params(game->params);
	return (ret);
}

void	ft_free_params_tex(t_param params)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		if (params.tex[i].path)
			free(params.tex[i].path);
		if (params.tex[i].tex)
			free(params.tex[i].tex);
		i++;
	}
	if (params.ceiling.path)
		free(params.ceiling.path);
	if (params.ceiling.tex)
		free(params.ceiling.tex);
	if (params.ceiling.tex)
		free(params.floor.path);
	if (params.floor.tex)
		free(params.floor.tex);
}

void	ft_free_params(t_param params)
{
	char	**map;
	int		i;

	map = params.map;
	i = 0;
	if (map)
	{
		while ((map)[i])
			free((map)[++i]);
		free(map);
	}
	if (params.sprites)
		free(params.sprites);
	ft_free_params_tex(params);
}

void	ft_init_params(t_param *params)
{
	int i;

	i = -1;
	params->map = NULL;
	params->sprites = NULL;
	while (++i < 5)
	{
		params->tex[i].path = NULL;
		params->tex[i].tex = NULL;
	}
	params->ceiling.path = NULL;
	params->ceiling.tex = NULL;
	params->floor.path = NULL;
	params->floor.tex = NULL;
	params->key_a = 0;
	params->key_w = 0;
	params->key_d = 0;
	params->key_s = 0;
	params->key_left = 0;
	params->key_right = 0;
	params->key_esc = 0;
	params->key_up = 0;
	params->key_down = 0;
	params->texture_floor = 0;
	params->jump = 2;
}
