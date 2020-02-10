#include "cub.h"

int main(int ac, char **av)
{
    t_cord_i res;
    t_cord_f plane;
    t_ray ray;
    float FOV;
    int i;
    t_data img;
    int **map;

    if (ac > 3 || ac < 2)
    {
        ft_putstr_fd("Error \n: Wrong number of arguments\n", 1);
        return(1);
    }
    if ((i = ft_init_parse(&map, &(ray.pos), &(ray.dir), &res, av[1])) != 1)
        return(0);
    //ft_print_map(map);
    //print_ray_info(ray);
    
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
        //printf("i: %d\n", i);
        compute_wall(res.y, &ray);
        display_wall(&img, ray, i);
        //if (i % 25 == 0)
            //print_ray_info(ray);
        i++;
    }
    ft_free_map(map);
    mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_loop(img.mlx);
}