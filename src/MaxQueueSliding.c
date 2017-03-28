#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct queueArray
{
  int front,rear;
  int capacity;
  int *array;
}queueArray;

queueArray * createQueue()
{
  queueArray *queue=(queueArray*)malloc(sizeof(queueArray));
  if(queue==NULL)
  {
    printf("No memory allocated");
    exit(0);
  }
  queue->capacity=10;
  queue->front=queue->rear=-1;
  queue->array=(int*)malloc(queue->capacity*sizeof(int));
  if(!queue->array)
  {
    printf("No memory allocated");
    exit(0);
  }
  return queue;
}
int max(queueArray *q1, int *a1, int w)
{
  int max=0;
  for(int i=0; i+w<=q1->rear+1; i++)
  {
    max=q1->array[i];

    for(int j=i;j<i+w;j++)
    {
      if(max<q1->array[j])
         max=q1->array[j];
    }
    a1[i]=max;
  }
  
/*  for(int i=q1->front;i<i+w<10;pop(q1))
  {
     
     if(max<q1->array[i])
         max=q1->array[i];
  }*/
}
void resizeQueue(queueArray *queue)
{
  int size=queue->capacity;
  queue->capacity=queue->capacity*2;
  int i=0;
  queue->array=realloc(queue->array,queue->capacity);

  if(!queue->array)
  {
    printf("No memory allocated");
    exit(0);
  }
  if(queue->front>queue->rear)
  {
    for(i=0;i<=queue->rear;i++)
    {
      queue->array[i+size]=queue->array[i];
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

  queue->array[++queue->rear]=num;
   
  if(queue->front==-1)
    queue->front=0;
}
int deque(queueArray *queue)
{
  if(queue->rear==-1 && queue->front==-1)
    printf("Queue is Empty");

  int num=queue->array[queue->front++];

  if(queue->front==queue->capacity)
    queue->front=0;
  if(queue->front-1==queue->rear)
    queue->front=queue->rear=-1;

  return num;
} 
void display(int *a1)
{
  int i=0;
  while(a1[i])
   printf("%d ",a1[i++]);
}

int main()
{
 queueArray *queue;
 int *a1;
 memset(a1,0,10);
 int w=3;
 queue=createQueue();
 a1=(int*)malloc(queue->capacity*sizeof(int));

  enque(queue,1);
  enque(queue,2);
  enque(queue,3);
  enque(queue,4);
  enque(queue,5);
  enque(queue,6);
  enque(queue,7);
  enque(queue,8);

 // deque(queue);
  enque(queue,9);
  enque(queue,10);
  enque(queue,11);
  printf("\n");
  display(queue->array);
  max(queue,a1,3);
  printf("\n");
  display(a1);
  
}
