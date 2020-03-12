/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:40:24 by bbrunet           #+#    #+#             */
/*   Updated: 2020/03/05 12:39:52 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_get_longest(t_list *lst)
{
	int		len;
	int		lon;
	char	*c;

	lon = 0;
	while (lst)
	{
		len = 0;
		c = lst->content;
		while (c[len])
			len++;
		if (len > lon)
			lon = len;
		lst = lst->next;
	}
	return (lon);
}

int		ft_fill_map_2(t_list *lst, char ***map, int lon)
{
	char	*c;
	int		i;
	int		j;
	int		len;

	i = 0;
	while (lst)
	{
		c = lst->content;
		len = ft_strlen(c);
		(*map)[i] = malloc((lon + 1) * sizeof(char));
		j = -1;
		while (++j < len)
			(*map)[i][j] = c[j];
		j = j - 1;
		while (++j < lon)
			(*map)[i][j] = ' ';
		(*map)[i][j] = 0;
		lst = lst->next;
		i++;
	}
	(*map)[i] = 0;
	return (0);
}

int		ft_line_is_map(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != '2' && line[i] != ' '
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != 'S' && line[i] != 'N')
			return (0);
		i++;
	}
	return (1);
}
