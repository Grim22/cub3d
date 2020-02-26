/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:53:00 by bbrunet           #+#    #+#             */
/*   Updated: 2020/02/26 15:51:17 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	set_int_in_char(char *ptr, int nbr)
{
	int *ptr_i;

	ptr_i = (int *)ptr;
	*ptr_i = nbr;
}

static int	write_bmp_header(int fd, int filesize, t_game *game)
{
	int		i;
	char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = 0;
	bmpfileheader[0] = 'B';
	bmpfileheader[1] = 'M';
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (char)54;
	bmpfileheader[14] = (char)40;
	set_int_in_char(bmpfileheader + 18, game->params.res.x);
	set_int_in_char(bmpfileheader + 22, game->params.res.y);
	bmpfileheader[26] = (char)(1);
	bmpfileheader[28] = (char)(24);
	if (write(fd, bmpfileheader, 54) < 0)
		return (0);
	return (1);
}

static int	get_color(t_game *game, int x, int y)
{
	int	rgb;
	int	color;

	my_mlx_pixel_get(game->img, x, y, &color);
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

static int	write_bmp_data(int file, t_game *game)
{
	int i;
	int j;
	int color;
	int zero;
	int pad;

	pad = 0;
	if ((game->params.res.x * 3) % 4)
		pad = 4 - ((game->params.res.x * 3) % 4);
	j = game->params.res.y - 1;
	zero = 0;
	while (j >= 0)
	{
		i = 0;
		while (i < game->params.res.x)
		{
			color = get_color(game, i, j);
			write(file, &color, 3);
			if (i == game->params.res.x - 1 && pad)
				write(file, &zero, pad);
			i++;
		}
		j--;
	}
	return (1);
}

int			save_bmp(t_game *game)
{
	int	filesize;
	int	file;
	int	pad;

	pad = 0;
	if ((game->params.res.x * 3) % 4)
		pad = 4 - ((game->params.res.x * 3) % 4);
	filesize = 54 + ((3 * game->params.res.x + pad) * game->params.res.y);
	if ((file = open("screenshot.bmp",
		O_RDWR | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU)) < 0)
		return (0);
	if (!write_bmp_header(file, filesize, game))
		return (0);
	if (!write_bmp_data(file, game))
		return (0);
	close(file);
	return (1);
}
