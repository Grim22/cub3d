/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:14:12 by bbrunet           #+#    #+#             */
/*   Updated: 2020/03/05 12:48:00 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_fill_map(t_list *lst, char ***map)
{
	int		lon;

	*map = malloc((ft_lstsize(lst) + 1) * sizeof(char *));
	lon = ft_get_longest(lst);
	ft_fill_map_2(lst, map, lon);
	return (0);
}

int		set_dir(t_cord_f *dir, char orientation)
{
	if (orientation == 'N')
	{
		dir->x = -1.01;
		dir->y = 0;
	}
	if (orientation == 'S')
	{
		dir->x = 1.01;
		dir->y = 0;
	}
	if (orientation == 'W')
	{
		dir->x = 0;
		dir->y = -1.01;
	}
	if (orientation == 'E')
	{
		dir->x = 0;
		dir->y = 1.01;
	}
	return (0);
}

int		ft_fill_dir_pos(t_cord_f *pos, t_cord_f *dir, char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'S' || map[i][j] == 'N'
			|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				pos->x = i + 0.5;
				pos->y = j + 0.5;
				set_dir(dir, (char)map[i][j]);
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (0);
}

int		ft_fill_plane(t_cord_f *plane, t_cord_f dir)
{
	float fov_gradient;

	fov_gradient = FOV * M_PI / 180;
	plane->x = -dir.y * tan(fov_gradient / 2);
	plane->y = dir.x * tan(fov_gradient / 2);
	return (0);
}

int		ft_fill_check_map(t_list **lst, char ***map, t_param *params)
{
	if (*lst == NULL)
	{
		ft_putstr_fd("Error\nNo map", 1);
		return (-1);
	}
	if (ft_fill_map(*lst, map) == -1)
		return (-1);
	ft_lstclear(lst, &free);
	if (ft_check_map(*map) == -1)
		return (-1);
	ft_fill_dir_pos(&(params->pos), &(params->dir), *map);
	ft_fill_plane(&(params->plane), params->dir);
	ft_fill_sprites(&(params->sprites), &(params->sprite_num), *map);
	(*map)[(int)params->pos.x][(int)params->pos.y] = '0';
	return (0);
}
