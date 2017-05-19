#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INT_MAX 999
typedef struct Graph
{
int V;
int E;
int **array;
}Graph;

Graph * createGraph(int vertices, int edge)
{
  Graph *graph=(Graph*)malloc(sizeof(Graph));

  if(graph==NULL)
  {
    printf("No memory allocated");
    exit(1);
  }
  graph->V=vertices;
  graph->E=edge;

  graph->array=(int**)malloc(sizeof(int*) * graph->V);

  for(int i=0;i<vertices;i++)
    graph->array[i]=(int*)malloc(sizeof(int) * graph->V);


// graph->array=malloc(sizeof(graph->V * graph->V));
  if(graph->array==NULL)
  {
    printf("No memory allocated");
    exit(1);
  }
  for(int i=0;i<graph->V;i++)
  {
    for(int j=0;j<graph->V;j++)
      graph->array[i][j]=0;
  }
  return graph;
}

void printGraph(Graph *graph)
{
  for(int i=0;i<graph->V;i++)
  {
    for(int j=0;j<graph->V;j++)
       printf("%d ",graph->array[i][j]);
  }
  printf("\n");
}
int minIndex(int dist[], int n, int mspt[])
{
  int min=INT_MAX;
  int minindex;
  for(int i=0;i<n;i++)
  {
    if(!mspt[i] && dist[i]<min)
    {
       min=dist[i];
       minindex=i;
    }
  }
  return minindex;

}
void printMST(int parent[], int n, int **graph)
{
   printf("Edge   Weight\n");
   for (int i = 1; i < n; i++)
      printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
}
int primsAlgo(Graph *graph, int src)
{
  int V=graph->V;
  int E=graph->E;
  int i;
  int dist[V];
  int mspt[V];
  int parent[V];
  parent[src]=-1;
  for(i=0; i<V;i++)
  {
    dist[i]=INT_MAX;
    mspt[i]=0;
  }
  int u;
  dist[src]=0;

  for(i=0;i<V-1;i++)
  {
    u=minIndex(dist,V,mspt);
    mspt[u]=1;
    for(int v=0;v<V;v++)
    {
       if(!mspt[v] && graph->array[u][v] && graph->array[u][v]<dist[v])
       {
           dist[v]=graph->array[u][v];
           parent[v]=u;
       }
    }
  }
  printMST(parent, V, graph->array);
}

int main()
{
   /* Let us create the following graph
          2    3
      (0)--(1)--(2)
       |   / \   |
      6| 8/   \5 |7
       | /     \ |
      (3)-------(4)
            9          */
   int V=5;
   int graph[5][5] = {{0, 2, 0, 6, 0},
                      {2, 0, 3, 8, 5},
                      {0, 3, 0, 0, 7},
                      {6, 8, 0, 0, 9},
                      {0, 5, 7, 9, 0},
                     };
 
    // Print the solution

    Graph *graph1=createGraph(5,5);
    for(int i=0; i<5;i++)
    {
       for(int j=0;j<5;j++)
         graph1->array[i][j]=graph[i][j];
    }
    primsAlgo(graph1,0);
 
    return 0;
}
