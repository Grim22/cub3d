#include "cub.h"

int compute_plane(t_cord_f dir, float FOV, t_cord_f *plane)
{
    // determination du vecteur plan image:
        // dir: perpendiculaire a direction du joueur = dir.
        // valeur: plane / 2
    int bool_x = 0;
    int bool_y = 0;
    
    if (dir.x)
        bool_y = 1;
    else
        bool_x = 1;
    plane->x = bool_x * tan(FOV/2);
    plane->y = bool_y * tan(FOV / 2);
    //printf("py: %f\n", plane->y);
    //printf("px: %f\n", plane->x);
    return(0);
}

int main()
{
    t_cord_i res;
    t_cord_f plane;
    t_ray ray;
    float FOV;
    int i;
    t_data img;
    int **map1;

    // position (a recuperer dans le fichier)
    // attention: les x correspondent aux lignes et les y aux colonnes. la coordonee (0,0) est en haut a gauche de la carte
    // dir correspond a W (a recuperer dans le fichier). Valeurs possibles (1, 0):Sud, (-1, 0):Nord, (0, -1):W, (0, 1):E
    
    int map[24][24]=
    {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    if ((i = ft_init_parse(&map1, &(ray.pos), &(ray.dir), &res)) != 1)
        return(ft_return_error(i));
    print_ray_info(ray);
    FOV = 66; // a choisir nous meme
    FOV = FOV * M_PI / 180;
    
    compute_plane(ray.dir, FOV, &plane);

    init_mlx(&img, res.x, res.y);
    fill_screen(&img, res.x, res.y); // background color

    i = 0;
    while(i < res.x)
    {
        init_ray(i, res.x, plane, &ray);
        compute_sideDist_step(&ray);
        perform_DDA(map, &ray);
        compute_wall(res.y, &ray);
        display_wall(&img, ray, i);
        //if (i % 25 == 0)
           // print_ray_info(ray);
        i++;
    }
    mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_loop(img.mlx);
}