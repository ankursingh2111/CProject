#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INT_MAX 100
typedef struct GraphArray
{
  int src;
  int dest;
//  int weight;
}GraphArray;

typedef struct Graph
{
int V;
int E;
GraphArray * edge;
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

  graph->edge=(GraphArray*)malloc(sizeof(GraphArray) * graph->E);

  if(graph->edge==NULL)
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
int findParent(int parent[], int i)
{
   if(parent[i]==-1)
      return i;
   return findParent(parent,parent[i]);
}

void unionSet(int parent[],int src,int dest)
{
   int xset=findParent(parent,src);
   int yset=findParent(parent,dest);
   parent[xset]=yset;
}
int detectCycle(Graph *graph)
{
  // Allocate memory for creating V subsets
    int *parent = (int*) malloc( graph->V * sizeof(int) );
 
    // Initialize all subsets as single element sets
    memset(parent, -1, sizeof(int) * graph->V);

    // Iterate through all edges of graph, find subset of both
    // vertices of every edge, if both subsets are same, then 
    // there is cycle in graph.
    for(int i = 0; i < graph->E; ++i)
    {
        int x = findParent(parent, graph->edge[i].src);
        int y = findParent(parent, graph->edge[i].dest);
 
        if (x == y)
            return 1;
 
 //       unionSet(parent, x, y);
        parent[x]=y;
    }
    return 0;
}
 
// Driver program to test above functions
int main()
{
    /* Let us create following graph
         0
        |  \
        |    \
        1-----2 */    
    int V = 3, E = 3;
    Graph* graph = createGraph(V, E);
 
    // add edge 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
 
    // add edge 1-2
    graph->edge[1].src = 1;
    graph->edge[1].dest = 2;
 
    // add edge 0-2
      graph->edge[2].src = 0;
    graph->edge[2].dest = 2;
 
    if (detectCycle(graph))
        printf( "graph contains cycle" );
    else
        printf( "graph doesn't contain cycle" );
 
    return 0;
}
