#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){
  int a[1000];
  FILE *fp = fopen("num.txt","r");
  for(int i=0; i<1000; i++){
    fscanf(fp,"%d",&a[i]);
  }

  int n = sizeof(a)/sizeof(a[0]);
  int swap = 0;
  double start = omp_get_wtime();
  do{
    swap = 0;
    for(int i=0; i<n-1; i+=2){
      if(a[i]>a[i+1]){
        swap = 1;
        int temp = a[i];
        a[i] = a[i+1];
        a[i+1] = temp;
      }
    }

    for(int i=1; i<n-1; i+=2){
      if(a[i]>a[i+1]){
        swap = 1;
        int temp = a[i];
        a[i] = a[i+1];
        a[i+1] = temp;
      }
    }
  }while(swap==1);
  double end = omp_get_wtime();
  for(int i=0; i<n; i++){
    printf("%d\t",a[i]);
  }
  printf("\nTime = %f",end-start);
  
}