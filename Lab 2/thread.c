#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define ASIZE 10000

int main() {
  int a[ASIZE], i, tid, numt, psum, sum = 0;
  for (i = 0; i < 10000; i++) {
    a[i] = 1;
  }
  double start = omp_get_wtime();
#pragma omp parallel default(shared) private(i, tid, psum)
  {
    int from, to;
    tid = omp_get_thread_num();
    numt = omp_get_num_threads();
    from = (ASIZE / numt) * tid;
    to = (ASIZE / numt) * (tid + 1) - 1;
    if (tid == numt - 1) {
      to = ASIZE - 1;
    }
    psum = 0;
    for (i = from; i <= to; i++) {
      psum = psum + a[i];
    }
#pragma omp critical
    { sum = sum + psum; }
  }
  double end = omp_get_wtime();
  printf("Sum = %d\n", sum);
  printf("Time = %f\n", end - start);
  printf("%d", numt);
}