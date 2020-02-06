#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mlx.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct  s_cord{
    float           x;
    float           y;
}               t_cord;

typedef struct  s_ray{
    //position du player
    t_cord          pos;
    //direction du player
    t_cord          dir;
    //rayon
    t_cord          vect;
    //distance (fixe): en X entre deux intersections vecticales a des carres, en Y entre deux intersections horizontales a des carres
    t_cord          deltaDist;
    //distance initale + incrementee a chaque intersection avec un carre (X est incrementee de deltadistX si intersection verticale, sinon Y est incremente de deltadistY). Permet de savoir si la prochaine intersection sera verticale ou horizontale 
    t_cord          sideDist;
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

float vect_prod(t_cord a, t_cord b);
t_cord vect_scalar_prod(t_cord a, float x);
t_cord vect_add(t_cord a, t_cord b);
t_cord vect_normalize(t_cord a);
void print_vect(t_cord a);

int init_ray(int i, int resX, t_cord plane, t_ray *ray);
int compute_sideDist_step(t_ray *ray);
int perform_DDA(int map[24][24], t_ray *ray);
int compute_wall(int resY, t_ray *ray);