#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){
  int a[1000];
  FILE *fp = fopen("num.txt","r");
  for(int i=0; i<1000; i++){
    fscanf(fp,"%d",&a[i]);
  }

  for(int i=0; i<1000; i++){
    for(int j=0; j<1000-i-1; j++){
      if(a[j]>a[j+1]){
        int temp = a[j];
        a[j] = a[j+1];
        a[j+1] = temp;
      }
    }
  }

  int s=0,e=999,mid,num,f=1;
  printf("Enter the number to be searched\n");
  scanf("%d",&num);
  double start = omp_get_wtime();
  while(s<=e){
    mid = (s+e)/2;
    if(num == a[mid]){
      f = 1; 
      break;
    }
    else if(num < a[mid]){
      e = mid - 1;
    }
    else{
      s = mid + 1;
    }
  }

  double end = omp_get_wtime();
  if(f == 1){
    printf("Number found at %d\n",mid);
  }
  else{
    printf("Number not found\n");
  }

  printf("\n%f", end-start);
}