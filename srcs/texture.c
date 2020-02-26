#include "cub.h"

int ft_xpm_to_inttab(int **tex, t_cord_i *dim, char *path, void *mlx_ptr)
{
    t_img img;
    int i;
    int j;
		
    img.mlx = mlx_ptr;
	if (!(img.img = mlx_xpm_file_to_image(img.mlx, path, &dim->x, &dim->y)))
        return(-1);
	if (!(*tex = malloc(dim->x * dim->y * sizeof(int))))
        return(-1);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	i = 0;
	while(i < dim->x)
	{
		j = 0;
		while(j < dim->y)
		{
            my_mlx_pixel_get(img, i, j, &tex[0][dim->x * j + i]);
			j++;
		}
		i++;
	}
    return(0);
}

int ft_get_textures(t_game *game)
{
    int i;
    t_tex *tex;

    tex = game->params.tex;
    i = 0;
    while (i < 5)
    {
        if (ft_xpm_to_inttab(&tex[i].tex, &tex[i].dim, tex[i].path, game->img.mlx) == -1)
        {
            ft_putstr_fd("Error\nUnable to use texture: ", 1);
            ft_putstr_fd(tex[i].path, 1);
            return(-1);
        }
        i++;
    }
    game->params.ceiling.path = ft_strdup(CEILING);
    game->params.floor.path = ft_strdup(FLOOR);
    if (ft_xpm_to_inttab(&game->params.ceiling.tex , &game->params.ceiling.dim, game->params.ceiling.path, game->img.mlx) == -1
	|| ft_xpm_to_inttab(&game->params.floor.tex , &game->params.floor.dim, game->params.floor.path, game->img.mlx) == -1)
	{
		ft_putstr_fd("Error\nUnable to use floor/ceiling texture", 1);
		return (-1);
	}
    return(0);
}
