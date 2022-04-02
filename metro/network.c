#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"

struct Metro
{
    unsigned int label;
    unsigned int x;
    unsigned int y;
    //unsigned int *adjlists;
};

void buildAdjlists(struct Metro *STATIONS, unsigned int nb_stat,
			    double max, Graph g)
{
    for(unsigned int i = 0; i < nb_stat; i++)
    {
        unsigned int x1 = STATIONS[i].x;
        unsigned int y1 = STATIONS[i].y;
        
        for(unsigned int j = 0; j < nb_stat; j++)
        {
            if(i != j)
            {
                unsigned int x2 = STATIONS[j].x;
                unsigned int y2 = STATIONS[j].y;
                
                double a = (double)((x1 - x2) * (x1 - x2));
                double b = (double)((y1 - y2) * (y1 - y2));
                double dist = sqrt(a + b);
                
                if(dist <= max)
                    add_edge(g, i+1, j+1);
                    
	    }
	}
    }
}

int nb_stations(char **matrice, int DIM)
{
  int nb_stat = 0;
  
  for(int i = 0; i < DIM; i++)
    {
      for(int j =0; j < DIM; j++)
	{
            
	  if(matrice[i][j] == '0')
	    nb_stat += 1;
            
	}
    }
  return nb_stat;
}

struct Metro *BuildStations(char **matrice, int DIM, Graph g1)
{

  int nb_stat = nb_stations(matrice, DIM);

  struct Metro *STATIONS = malloc(sizeof(struct Metro) * nb_stat);

  int k = 0;
  

  for(int i = 0; i < DIM; i++)
    {
      for(int j =0; j < DIM; j++)
	{
	  
	  if(matrice[i][j] == '0')
	    {
	      struct Metro st = {k+1, i, j};
	      add_label(g1, k+1, i, j);
	      STATIONS[k] = st;
	      k += 1;
	    }
	  
	}
    }
  
  return STATIONS;
  
}

void MakeMetro(char **matrice)
{
  int NUMBER_STATIONS; 
  double MAX = 3.8;
  int DIM = 15;

  NUMBER_STATIONS = nb_stations(matrice, DIM);

  Graph g1 = new_graph(NUMBER_STATIONS, false);

  fprintf(g1->graph_file, "\tedge [color=black];\n");
  fprintf(g1->graph_file, "\tnode [color=turquoise, style=filled];\n");

  struct Metro *STATIONS = BuildStations(matrice, DIM, g1);
  
  buildAdjlists(STATIONS, NUMBER_STATIONS, MAX, g1);

  print_graph(g1);
  display_graph(g1);
  erase_graph(g1);
  system("dot -Tpng graph.out -o graph.png");
  
  free(STATIONS);
}

