#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 1000

int graph[MAX_NODE][MAX_NODE];
int visited[MAX_NODE];
int num_nodes, num_edges;

void initialize() {
  for (int i = 0; i < num_nodes; i++) {
    visited[i] = 0;
    for (int j = 0; j < num_nodes; j++) {
      graph[i][j] = 0;
    }
  }
}

void addEdge(int u, int v) { graph[u][v] = 1; }

void bfs(int node) {
  int queue[num_nodes], front = 0, rear = 0;
  for (int i = 0; i < num_nodes; i++) {
    visited[i] = 0;
  }
  visited[node] = 1;
  queue[rear++] = node;
  printf("%d ", node);
  while (front != rear) {
    node = queue[front++];
    for (int i = 0; i < num_nodes; i++) {
      if (graph[node][i] && !visited[i]) {
        visited[i] = 1;
        queue[rear++] = i;
        printf("%d ", i);
      }
    }
  }
  printf("\n");
}

int main() {
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
  printf("BFS: ");
  bfs(0);
  double end = omp_get_wtime();
  printf("Time = %f\n", end - start);
  return 0;
}