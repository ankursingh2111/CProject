#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct queueArray
{
  int front,rear;
  int capacity;
  int *array;
}queueArray;
typedef struct stack
{
  queueArray *q1;
  queueArray *q2;
}stack;
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
int empty(queueArray *queue)
{
  if(queue->front==-1)
    return 1;
  return 0;
}
void enque(queueArray *queue, int num)
{
  if((queue->rear==queue->capacity-1 && queue->front==0) || (queue->front==queue->rear+1))
  {
    printf("Queue is full");
    exit(1);
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
  {
     queue->front=0;
     queue->rear=-1;
  }
  if(queue->front-1==queue->rear)
    queue->front=queue->rear=-1;

  return num;
}
void push(stack *s1,int num)
{
  if(empty(s1->q1))
    enque(s1->q2,num);
  else
    enque(s1->q1,num);    
}
int pop(stack *s1)
{
  int i=0,size,size1;
  if(s1->q1->rear<s1->q1->front)
    size=s1->q1->capacity-s1->q1->front+s1->q1->rear;
  else
    size=s1->q1->rear-s1->q1->front;

  if(s1->q2->rear<s1->q2->front)
    size1=s1->q2->capacity-s1->q2->front+s1->q2->rear;
  else
    size1=s1->q2->rear-s1->q2->front;

  if(empty(s1->q1))
  {
    while(i++<size1)
      enque(s1->q1,deque(s1->q2));
    return deque(s1->q2);
  }
  else
  {
    while(i++<size)
     enque(s1->q2,deque(s1->q1));
   return deque(s1->q1);
  }
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
  stack *s1;
  s1=(stack*)malloc(sizeof(stack));

  s1->q1=createQueue();
  s1->q2=createQueue();

  push(s1,1);
  push(s1,2);
  push(s1,3);
  push(s1,4);
  push(s1,5);
  push(s1,6);
  push(s1,7);
  push(s1,8);

 // deque(queue);
  push(s1,9);
  push(s1,10);
  printf("\n");
  display(s1->q2); 
  
 printf("\n");
  printf("%d ",pop(s1));
  printf("%d ",pop(s1));
  printf("%d ",pop(s1));
  printf("%d ",pop(s1));
  printf("%d ",pop(s1));
  printf("%d ",pop(s1));
}
