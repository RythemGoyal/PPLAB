#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void sort(int a[], int low, int high){
  if(low<=high){
    int s = low;
    int e = high; 
    int m = s + (e-s)/2;
    int pivot = a[m];

    while(s<=e){
      while(a[s]<pivot){
        s++;
      }
      while(a[e]>pivot){
        e--;
      }
      if(s<=e){
        int temp = a[s];
        a[s] = a[e];
        a[e] = temp;
        s++;
        e--;
      }
    }
    #pragma omp parallel sections
    {
      #pragma omp section
      {
        sort(a,low,e);
      }
      #pragma omp section
      {
        sort(a,s,high);
      }
    }
  }
}

int main(){
  int a[1000];
  FILE *fp = fopen("num.txt","r");
  for(int i=0; i<1000; i++){
    fscanf(fp,"%d",&a[i]);
  }
  int n = sizeof(a)/sizeof(a[0]);
  double start = omp_get_wtime();
  sort(a,0,n-1);
  double end = omp_get_wtime();
  for(int i=0; i<1000; i++)
    printf("%d\t",a[i]);
  printf("\nTime = %f",end-start);
}