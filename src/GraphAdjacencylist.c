#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct adjacencyListNode
{
  int data;
  struct adjacencyListNode * next;
}adjacencyListNode;

typedef struct adjacencyList
{
  adjacencyListNode *head;
}adjacencyList;

typedef struct Graph
{
int V;
int E;
adjacencyList * array;
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

  graph->array=(adjacencyList *)malloc(sizeof(adjacencyList) * graph->V);

  if(graph->array==NULL)
  {
    printf("No memory allocated");
    exit(1);
  }
  for(int i=0;i<vertices;i++)
    graph->array[i].head=NULL;
   
  return graph;

}
adjacencyListNode * createNode(int data)
{
  adjacencyListNode *temp=(adjacencyListNode*)malloc(sizeof(adjacencyListNode));

  if(temp==NULL)
  {
    printf("No memory allocated");
    exit(1);
  }
  temp->data=data;
  temp->next=NULL;
  return temp;
}

Graph * addEdge(Graph *graph, int src, int dest,int *arr)
{
  adjacencyListNode *temp=createNode(dest);

  temp->next=graph->array[src].head;
  graph->array[src].head=temp;
  arr[dest]++;
/*  temp=createNode(src);
  temp->next=graph->array[dest].head;
  graph->array[dest].head=temp;*/

  return graph;
}

void printGraph(Graph *graph)
{
  for(int i=0; i<graph->V; i++)
  {
    adjacencyListNode *temp=graph->array[i].head;

    printf("\n Adjacency list of vertex %d\n head ", i);
    while(temp)
    {
       printf("-> %d",temp->data);
       temp=temp->next;
    }
  }
  printf("\n");
}

typedef struct queueArray
{
  int front,rear;
  int capacity;
  int *arr;
}queueArray;
queueArray * createQueue()
{
  queueArray *queue=(queueArray*)malloc(sizeof(queueArray));
  if(queue==NULL)
  {
    printf("No memory allocated");
    exit(0);
  }
  queue->capacity=7;
  queue->front=queue->rear=-1;
  queue->arr=(int*)malloc(queue->capacity*sizeof(int));
  if(!queue->arr)
  {
    printf("No memory allocated");
    exit(0);
  }
  return queue;
}

void resizeQueue(queueArray *queue)
{
  int size=queue->capacity;
  queue->capacity=queue->capacity*2;
  int i=0;
  queue->arr=realloc(queue->arr,queue->capacity);

  if(!queue->arr)
  {
    printf("No memory allocated");
    exit(0);
  }
  if(queue->front>queue->rear)
  {
    for(i=0;i<=queue->rear;i++)
    {
      queue->arr[i+size]=queue->arr[i];
    }
  queue->rear=queue->rear+size;
  }

}

void enque(queueArray *queue, int num)
{
  if((queue->rear==queue->capacity-1 && queue->front==0) || (queue->front==queue->rear+1))
  {
    printf("Queue is full");
    resizeQueue(queue);
  }
  if(queue->rear==queue->capacity-1 && queue->front!=0)
    queue->rear=-1;

  queue->arr[++queue->rear]=num;

  if(queue->front==-1)
    queue->front=0;
}
int deque(queueArray *queue)
{
  if(queue->rear==-1 && queue->front==-1)
    printf("Queue is Empty");

  int num=queue->arr[queue->front++];

  if(queue->front==queue->capacity)
    queue->front=0;
  if(queue->front-1==queue->rear)
    queue->front=queue->rear=-1;

  return num;
}

int isEmpty(queueArray *queue)
{
    return queue->front == -1;
}
void topologicalSort(Graph *graph, int *arr)
{
   int i,k;
   int count=0;
   queueArray *queue=createQueue();
   for(i=0;i<graph->V;i++)
   {
      if(!arr[i])
        enque(queue,i);
   }
   while(!isEmpty(queue))
   {
       k=deque(queue);
       printf("%d ",k);
       count++;

       adjacencyListNode *temp=graph->array[k].head;

       while(temp)
       {
          if(--arr[temp->data]==0)
             enque(queue,temp->data);
          temp=temp->next;
       }
   }
}
void printarray(int *arr, int num)
{
   for(int i=0;i<num;i++)
     printf("%d ",arr[i]);
   printf("\n");
}
int shortestPathAlgorithm(Graph *graph, int s)
{
    int *distance, *path;
    distance=(int*)malloc(sizeof(int)*graph->V);
    path=(int*)malloc(sizeof(int)*graph->V);
    queueArray *queue=createQueue();
    for(int i=0;i<graph->V;i++)
       distance[i]=-1;
    int v,w;
    distance[s]=0;
    enque(queue,s);
 
    while(!isEmpty(queue))
    {
       v=deque(queue);
       adjacencyListNode *temp=graph->array[v].head;
       while(temp)
       {
          if(distance[temp->data]==-1)
          {
              distance[temp->data]=distance[v]+1;
              path[temp->data]=v;
              enque(queue,temp->data);
          }
          temp=temp->next;
       }
    }
    printarray(distance,graph->V);
    printarray(path,graph->V);          
    free(distance);
    free(path);
    return 0;
}
typedef struct storePath
{
    char Vertices;
    int distance; 
}storePath;
Graph * addedge1(Graph *graph, char s, char d)
{
    adjacencyListNode *temp=createNode(d);
    temp=graph->array[s].head;
    graph->array[s].head=temp;

    return graph;  
}
int main()
{
    // create the graph given in above fugure
    int V = 6;
    int arr[7]={0,0,0,0,0,0,0};
 /*   Graph* graph = createGraph(V,1);
    addEdge(graph,5, 2,arr);
    addEdge(graph,5, 0,arr);
    addEdge(graph,4, 0,arr);
    addEdge(graph,4, 1,arr);
    addEdge(graph,2, 3,arr);
    addEdge(graph,3, 1,arr);

    // print the adjacency list representation of the above graph
    printGraph(graph);

    topologicalSort(graph,arr);*/
    Graph *graph=createGraph(7,1);
    
    addEdge(graph,0, 1,arr);
    addEdge(graph,0, 3,arr);
    addEdge(graph,1, 3,arr);
    addEdge(graph,1, 4,arr);
    addEdge(graph,2, 0,arr);
    addEdge(graph,2, 5,arr);
    addEdge(graph,3, 2,arr);
    addEdge(graph,3, 4,arr);
    addEdge(graph,3, 5,arr);
    addEdge(graph,3, 6,arr);
    addEdge(graph,4, 6,arr);
    addEdge(graph,6, 5,arr);
    printGraph(graph);
    shortestPathAlgorithm(graph,0);
    return 0;
}
