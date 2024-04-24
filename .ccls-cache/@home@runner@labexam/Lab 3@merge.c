#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void merge(int a[], int s, int m, int e){
  int i=s;
  int j = m+1;
  int k=0;
  int arr[e-s];
  while (i <= m && j <= e) {
      if (a[i] < a[j]) {
          arr[k] = a[i];
          i++;
      } else {
          arr[k] = a[j];
          j++;
      }
      k++;
  }

  while (i <= m) {
      arr[k] = a[i];
      i++;
      k++;
  }
  while (j <= e) {
      arr[k] = a[j];
      j++;
      k++;
  }

  // Copy elements from arr back to a
  for (int l = 0; l < k; l++) {
      a[s + l] = arr[l];
  }

}

void mergeSort(int a[], int s, int e){
  if(s<e){
    int m = s + (e-s)/2;
    mergeSort(a,s,m);
    mergeSort(a,m+1,e);
    merge(a,s,m,e);
  }
}

int main(){
  int a[1000];
  FILE *fp = fopen("num.txt","r");
  for(int i=0; i<1000; i++){
    fscanf(fp,"%d",&a[i]);
  }
  double start = omp_get_wtime();
  mergeSort(a,0,999);
  double end = omp_get_wtime();
  for(int i=0; i<1000; i++)
    printf("%d\t",a[i]);
  printf("\nTime = %f",end-start);
}