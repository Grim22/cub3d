/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:48:47 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/24 10:50:20 by bbrunet          ###   ########.fr       */
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

int		check_filename(char *filename)
{
	char	*ext;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		perror("Error\nWrong argument: ");
		return (-1);
	}
	ext = ft_substr(filename, ft_strlen(filename) - 4, ft_strlen(filename));
	if (ft_strncmp(ext, ".cub", 4))
	{
		ft_putstr_fd("Error\nFile extension must be .cub", 1);
		return (-1);
	}
	free(ext);
	return (fd);
}

int		ft_free_params(t_param params)
{
	int		i;
	char	**map;

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
	i = 0;
	while (i < 5)
	{
		if (params.tex[i].path)
			free(params.tex[i].path);
		if (params.tex[i].tex)
			free(params.tex[i].tex);
		i++;
	}
	return (0);
}

void	ft_init_params(t_param *params)
{
	int i;

	i = 0;
	params->map = NULL;
	params->sprites = NULL;
	while (i < 5)
	{
		params->tex[i].path = NULL;
		params->tex[i].tex = NULL;
		i++;
	}
}
