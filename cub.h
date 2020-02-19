#ifndef CUB_H
# define CUB_H

#include <stdio.h>
#include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include "libft.h"
#include "mlx_h.h"
#include "parsing.h"
#include "vectors.h"
#include "ray.h"

#define RES_MAX_X 2560
#define RES_MAX_Y 1440
#define FOV (66 * M_PI / 180)
#define SPEED_M 4  // mvmt speed (plus cest grand MOINS on va vite)
#define SPEED_R 5 // rotation speed (plus cest grand PLUS on tourne vite)
#define texW 64
#define texH 64
typedef struct  s_game{
    t_param         params;
    t_img           img;
    int             save;
}               t_game;

int cast_rays(t_game *game);
int ft_press_close(void *param); 
int ft_key_events(int key, t_game *game);
int save_bmp(t_game *game);

#endif
