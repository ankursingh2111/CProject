#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INT_MAX 100
typedef struct GraphArray
{
  int src;
  int dest;
  int weight;
}GraphArray;

typedef struct Graph
{
int V;
int E;
GraphArray * array;
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

  graph->array=(GraphArray*)malloc(sizeof(GraphArray) * graph->E);

  if(graph->array==NULL)
  {
    printf("No memory allocated");
    exit(1);
  }
  return graph;

}

void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
void bfAlgo(Graph *graph, int src)
{
 int vertices=graph->V;
 int edge=graph->E;
 int dist[vertices];
 int i,j,u,v,w;
 for(i=0;i<vertices;i++)
   dist[i]=INT_MAX;

 dist[src]=0; 

 for(i=0;i<vertices;i++)
 {
   for(j=0;j<edge;j++)
   {
     u=graph->array[j].src;
     v=graph->array[j].dest;
     w=graph->array[j].weight;

     if(dist[u]!=INT_MAX && dist[u]+w<dist[v])  
         dist[v]=dist[u]+w; 
   }
 }
 for(j=0;j<edge;j++)
 {
     u=graph->array[j].src;
     v=graph->array[j].dest;
     w=graph->array[j].weight;
   
     if(dist[u]!=INT_MAX && dist[u]+w<dist[v])  
       printf("Graph has negative cyle");
 }
 printArr(dist,vertices);
}
int main()
{
    /* Let us create the graph given in above example */
    int V = 5;  // Number of vertices in graph
    int E = 8;  // Number of arrays in graph
    Graph* graph = createGraph(V, E);
 
    // add array 0-1 (or A-B in above figure)
    graph->array[0].src = 0;
    graph->array[0].dest = 1;
    graph->array[0].weight = -1;
 
    // add array 0-2 (or A-C in above figure)
    graph->array[1].src = 0;
    graph->array[1].dest = 2;
    graph->array[1].weight = 4;
 
    // add array 1-2 (or B-C in above figure)
    graph->array[2].src = 1;
    graph->array[2].dest = 2;
    graph->array[2].weight = 3;
 
    // add array 1-3 (or B-D in above figure)
    graph->array[3].src = 1;
    graph->array[3].dest = 3;
    graph->array[3].weight = 2;
 
    // add array 1-4 (or A-E in above figure)
    graph->array[4].src = 1;
    graph->array[4].dest = 4;
    graph->array[4].weight = 2;
 
    // add array 3-2 (or D-C in above figure)
    graph->array[5].src = 3;
    graph->array[5].dest = 2;
    graph->array[5].weight = 5;
 
    // add array 3-1 (or D-B in above figure)
    graph->array[6].src = 3;
    graph->array[6].dest = 1;
    graph->array[6].weight = 1;
 
    // add array 4-3 (or E-D in above figure)
    graph->array[7].src = 4;
    graph->array[7].dest = 3;
    graph->array[7].weight = -3;
 
    bfAlgo(graph, 0);
 
    return 0;
}
