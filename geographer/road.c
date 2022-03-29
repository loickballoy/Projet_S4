#include "../assign/assign.h"
#include "err.h"
#include "road.h"
#include <stdio.h>

int updateConnected(struct map *map, int x, int y)
{
  struct cell* tempcell = map->cells + (x + y * map->maxWidth);
  if(x != 0)
    (tempcell-1)->isRoadConnected = 1;
  if(y != 0)
    (tempcell-map->maxWidth)->isRoadConnected = 1;
  if(x != map->maxWidth)
    (tempcell+1)->isRoadConnected = 1;
  if(y != map->maxHeight)
    (tempcell+map->maxWidth)->isRoadConnected = 1;
  return 1;
}

void square(struct map *map, int x, int y, int len, int *a, int *b)
{
  int startx = x-len/2 < 0 ? 0 : x-len/2;
  int starty = y-len/2 < 0 ? 0 : y-len/2;
  struct cell* tempcell = map->cells + (startx + starty * map->maxWidth);
  int endx = (x + len/2) >= map->maxWidth ? map->maxWidth-1 : x + len/2;
  int endy = (y + len/2) >= map->maxHeight ? map->maxHeight-1 : (y + len/2) ;
  //printf("startx = %i  || starty = %i || endx = %i || endy = %i \n",startx,starty,endx,endy);

  for(int i = 0; i <= endx-startx; i++)
  {
    if((tempcell + i)->type == 6)
    {
      *a = i;
      *b = starty;
      printf(" hey hey trouver 1");
      return;
    }
    //(tempcell + i)->type = 13;
  }
  for(int j = 0; j <= endy-starty; j++)
  {
    if((tempcell + j * map->maxWidth)->type == 6)
    {
      *a = startx;
      *b = j;
      printf(" hey hey trouver 2");
      return;
    }
    //(tempcell + j * map->maxWidth)->type = 12;
  }


  tempcell = map->cells + (startx + (endy * map->maxWidth));
  for(int i = 0; i <= endx-startx; i++)
  {
    if((tempcell + i)->type == 6)
    {
      *a = i;
      *b = endy;
      printf(" hey hey trouver 3");
      return;
    }
    //(tempcell+i)->type = 14;
  }

  tempcell = map->cells + (endx + (starty * map->maxWidth));
  for(int j = 0; j <= endy-starty; j++)
  {
    if((tempcell + j * map->maxWidth)->type == 6)
    {
      *a = endx;
      *b = j;
      printf(" hey hey trouver 4");
      return;
    }
    //(tempcell + j * map->maxWidth)->type = 11;
  }
  *a = 0;
  *b = 0;
  return;
}

void createWay(struct map* map, int x, int y, int a, int b)//x,y = cell from || a,b = cell to
{
  int **building_value = load_building_value();
  struct cell* tempcell = map->cells;
  printf(" x = %i || y = %i || a = %i || b = %i \n",x,y,a,b);
  if(y < b)
  {
    for(int i = b-1; y != i; i--)
    {
      tempcell += a + i*map->maxWidth;
      if(tempcell->type != -1 && tempcell->type != 6)
      {
        reverseUpdateAround(map, a, i, building_value);
        tempcell->type = 6;
      }
      else
        tempcell->type = 6;
    }
  }
  else
  {
    for(int i = b; y != i; i++)
    {
      tempcell += a + i*map->maxWidth;
      if(tempcell->type != -1 && tempcell->type != 6)
      {
        reverseUpdateAround(map, a, i, building_value);
        tempcell->type = 6;
      }
      else
        tempcell->type = 6;
    }
  }
  if(x < a)
  {
    for(int j = a; x != j; j--)
    {
      tempcell += j + y*map->maxWidth;
      if(tempcell->type != -1 && tempcell->type != 6)
      {
        reverseUpdateAround(map, j, y, building_value);
        tempcell->type = 6;
      }
      else
        tempcell->type = 6;
    }
  }
  else
  {
    for(int j = a; x != j; j++)
    {
      tempcell += j + y*map->maxWidth;
      if(tempcell->type != -1 && tempcell->type != 6)
      {
        reverseUpdateAround(map, j, y, building_value);
        tempcell->type = 6;
      }
      else
        tempcell->type = 6;
    }
  }
  return;
}

void roadToConnect(struct map *map, int x, int y)
{
  int a = 0;
  int b = 0;
  int far = 0;
  while(a == 0/* && far < 20 pour les tests*/)//find the nearest road to connect
  {
    square(map, x, y, 3+far*2, &a, &b);
    if(a != 0)
    {
      printf("hey hey we found a = %i || b = %i\n", a,b);
      (map->cells+ a + b*map->maxWidth)->type = 0;
    }
    far++;
  }
  printMatrix(map);
  createWay(map, x, y, a, b);//place roads need to add the replacement on buildinglist
  return;
}
