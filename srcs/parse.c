/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:13:28 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/28 10:18:15 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_scan_id(char *line)
{
	if (line[0] == 0)
		return (0);
	if (line[0] == '1')
		return (1);
	if (ft_strlen(line) < 3)
		return (-1);
	if (line[0] == 'R' && line[1] == 32)
		return (2);
	if (line[0] == 'S' && line[1] == 32)
		return (5);
	if (line[0] == 'F' && line[1] == 32)
		return (3);
	if (line[0] == 'C' && line[1] == 32)
		return (4);
	if (line[0] == 'N' && line[1] == 'O' && line[2] == 32)
		return (6);
	if (line[0] == 'S' && line[1] == 'O' && line[2] == 32)
		return (7);
	if (line[0] == 'W' && line[1] == 'E' && line[2] == 32)
		return (8);
	if (line[0] == 'E' && line[1] == 'A' && line[2] == 32)
		return (9);
	return (-1);
}

void	ft_fill_last(char *line, unsigned char *last)
{
	if (ft_strlen(line) < 2)
		return ;
	if (line[0] == 'R' && line[1] == 32)
		*last = *last | _R;
	if (line[0] == 'S' && line[1] == 32)
		*last = *last | _S;
	if (line[0] == 'F' && line[1] == 32)
		*last = *last | _F;
	if (line[0] == 'C' && line[1] == 32)
		*last = *last | _C;
	if (line[0] == 'N' && line[1] == 'O' && line[2] == 32)
		*last = *last | _NO;
	if (line[0] == 'S' && line[1] == 'O' && line[2] == 32)
		*last = *last | _SO;
	if (line[0] == 'W' && line[1] == 'E' && line[2] == 32)
		*last = *last | _WE;
	if (line[0] == 'E' && line[1] == 'A' && line[2] == 32)
		*last = *last | _EA;
}

int		ft_scan_last_error(int ret, int map_on, int last, int map_end)
{
	if ((map_on == 0 && ret == 1 && last != 255))
	{
		ft_putstr_fd("Error\nAll parameters must be given before map", 1);
		return (-1);
	}
	if (map_on && ret != 1 && ret)
	{
		ft_putstr_fd("Error\nParameter(s) given after map or inside map", 1);
		return (-1);
	}
	if (map_on && map_end == 0 && ret == 0)
	{
		ft_putstr_fd("Error\nEmpty line inside map", 1);
		return (-1);
	}
	return (0);
}

int		ft_scan(char *line)
{
	static unsigned char	last;
	static int				map_on;
	int						ret;
	static int				map_end;

	if ((ret = ft_scan_id(line)) == -1)
	{
		ft_putstr_fd("Error\nWrong line:\n", 1);
		ft_putstr_fd(line, 1);
		return (-1);
	}
	ft_fill_last(line, &last);
	if (ft_scan_last_error(ret, map_on, last, map_end) == -1)
		return (-1);
	if (map_on && ft_line_is_1(line))
		map_end = 1;
	if (ret == 1)
		map_on = 1;
	return (ret);
}

int		ft_init_parse(t_param *params, char *filename)
{
	char	*line;
	int		i;
	int		fd;
	t_list	*lst;

	ft_init_params(params, &lst);
	if ((fd = check_filename(filename)) == -1)
		return (-1);
	while ((i = get_next_line(fd, &line)))
	{
		if (i == -1 || (i = ft_scan(line)) == -1)
			return (-1);
		if (i == 1)
			ft_lstadd_back(&lst, ft_lstnew(line));
		else
		{
			if (i && ft_fill_params(i, line, params) == -1)
				return (-1);
			free(line);
		}
	}
	if (ft_fill_check_map(&lst, &(params->map), params) == -1)
		return (-1);
	//ft_inverse_map(&(params->map));
	close(fd);
	return (1);
}
