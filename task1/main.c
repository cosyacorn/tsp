#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<math.h>

double dist(double **coords, int point_a, int point_b);
void permute(int *order, int n, int i, FILE *fp);
void free_2d(double **mat, int size);
double route_dist(double **dists, int num_cities, int *route);
int *shortest_route(FILE *fp, double **dists, int num_cities);


int main(int argc, char **argv){

  int nflag, *order, opt, num_cities, i, j;
  double **points, **dists;
  FILE *fp;

  fp=fopen("routes.txt", "w+");
  srand48(time(NULL));
  nflag=0;

  //COMMAND LINE 
  while((opt=getopt(argc,argv,"n:"))!=-1){
    switch(opt){

    case 'n':
      nflag=1;
      num_cities=atoi(optarg);

    }
  }

  if(nflag!=1){
    num_cities=10;
  }


  //INITIALISE THE POINTS
  points=(double**)malloc(sizeof(double*)*num_cities);
  for(i=0;i<num_cities;i++){
    points[i]=(double*)malloc(sizeof(double)*2);
    for(j=0;j<2;j++){
      points[i][j]=drand48();
    }
  }

  //SET UP DIST MATRIX
  dists=(double**)malloc(sizeof(double*)*num_cities);
  for(i=0;i<num_cities;i++){
    dists[i]=(double*)malloc(sizeof(double)*(num_cities));
    for(j=0;j<num_cities;j++){
      dists[i][j]=dist(points, i, j);
    }
  }

  //for(i=0;i
  
  //SET INITIAL ORDERING OF ROUTE
  order=(int*)malloc(sizeof(int)*num_cities);
  for(i=0;i<num_cities;i++){
    order[i]=i;
  }

  //GET ALL PERMUTATIONS AND WRITE TO A FILE
  permute(order, num_cities, 1, fp);

  fclose(fp);
  //have written file and now need to read it
  fp=fopen("routes.txt", "r");

  order=shortest_route(fp, dists, num_cities);

  for(i=0;i<num_cities;i++)
    printf("%d ", order[i]);

  printf("\n");

  fclose(fp);

  free_2d(points, num_cities);
  free_2d(dists, num_cities);
  //free(order);

  return 0;
}
