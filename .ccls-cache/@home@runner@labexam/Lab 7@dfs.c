#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000

int graph[MAX_NODES][MAX_NODES];
int visited[MAX_NODES];
int num_nodes;

void initialize() {
  for (int i = 0; i < num_nodes; i++) {
    visited[i] = 0;
    for (int j = 0; j < num_nodes; j++) {
      graph[i][j] = 0;
    }
  }
}

void addEdge(int u, int v) { graph[u][v] = 1; }

void serial_dfs(int node) {
  printf("%d ", node);
  visited[node] = 1;
  for (int i = 0; i < num_nodes; i++) {
    if (graph[node][i] && !visited[i]) {
      serial_dfs(i);
    }
  }
}

int main() {
  int num_edges;
  printf("Enter number of nodes: ");
  scanf("%d", &num_nodes);
  printf("Enter number of edges: ");
  scanf("%d", &num_edges);

  initialize();
  printf("Enter edges (u v):\n");
  for (int i = 0; i < num_edges; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    addEdge(u, v);
  }

  double start = omp_get_wtime();
  printf("\nSerial DFS: ");
  serial_dfs(0);
  double end = omp_get_wtime();
  printf("\nTime = %f\n", end - start);
}
