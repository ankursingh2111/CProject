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
typedef struct Subset
{
  int parent;
  int rank;
}Subset;
int findParent(Subset *set, int i)
{
   if(set[i].parent==i)
      return set[i].parent;
   return findParent(set,set[i].parent);
}

void unionSet(Subset *set,int src,int dest)
{ 
   int xset=findParent(set,src);
   int yset=findParent(set,dest);

   if(set[xset].rank<set[yset].rank)
      set[xset].parent=yset;
   else if(set[xset].rank>set[yset].rank)
      set[yset].parent=xset;
   else
   {
       set[yset].parent=xset;
       set[xset].rank++;
   }
}
void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
// The main function to check whether a given graph contains cycle or not
int isCycle( Graph* graph )
{
    int V = graph->V;
    int E = graph->E;
 
    // Allocate memory for creating V sets
    Subset *subsets = (Subset*) malloc( V * sizeof(Subset) );
 
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Iterate through all edges of graph, find sets of both
    // vertices of every edge, if sets are same, then there is
    // cycle in graph.
    for(int e = 0; e < E; ++e)
    {
        int x = findParent(subsets, graph->edge[e].src);
        int y = findParent(subsets, graph->edge[e].dest);
 
        if (x == y)
            return 1;
 
        unionSet(subsets, x, y);
    }
    return 0;
}
 
// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp(const void* a, const void* b)
{
    struct GraphArray* a1 = (GraphArray*)a;
    struct GraphArray* b1 = (GraphArray*)b;
    return a1->weight > b1->weight;
}
 
// The main function to construct MST using Kruskal's algorithm
void KruskalMST(Graph* graph)
{
    int V = graph->V;
    GraphArray result[V];  // Tnis will store the resultant MST
    int e = 0;  // An index variable, used for result[]
    int i = 0;  // An index variable, used for sorted edges
 
    // Step 1:  Sort all the edges in non-decreasing order of their weight
    // If we are not allowed to change the given graph, we can create a copy of
    // array of edges
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);
 
    // Allocate memory for creating V ssubsets
    Subset *subsets =(Subset*) malloc( V * sizeof(Subset) );
 
    // Create V subsets with single elements
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Number of edges to be taken is equal to V-1
    while (e < V - 1)
    {
        // Step 2: Pick the smallest edge. And increment the index
        // for next iteration
        GraphArray next_edge = graph->edge[i++];
 
        int x = findParent(subsets, next_edge.src);
        int y = findParent(subsets, next_edge.dest);
 
        // If including this edge does't cause cycle, include it
        // in result and increment the index of result for next edge
        if (x != y)
        {
            result[e++] = next_edge;
            unionSet(subsets, x, y);
        }
        // Else discard the next_edge
    }
 
    // print the contents of result[] to display the built MST
    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest,
                                                   result[i].weight);
    return;
}
 
// Driver program to test above functions
int main()
{
    /* Let us create following weighted graph
             10
        0--------1
        |  \     |
       6|   5\   |15
        |      \ |
        2--------3
            4       */
    int V = 4;  // Number of vertices in graph
    int E = 5;  // Number of edges in graph
    struct Graph* graph = createGraph(V, E);
 
 
    // add edge 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 10;
 
    // add edge 0-2
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 6;
 
    // add edge 0-3
    graph->edge[2].src = 0;
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 5;
 
    // add edge 1-3
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 15;
 
    // add edge 2-3
    graph->edge[4].src = 2;
    graph->edge[4].dest = 3;
    graph->edge[4].weight = 4;
 
    KruskalMST(graph);
 
    return 0;
}

/*
/ Driver program to test above functions
int main()
{
     Let us create following graph
         0
        |  \
        |    \
        1-----2 
 
    int V = 3, E = 2;
    Graph* graph = createGraph(V, E);
 
    // add edge 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
 
    // add edge 1-2
    graph->edge[1].src = 1;
    graph->edge[1].dest = 2;
 
    // add edge 0-2
//    graph->edge[2].src = 0;
//    graph->edge[2].dest = 2;
 
    if (isCycle(graph))
        printf( "Graph contains cycle" );
    else
        printf( "Graph doesn't contain cycle" );
 
    return 0;
}*/
