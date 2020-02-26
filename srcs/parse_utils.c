/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 13:56:43 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/26 13:57:12 by bbrunet          ###   ########.fr       */
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
