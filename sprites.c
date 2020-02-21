#include "cub.h"

void	ft_swap_i(int *a, int *b)
{
	int swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

void	ft_swap_f(float *a, float *b)
{
	float swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

int ft_sort_distance(int *order, float *distance, int num)
{
	int j;

  j = 0;
  while (j < num - 1)
  {
    if (distance[j] < distance[j + 1])
    {
      ft_swap_i(&order[j], &order[j + 1]);
      ft_swap_f(&distance[j], &distance[j + 1]);
      j = 0;
    }
    else
      j++;
  }
  return(0);
}

void ft_project_sprites(float *transformY, int *screenX, int *order, t_param params, int i)
{
      float spriteX;
      float spriteY;
      float invDet;
      float transformX;
      t_cord_f *sprite;

      sprite = params.sprites;
      //translate sprite position to relative to camera
      spriteX = sprite[order[i]].x - params.pos.x;
      spriteY = sprite[order[i]].y - params.pos.y;
      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]
      invDet = 1.0 / (params.plane.x * params.dir.y - params.dir.x * params.plane.y); //required for correct matrix multiplication
      transformX = invDet * (params.dir.y * spriteX - params.dir.x * spriteY);
      *transformY = invDet * (-params.plane.y * spriteX + params.plane.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
      *screenX = (int)((params.res.x / 2) * (1 + transformX / *transformY));
      //printf("screenX: %d\n", *screenX);
      //printf("transformY: %f\n", *transformY);
}

int ft_get_distance(int **order, float **distance, int num, t_cord_f *sprite, t_cord_f pos)
{
    int i;
    
    *order = malloc(num * sizeof(int));
    *distance = malloc(num * sizeof(float));
    i = 0;
    while (i < num)
    {
      order[0][i] = i;
      distance[0][i] = (pos.x - sprite[i].x) * (pos.x - sprite[i].x) + (pos.y - sprite[i].y) * (pos.y - sprite[i].y);
      i++;
    }
    return(0);
}

void ft_get_start_end(t_param params, t_cord_i *drawEnd, t_cord_i *drawStart, t_cord_i *spr_sceen_dim, float transformY, int screenX)
{
  int w;
  int h;

  w = params.res.x;
  h = params.res.y;
  
  //calculate height of the sprite on screen
  spr_sceen_dim->y = abs((int)(h / (transformY))); //using "transformY" instead of the real distance prevents fisheye
  //calculate lowest and highest pixel to fill in current stripe
  drawStart->y = -spr_sceen_dim->y / 2 + h / 2;
  if(drawStart->y < 0) 
    drawStart->y = 0;
  drawEnd->y = spr_sceen_dim->y / 2 + h / 2;
  if(drawEnd->y >= h) 
    drawEnd->y = h - 1;

  //calculate width of the sprite
  spr_sceen_dim->x = abs((int)(h / (transformY))); // on part du principe que la texture est carree
  drawStart->x = -spr_sceen_dim->x / 2 + screenX;
  if(drawStart->x < 0) 
    drawStart->x = 0;
  drawEnd->x = spr_sceen_dim->x / 2 + screenX;
  if(drawEnd->x >= w) 
    drawEnd->x = w - 1;
}

int ft_draw_sprites(t_img *img, t_param params, float *buffer, float transformY, int screenX)
{
  t_cord_i drawStart;
  t_cord_i drawEnd;
  t_cord_i spr_tex_dim; // taille de la texture du sprite
  t_cord_i spr_screen_dim; // taille du sprite sur lecran
  int stripe;
  int texX;
  int texY;
  int d;
  int y;
  int color;
  
  spr_tex_dim = params.tex[SPRIT].dim;
  ft_get_start_end(params, &drawEnd, &drawStart, &spr_screen_dim, transformY, screenX);
  //printf("distance: %f\n", transformY);
  //printf("screenX: %d\n", screenX);
  //printf("startx %d, starty %d, endx %d, endy%d\n", drawStart.x, drawStart.y, drawEnd.x, drawEnd.y);
  //loop through every vertical stripe of the sprite on screen
  stripe = drawStart.x;
  while (stripe < drawEnd.x)
  {
    texX = (int)(256 * (stripe - (-spr_screen_dim.x / 2 + screenX)) * spr_tex_dim.x / spr_screen_dim.x) / 256;
    //the conditions in the if are:
    //1) it's in front of camera plane so you don't see things behind you
    //2) it's on the screen (left)
    //3) it's on the screen (right)
    //4) ZBuffer, with perpendicular distance
    if (transformY > 0 && stripe > 0 && stripe < params.res.x && transformY < buffer[stripe])
    {
      y = drawStart.y;
      while (y < drawEnd.y)
      {
        d = (y * 256 - params.res.y * 128 + spr_screen_dim.y * 128); //256 and 128 factors to avoid floats
        texY = ((d * spr_tex_dim.y) / spr_screen_dim.y) / 256;
        color = params.tex[SPRIT].tex[spr_tex_dim.x * texY + texX];
        if ((color & 0x00FFFFFF) != 0) //paint pixel if isnt black, black is the invisible color
          my_mlx_pixel_put(img, stripe, y, color);
        //Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
        //if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible colorstripe++;
        y++;
      }
    }
      stripe++;
  }
  return(0);
}

int display_sprites(t_img *img, t_param params, float *buffer)
{
    //sort sprites from far to close
    int *order;
    float *distance;
    int i;
    float transformY;
    int screenX;
    ft_get_distance(&order, &distance, params.sprite_num, params.sprites, params.pos);
    ft_sort_distance(order, distance, params.sprite_num); // du moins proche au plus proche
    //after sorting the sprites, do the projection and draw them
    i = 0;
    while (i < params.sprite_num)
    {
      ft_project_sprites(&transformY, &screenX, order, params, i);
      ft_draw_sprites(img, params, buffer, transformY, screenX);
      i++;
    }
    free(distance);
    free(order);
    return(0);
}