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

typedef struct  s_game{
    t_ray           *ray;
    t_img           *img;
}               t_game;

#endif