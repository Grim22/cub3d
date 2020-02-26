/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 13:56:43 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/26 18:04:03 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

int		ft_line_is_1(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

void	ft_init_textures(t_param *params)
{
	int i;

	i = 0;
	while (i < 5)
	{
		params->tex[i].path = NULL;
		params->tex[i].tex = NULL;
		i++;
	}
	params->ceiling.path = NULL;
	params->ceiling.tex = NULL;
	params->floor.path = NULL;
	params->floor.tex = NULL;
}

void	ft_init_params(t_param *params, t_list **lst)
{
	*lst = NULL;
	params->map = NULL;
	params->sprites = NULL;
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
	params->save = 0;
	ft_init_textures(params);
}
