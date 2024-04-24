#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000

typedef struct Graph_t {
  int v;
  bool adj[MAX_NODES][MAX_NODES];
} Graph;

Graph *createGraph(int v) {
  Graph *G = malloc(sizeof(Graph));
  G->v = v;
  for (int i = 0; i < v; i++) {
    for (int j = 0; j < v; j++) {
      G->adj[i][j] = false;
    }
  }
  return G;
}

void printAdmrt(Graph *g) {
  int v = g->v;
  printf("v -> ");
  for (int i = 0; i < v; i++) {
    printf("%d ", i);
  }
  printf("\n");
  for (int i = 0; i < v; i++) {
    printf("%d\t", i);
    for (int j = 0; j < v; j++) {
      printf("%d  ", g->adj[i][j]);
    }
    printf("\n");
  }
}

void addEdge(Graph *g, int v, int w) { g->adj[v][w] = true; }

void Graph_BFS_parallel(Graph *g, int s) {
  bool visited[MAX_NODES];
  for (int i = 0; i < g->v; i++) {
    visited[i] = false;
  }
  int queue[MAX_NODES];
  int front = 0, rear = 0;
  visited[s] = true;
  queue[rear++] = s;
#pragma omp parallel default(shared)
  {
    while (front != rear) {
#pragma omp critical
      { s = queue[front++]; }
#pragma omp parallel for
      for (int a = 0; a < g->v; a++) {
        if (g->adj[s][a] && !visited[a]) {
          visited[a] = true;
#pragma omp critical
          { queue[rear++] = a; }
        }
      }
    }
  }
  printf("\n");
}

int main() {
  int n;
  printf("Enter number of vertices: ");
  scanf("%d", &n);
  Graph *g = createGraph(n);

  // for(int i=0; i<g->v; i++){
  //   for(int j=i+1; j<g->v; j++){
  //     addEdge(g, i, j);
  //   }
  // }

  addEdge(g, 0, 1);
  addEdge(g, 0, 2);
  addEdge(g, 1, 3);
  addEdge(g, 1, 4);
  addEdge(g, 2, 5);

  printf("Following is the BFS traversal starting from vertex 0\n");
  printAdmrt(g);

  double start1 = omp_get_wtime();
  Graph_BFS_parallel(g, 0);
  double end1 = omp_get_wtime();

  printf("Parallel Execution time = %f\n", end1 - start1);
}