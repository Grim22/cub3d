/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:40:24 by bbrunet           #+#    #+#             */
/*   Updated: 2020/03/03 15:26:44 by bbrunet          ###   ########.fr       */
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

int		ft_check_map_spacing(t_list *lst)
{
	char	*c;
	int		i;

	while (lst)
	{
		c = lst->content;
		i = 0;
		while (c[i])
		{
			if (i % 2 == 1 && c[i] != ' ')
				return (-1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

void	ft_str_space_to_zero(char *c)
{
	int i;

	i = 0;
	if (ft_strlen(c) < 3)
		return ;
	while (c[i + 2])
	{
		if (c[i] == ' ' && c[i + 1] == ' ' && c[i + 2] == ' ')
			c[i + 1] = '8';
		i++;
	}
}

int		ft_make_map_line(t_list *lst)
{
	char *c;

	if (ft_check_map_spacing(lst) == -1)
		return (-1);
	while (lst)
	{
		c = lst->content;
		ft_str_space_to_zero(c);
		c = ft_str_del_1_sur_2(c);
		lst = lst->next;
	}
	return (0);
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
			(*map)[i][j] = '8';
		(*map)[i][j] = 0;
		lst = lst->next;
		i++;
	}
	(*map)[i] = 0;
	return (0);
}
