#include<stdlib.h>

void free_2d(double **mat, int size){

  int i;
  for(i=0;i<size;i++){
    free(mat[i]);
  }
  free(mat);
}
