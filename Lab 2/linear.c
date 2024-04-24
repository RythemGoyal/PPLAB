#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
int main(){
  int a[1000];
  FILE *fp = fopen("num.txt","r");
  for(int i=0; i<1000; i++)
    fscanf(fp,"%d",&a[i]);

  int num,f=0;
  printf("Enter number to be searched");
  scanf("%d",&num);
  double start = omp_get_wtime();
  for(int i=0; i<1000; i++){
    if(num == a[i]){
      printf("Number found at %d\n",i);
      f = 1;
      
    }
  }
  double end = omp_get_wtime();
  if(f!=1)
    printf("\nNumber not found");
  printf("\n%f",end - start);
}