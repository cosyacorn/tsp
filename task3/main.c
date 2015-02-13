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

  int fflag, *order, opt, num_cities, i, j, msec, numlines;
  double **points, **dists;
  FILE *fp, *points_file;
  clock_t start, diff;
  char line[100], ch;

  srand48(time(NULL));
  fflag=0;

  //COMMAND LINE 
  while((opt=getopt(argc,argv,"f:"))!=-1){
    switch(opt){

    case 'f':
      fflag=1;
      points_file=fopen(argv[2], "r");
      break;

    }
  }
 
  //can't have nflag and fflag
  if(fflag!=1){
    printf("Usage: '%s -n <integer>' OR %s -f <file>\n",argv[0], argv[0]);
    return 1;
  }


  //INITIALISE POINTS FROM FILE
  else{
    if(points_file==NULL){
      printf("file does not exist\n");
      return 1;
    }

    while ((ch=fgetc(points_file))!=EOF)
      if (ch=='\n')
        ++numlines;

    rewind(points_file);

    for(i=0;i<6;i++){
      fgets(line, sizeof(line), points_file);
    }

    num_cities=numlines-7;

    points=(double**)malloc(sizeof(double*)*num_cities);
    for(i=0;i<num_cities;i++){
      points[i]=(double*)malloc(sizeof(double)*2);
      fscanf(points_file,"%lf %lf;", &points[i][0], &points[i][1]);
    }
    fclose(points_file);
  }


  /*
  //SET UP DIST MATRIX
  dists=(double**)malloc(sizeof(double*)*num_cities);
  for(i=0;i<num_cities;i++){
    dists[i]=(double*)malloc(sizeof(double)*(num_cities));
    for(j=0;j<num_cities;j++){
      dists[i][j]=dist(points, i, j);
    }
  }
  */
  


  /*
  fp=fopen("routes.txt", "w+");

  //GET ALL PERMUTATIONS AND WRITE TO A FILE
  permute(order, num_cities, 1, fp);

  fclose(fp);
  //have written file and now need to read it
  fp=fopen("routes.txt", "r");


  start=clock();
  //returns the shortest route
  order=shortest_route(fp, dists, num_cities);
  diff=clock()-start;

  //to get timing data for task 2
  msec=diff*1000/CLOCKS_PER_SEC;
  //printf("%d\n", msec);


  //print shortest route
  for(i=0;i<num_cities;i++)
    printf("%d ", order[i]);

  printf("\n");

  fclose(fp);

  */

  free_2d(points, num_cities);
  free_2d(dists, num_cities);
  //free(order);

  return 0;
}
