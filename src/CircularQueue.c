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
void display(queueArray *queue)
{
  if(queue->front==-1)
    printf("Queue is Empty");
  
  int i=queue->front;
  if(queue->front<queue->rear)
  {
     while(i<=queue->rear)
     {
       printf("%d ",queue->array[i]);
       i++;
     }
     
  }
  else
  {
     while(i<queue->capacity)
     {
       printf("%d ",queue->array[i]);
       i++;
     }
     i=0;
     while(i<=queue->rear)
     {
       printf("%d ",queue->array[i]);
       i++;
     }
  }
}
int main()
{
  queueArray *queue;

  queue=createQueue();
  
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
  display(queue);
}
