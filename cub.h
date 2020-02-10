#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
#include "libft.h"

typedef struct  s_data {
    void        *img;
    void        *win;
    void        *mlx;
    char        *addr;
    int         bpp;
    int         line_length;
    int         endian;
}               t_data;

typedef struct  s_cord_f{
    float           x;
    float           y;
}               t_cord_f;

typedef struct  s_cord_i{
    int           x;
    int           y;
}               t_cord_i;

typedef struct  s_ray{
    //position du player
    t_cord_f         pos;
    //direction du player
    t_cord_f          dir;
    //rayon
    t_cord_f          vect;
    //distance (fixe): en X entre deux intersections vecticales a des carres, en Y entre deux intersections horizontales a des carres
    t_cord_f          deltaDist;
    //distance initale + incrementee a chaque intersection avec un carre (X est incrementee de deltadistX si intersection verticale, sinon Y est incremente de deltadistY). Permet de savoir si la prochaine intersection sera verticale ou horizontale 
    t_cord_f          sideDist;
    //carre dans lequel le rayon se trouve
    int             mapX;
    int             mapY;
    //direction (+1 / -1) du rayon sur laxe des X et sur l'axe des Y
    int             stepX;
    int             stepY;
    //cote du carré touché (horizontal 0 ou vertical 1)
    int             side;
    int             hit;
    //distance to wall
    float           wallDist;
    //hauteur du mur
    int             lineHeight;
    //lowest and highest pixel to fill (du mur) in current stripe
    int             drawStart;
    int             drawEnd;

    int             color;
}               t_ray;
//vectors
float vect_prod(t_cord_f a, t_cord_f b);
t_cord_f vect_scalar_prod(t_cord_f a, float x);
t_cord_f vect_add(t_cord_f a, t_cord_f b);
t_cord_f vect_normalize(t_cord_f a);
void print_vect(t_cord_f a);

//ray casting
int init_ray(int i, int resX, t_cord_f plane, t_ray *ray);
int compute_sideDist_step(t_ray *ray);
//int perform_DDA(int map[24][24], t_ray *ray);
int perform_DDA(int **map, t_ray *ray);
int compute_wall(int resY, t_ray *ray);
void print_ray_info(t_ray ray);

//minirt
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
int encode_color(int R, int G, int B);
void init_mlx(t_data *img, int xres, int yres);
void fill_screen(t_data *img, int xres, int yres);
void display_wall(t_data *img, t_ray ray, int x);

//parse
int ft_init_parse(int ***map, t_cord_f *pos, t_cord_f *dir, t_cord_i *res, char *filename);
int ft_return_error(int err_index);

int ft_get_map(t_list **lst, char *line);
int ft_fill_map(t_list *lst, int ***map);
int ft_fill_dir_pos(t_cord_f *pos, t_cord_f *dir, int **map);
int ft_check_map(int **map);
int set_dir(t_cord_f *dir, char orientation);
int ft_free_map(int **map);