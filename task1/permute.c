#include<stdio.h>
#include<stdlib.h>
void swap(int v[], int i, int j);


void permute(int *order, int n, int i, FILE *fp){

  int j;

  if(i==n){
    for(j=0;j<n;j++){
      fprintf(fp,"%d ", order[j]);
    }
    fprintf(fp,"\n");
  }else{

    for(j=i;j<n;j++){
      swap(order,i, j);
      permute(order, n, (i+1), fp);
      swap(order, i, j); 
    }
  }
}
