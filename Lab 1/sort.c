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
    for(int j=0; j<1000-1-i; j++){
      if(a[j]<a[j+1]){
        int temp = a[j];
        a[j] = a[j+1];
        a[j+1] = temp;
      }
    }
  }
  for(int i=0; i<1000; i++){
    printf("%d\t",a[i]);
  }
}