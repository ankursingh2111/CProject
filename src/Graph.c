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
int dfsTraversal(Graph *graph, int k, int *visit)
{
  visit[k]=1;
  printf("%d ",k);

  for(int i=0;i<graph->V;i++)
  {
     if(!visit[i] && graph->array[k][i])
        dfsTraversal(graph,i,visit);
  } 
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
  queue->capacity=5;
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
int bfsTraversal(Graph *graph,int k, int *visit, queueArray *queue)
{
   visit[k]=1;
   enque(queue,k);
   int i;
   while(!isEmpty(queue))
   {
       k=deque(queue);
       printf("%d",k);
       for(i=0;i<graph->V;i++)
       {
         if(!visit[i] && graph->array[k][i])
         {
           visit[i]=1;
           enque(queue,i);
         }
       }
   } 
}
int main()
{
  queueArray *queue=createQueue();
  int u,v,k=0;
  int visited[5]={0,0,0,0,0};
  int arr[4][4]={{0,1,1,0},{0,0,1,0},{1,0,0,1},{0,0,0,1}};
  printf("Enter the number of Vertices and Edges\n");

  scanf("%d %d",&v,&u);
  Graph *graph=createGraph(v,u);

  printf("Enter the Edges for all vertices\n");
  for(int i=0;i<v;i++)
  {
    for(int j=0;j<v;j++)
      graph->array[i][j]=arr[i][j];
  }
 
  printGraph(graph);

  for(k=0;k<graph->V;k++)
  {
      if(!visited[k])
        dfsTraversal(graph,k,visited);
  }
  printf("\n");
  int visited1[5]={0,0,0,0,0};
//  for(k=0;k<graph->V;k++)
//  {
      if(!visited1[2])
        bfsTraversal(graph,2,visited1,queue);
//  }
  
}
