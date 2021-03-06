/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:12:34 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/26 16:45:06 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_fill_col(int indice, char **words, int *colc, int *colf)
{
	int		i;
	char	**str;

	i = 0;
	while (words[i])
		i++;
	if (i != 2)
		return (-1);
	str = ft_split(words[1], ',');
	i = 0;
	while (str[i])
		i++;
	if (i != 3 || !ft_isdigit_str(str[0])
		|| !ft_isdigit_str(str[1]) || !ft_isdigit_str(str[2]))
		return (-1);
	if (indice == 3)
		*colf = encode_color(ft_atoi(str[0]), ft_atoi(str[1]), ft_atoi(str[2]));
	else
		*colc = encode_color(ft_atoi(str[0]), ft_atoi(str[1]), ft_atoi(str[2]));
	free(str[0]);
	free(str[1]);
	free(str[2]);
	free(str);
	return (0);
}

int	ft_fill_res(char **words, t_cord_i *reso)
{
	int i;

	i = 0;
	while (words[i])
		i++;
	if (i != 3 || !ft_isdigit_str(words[1]) || !ft_isdigit_str(words[2]))
		return (-1);
	if (ft_atoi(words[1]) < RES_MAX_X)
		reso->x = ft_atoi(words[1]);
	else
		reso->x = RES_MAX_X;
	if (ft_atoi(words[2]) < RES_MAX_Y)
		reso->y = ft_atoi(words[2]);
	else
		reso->y = RES_MAX_Y;
	return (0);
}

int	ft_fill_text_path(int indice, char **words, t_param *params)
{
	int i;

	i = 0;
	while (words[i])
		i++;
	if (i != 2)
		return (-1);
	i = 5;
	while (i < 10)
	{
		if (indice == i)
		{
			if (params->tex[i - 5].path)
				free(params->tex[i - 5].path);
			if (!(params->tex[i - 5].path = ft_strdup(words[1])))
				return (-1);
			return (i - 5);
		}
		i++;
	}
	return (-1);
}

int	ft_fill_text(int indice, char **words, t_param *params)
{
	int tex_num;

	if ((tex_num = ft_fill_text_path(indice, words, params)) == -1)
		return (-1);
	return (0);
}

int	ft_fill_params(int indice, char *line, t_param *params)
{
	char	**words;
	int		i;
	int		ret;

	words = ft_split(line, ' ');
	if (indice == 2)
		ret = ft_fill_res(words, &(params->res));
	else if (indice == 3 || indice == 4)
		ret = ft_fill_col(indice, words, &(params->col_c), &(params->col_f));
	else
		ret = ft_fill_text(indice, words, params);
	if (ret == -1)
	{
		ft_putstr_fd("Error\nWrong line:\n", 1);
		ft_putstr_fd(line, 1);
		return (-1);
	}
	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (0);
}
