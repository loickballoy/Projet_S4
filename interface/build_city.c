#include <stdio.h>
#include <err.h>
#include <stdlib.h>


char **genMat(int DIM)
{
  char **matrice;

  matrice = malloc(sizeof(char *)* DIM);

  for(int k = 0; k < DIM; k++)
    {
      matrice[k] = malloc(sizeof(char *) * DIM);
    }
  
  for(int i = 0; i < DIM; i++)
    {
      for(int j =0; j < DIM; j++)
	{
	  if(j%2 != 0)
	    matrice[i][j] = 'H';
	  if(j%2 == 0)
	    matrice[i][j] = 'P';
	  if(j%5 == 0)
	    matrice[i][j] = 'S';
	}
    }
  return matrice;
}


void build_city()
{

  printf("Bienvenue sur CityMap !\n");
  printf("Rentrez les différents paramètres et nous vous générerons une ville\n");

  int nb_hab;
  int budget;
  int sec;
  int edu;
  int env;

  printf("\nNombre habitants : ");
  scanf("%d", &nb_hab);

  printf("\nBudget : ");
  scanf("%d", &budget);

  printf("\nSécurité : ");
  scanf("%d", &sec);

  printf("\nEducation : ");
  scanf("%d", &edu);

  printf("\nEnvironnement : ");
  scanf("%d", &env);
  printf("\n");
  
  //list batiment
  
  //execute les programmes de génération de ville

  //affiche l'image de la ville

  int DIM = 15;

  
  printf("VILLE :\n");
  
  char **matrice = genMat(DIM);

  for(int i = 0; i < DIM; i++)
    {
      printf("\n\n");
      for(int j =0; j < DIM; j++)
	{
	  if(j == DIM-1)
	    printf("%c", matrice[i][j]);
	  else
	    printf("%c - ", matrice[i][j]);
	  
	}
    }

  for(int i = 0; i < DIM; i++)
    {
      free(matrice[i]);
    }
  free(matrice);

  printf("\n");

  
}



int main()
{
  build_city();
}