#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int a[1000];
  FILE *fp = fopen("num.txt", "r");
  for (int i = 0; i < 1000; i++)
    fscanf(fp, "%d", &a[i]);
  int n = sizeof(a) / sizeof(a[0]);
  int swap = 0;
  double start = omp_get_wtime();
  do {
    swap = 0;
#pragma omp parallel for
    for (int i = 0; i < n - 1; i += 2) {
      if (a[i] > a[i + 1]) {
        int temp = a[i];
        a[i] = a[i + 1];
        a[i + 1] = temp;
        swap = 1;
      }
    }
#pragma omp parallel for
    for (int i = 1; i < n - 1; i += 2) {
      if (a[i] > a[i + 1]) {
        int temp = a[i];
        a[i] = a[i + 1];
        a[i + 1] = temp;
        swap = 1;
      }
    }
  } while (swap != 0);
  double end = omp_get_wtime();
  for (int i = 0; i < n; i++)
    printf("%d\t", a[i]);
  printf("\nTime = %f", end - start);
}
