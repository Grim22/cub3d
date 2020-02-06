#include "cub.h"

int compute_plane(t_cord dir, float FOV, t_cord *plane)
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
    //int mapW = 24;
    //int mapH = 24;
    int resX = 640; // a recuperer
    int resY = 480;
    t_cord plane;
    t_ray ray;
    float FOV;
    int bool_x;
    int bool_y;
    int i;
    int map[24][24] ={
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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

    // position (a recuperer dans le fichier)
    ray.pos.x = 1;
    ray.pos.y = 2;
    // dir correspond a W (a recuperer dans le fichier). Valeurs possibles (1, 0), (-1, 0), (0, -1), (0, 1)
    ray.dir.x = 0;
    ray.dir.y = 1;

    FOV = 66; // a choisir nous meme
    FOV = FOV * M_PI / 180;
    
    compute_plane(ray.dir, FOV, &plane);
    
    i = resX;
    while(i <= resX)
    {
        init_ray(i, resX, plane, &ray);
        compute_sideDist_step(&ray);
        perform_DDA(map, &ray);
        compute_wall(resY, &ray);
        printf("mapX %d\n", ray.mapX);
        printf("mapY %d\n", ray.mapY);
        printf("dist %f\n", ray.wallDist);
        printf("height %d\n", ray.lineHeight);
        printf("start %d\n", ray.drawStart);
        printf("end %d\n", ray.drawEnd);
        i++;
    }
}