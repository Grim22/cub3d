#include "cub.h"

//from Glagan github

static void set_int_in_char(char *ptr, int nbr)
{
	int *ptr_i;

	ptr_i = (int *)ptr;
	*ptr_i = nbr;
}

static int  write_bmp_header(int fd, int filesize, t_game *game)
{
	int				i;
	char			bmpfileheader[54];

// pourquoi unsigned char ?
	printf("header\n");
	i = 0;
	while (i < 54)
		bmpfileheader[i++] = 0; // met les champs a zero par defaut
	bmpfileheader[0] = 'B';
	bmpfileheader[1] = 'M';
	set_int_in_char(bmpfileheader + 2, filesize); // a ladrresse bmp[2] on veut un int (4 bytes) qui contient la taille totale du fichier
	printf("fsize: %d\n", filesize);
	bmpfileheader[10] = (char)54; // offset
	bmpfileheader[14] = (char)40; // 54 - 14
	set_int_in_char(bmpfileheader + 18, game->params.res.x); // img width
	set_int_in_char(bmpfileheader + 22, game->params.res.y); // img height
	bmpfileheader[26] = (char)(1); // planes
	bmpfileheader[28] = (char)(24); // en mode 24 bpp (pas de alpha precise dans la map !)
	if (write(fd, bmpfileheader, 54) < 0)
        return(0);
    return(1);
}

static int get_color(t_game *game, int x, int y) // recupere la couleur du pixel en (x,y) (coordonnees 0,0 en bas a gauche de limage)
{
	int	rgb;
	int	color;

	my_mlx_pixel_get(game->img.img, x, y, &color);
    //color = *(int*)(game->img.addr
	//		+ (4 * game->params.res.x * (game->params.res.y - 1 - y))
	//		+ (4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF); // on met R/G et B sur les 3 premiers bytes de l'int (<> initialement l'int est de type ARGB)
	return (rgb);
}

int write_bmp_data(int file, t_game *game)
{
	int i;
	int j;
	int color;
	int zero;

	i = 0;
	zero = 0;
	while(i < game->params.res.x)
	{
		j = 0;
		while(j <= game->params.res.y)
		{
			if (j == game->params.res.y && game->params.res.y % 4)
			{
				printf("padj: %d\n", j);
				write(file, &zero, game->params.res.y % 4);
			}
			else
			{
				color = get_color(game, i, j);
				write(file, &color, 3); // ecrit en 3*i + 3*j (sachant que la premiere adresse est celle du point en bas a gauche de limage, la deuxieme celui en (0,1)...)
			}
			j++;
		}
		i++;
	}
	return(1);
}

int     save_bmp(t_game *game)
{
	int			filesize;
	int			file;

	filesize = 54 + (((3 * game->params.res.y + (game->params.res.y % 4)) * game->params.res.x));
	if ((file = open("screenshot.bmp", O_RDWR | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU)) < 0)
		return (0);
	if (!write_bmp_header(file, filesize, game))
		return (0);
	if (!write_bmp_data(file, game))
		return (0);
	close(file);
	return (1);
}