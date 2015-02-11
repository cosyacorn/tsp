double route_dist(double **dists, int num_cities, int *route){
  
  double tot;
  int i;

  tot=0.0;

  tot+=dists[route[0]][route[num_cities-1]];

  for(i=0;i<num_cities-1;i++){
    tot+=dists[route[i]][route[i+1]];
  }

  return tot;

}
