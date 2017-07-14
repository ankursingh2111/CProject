#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
//  memset(graph->array,0,25);

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
int checkCycleDirectedGraph(Graph *graph,int visited[],int recstack[],int u)
{
  if(!visited[u])
  {
     visited[u]=1;
     recstack[u]=1;

     for(int i=0;i<graph->V;i++)
     {
       if(graph->array[u][i])
       {
         if(!visited[i] && checkCycleDirectedGraph(graph,visited,recstack,i))
            return 1;
         else if(recstack[i])
           return 1;
       }
     }
  }
  recstack[u]=0;
  return 0;
}

int checkCycleDG(Graph *graph)
{
  int visit[graph->V];
  int recstack[graph->V];
  
  for(int i=0;i<graph->V;i++)
  {
    visit[i]=0;
    recstack[i]=0;
  }

  for(int j=0;j<graph->V;j++)
  {
     if(!visit[j])
     {
        if(checkCycleDirectedGraph(graph,visit,recstack,j))
           return 1;
     }
  }
  return 0;
}

int checkCycleGraph(Graph *graph,int visited[],int parent,int u)
{    
    visited[u]=1;
          
     for(int i=0;i<graph->V;i++)
     {
       if(graph->array[u][i])
       {
         if(!visited[i])
         {
            if( checkCycleGraph(graph,visited,u,i))
              return 1;
         }
         else if(parent!=i)
           return 1;
       }
     }
  return 0;
}

int checkCycleG(Graph *graph)
{
  int visit[graph->V];
 
  for(int i=0;i<graph->V;i++)
    visit[i]=0;

  for(int j=0;j<graph->V;j++)
  {
     if(!visit[j])
     {
        if(checkCycleGraph(graph,visit,-1,j))
           return 1;
     }
  }
  return 0;
}

int main()
{
  Graph *graph=createGraph(4,6);

  int arr[4][4]={{0,1,1,0},{0,0,1,0},{0,0,0,1},{0,0,0,0}};

  for(int i=0;i<graph->V;i++)
  {
    for(int j=0;j<graph->V;j++)
      graph->array[i][j]=arr[i][j];
  }
  if(checkCycleDG(graph))
    printf("Graph has cycle\n");
  else
    printf("Graph has no cycle\n");

  Graph *graph1=createGraph(5,6);

  int arr1[5][5]={{0,0,1,1,0},{1,0,0,0,0},{1,0,0,0,0},{0,0,0,0,1},{0,0,0,0,0}};

  for(int i=0;i<graph1->V;i++)
  {
    for(int j=0;j<graph1->V;j++)
      graph1->array[i][j]=arr1[i][j];
  }
  if(checkCycleG(graph1))
    printf("Graph has cycle\n");
  else
    printf("Graph has no cycle\n");

Graph *graph2=createGraph(3,6);

  int arr2[3][3]={{0,1,0},{0,1,1},{0,0,0}};

  for(int i=0;i<graph2->V;i++)
  {
    for(int j=0;j<graph2->V;j++)
      graph2->array[i][j]=arr2[i][j];
  }
  if(checkCycleG(graph2))
    printf("Graph has cycle\n");
  else
    printf("Graph has no cycle\n");
}
