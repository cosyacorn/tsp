#include<stdio.h>
#include<stdlib.h>
double route_dist(double **dists, int num_cities, int *route);

int *shortest_route(FILE *fp, double **dists, int num_cities){

  int i, *route, *shortest;
  double dist, best;

  route=(int*)malloc(sizeof(int)*num_cities);
  shortest=(int*)malloc(sizeof(int)*num_cities);
  for(i=0;i<num_cities;i++){
    fscanf(fp, "%d ", &route[i]);
    //printf("%d ", route[i]);
  }
  //printf("\n");

  for(i=0;i<num_cities;i++)
    shortest[i]=route[i];

  best=route_dist(dists, num_cities, shortest);

  while(!feof(fp)){
    for(i=0;i<num_cities;i++){
      fscanf(fp, "%d ", &route[i]);
    }
    //printf("\n");
    dist=route_dist(dists, num_cities, route);
    if(dist<best){
      best=dist;
      for(i=0;i<num_cities;i++)
	shortest[i]=route[i];
    }
  }



  return shortest;

  free(route);
  free(shortest);

  
}
