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
      t_cord_i *sprite;

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

int ft_get_distance(int **order, float **distance, int num, t_cord_i *sprite, t_cord_f pos)
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

void ft_get_start_end(t_param params, t_cord_i *drawEnd, t_cord_i *drawStart, float transformY, int screenX)
{
  int w;
  int h;
  int spriteHeight;
  int spriteWidth;

  w = params.res.x;
  h = params.res.y;
  
  //calculate height of the sprite on screen
  spriteHeight = abs((int)(h / (transformY))); //using "transformY" instead of the real distance prevents fisheye
  //calculate lowest and highest pixel to fill in current stripe
  drawStart->y = -spriteHeight / 2 + h / 2;
  if(drawStart->y < 0) 
    drawStart->y = 0;
  drawEnd->y = spriteHeight / 2 + h / 2;
  if(drawEnd->y >= h) 
    drawEnd->y = h - 1;

  //calculate width of the sprite
  spriteWidth = abs((int)(h / (transformY))); // FAUX ??
  drawStart->x = -spriteWidth / 2 + screenX;
  if(drawStart->x < 0) 
    drawStart->x = 0;
  drawEnd->x = spriteWidth / 2 + screenX;
  if(drawEnd->x >= w) 
    drawEnd->x = w - 1;
}

int ft_draw_sprites(t_img *img, t_param params, float *buffer, float transformY, int screenX)
{
  t_cord_i drawStart;
  t_cord_i drawEnd;
  int stripe;
  int texX;
  
  ft_get_start_end(params, &drawEnd, &drawStart, transformY, screenX);
  printf("distance: %f\n", transformY);
  printf("screenX: %d\n", screenX);
  printf("startx %d, starty %d, endx %d, endy%d\n", drawStart.x, drawStart.y, drawEnd.x, drawEnd.y);
  //loop through every vertical stripe of the sprite on screen
  /*stripe = drawStart.x;
  while (stripe < drawEnd.x)
  {
    int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
    //the conditions in the if are:
    //1) it's in front of camera plane so you don't see things behind you
    //2) it's on the screen (left)
    //3) it's on the screen (right)
    //4) ZBuffer, with perpendicular distance
    if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
    for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
    {
      int d = (y-vMoveScreen) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
      int texY = ((d * texHeight) / spriteHeight) / 256;
      Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
      if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible colorstripe++;
    }
    stripe++;
  }*/
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