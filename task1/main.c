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

  int nflag, fflag, *order, opt, num_cities, i, j;
  double **points, **dists;
  FILE *fp, *points_file;

  srand48(time(NULL));
  nflag=0;
  fflag=0;

  //COMMAND LINE 
  while((opt=getopt(argc,argv,"n:f:"))!=-1){
    switch(opt){

    case 'n':
      nflag=1;
      num_cities=atoi(optarg);
      break;

    case 'f':
      fflag=1;
      points_file=fopen(argv[2], "r");
      break;

    }
  }
 
  //can't have nflag and fflag
  if(nflag==1 && fflag==1){
    printf("Usage: '%s -n <integer>' OR %s -f <file>\n",argv[0], argv[0]);
    return 1;
  }

  //default for no flags given
  if(nflag!=1 && fflag!=1){
    num_cities=10;
  }


 //INITIALISE THE POINTS (not from file)
  if(fflag!=1){
    points=(double**)malloc(sizeof(double*)*num_cities);
    for(i=0;i<num_cities;i++){
      points[i]=(double*)malloc(sizeof(double)*2);
      for(j=0;j<2;j++){
	points[i][j]=drand48();
      }
    }
  }


  //INITIALISE POINTS FROM FILE
  if(fflag==1){
    fscanf(points_file,"%d", &num_cities);

    points=(double**)malloc(sizeof(double*)*num_cities);
    for(i=0;i<num_cities;i++){
      points[i]=(double*)malloc(sizeof(double)*2);
      fscanf(points_file,"%lf %lf;", &points[i][0], &points[i][1]);
    }
    fclose(points_file);
  }



  //SET UP DIST MATRIX
  dists=(double**)malloc(sizeof(double*)*num_cities);
  for(i=0;i<num_cities;i++){
    dists[i]=(double*)malloc(sizeof(double)*(num_cities));
    for(j=0;j<num_cities;j++){
      dists[i][j]=dist(points, i, j);
    }
  }

  
  //SET INITIAL ORDERING OF ROUTE
  order=(int*)malloc(sizeof(int)*num_cities);
  for(i=0;i<num_cities;i++){
    order[i]=i;
  }

  fp=fopen("routes.txt", "w+");

  //GET ALL PERMUTATIONS AND WRITE TO A FILE
  permute(order, num_cities, 1, fp);

  fclose(fp);
  //have written file and now need to read it
  fp=fopen("routes.txt", "r");

  //returns the shortest route
  order=shortest_route(fp, dists, num_cities);

  //print shortest route
  for(i=0;i<num_cities;i++)
    printf("%d ", order[i]);

  printf("\n");

  fclose(fp);

  free_2d(points, num_cities);
  free_2d(dists, num_cities);
  //free(order);

  return 0;
}
