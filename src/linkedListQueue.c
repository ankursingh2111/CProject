#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct listNode
{
   int data;
   struct listNode *next;
}listNode;
typedef struct queueArray
{
  listNode *front,*rear;
}queueArray;
listNode* addNode(int data)
{
   listNode *temp;
   temp=(listNode *) malloc(sizeof(listNode));
   if(temp==NULL)
   {
     printf("Error creating a new node.\n");
        exit(0);
   }

   temp->data= data;
   temp->next=NULL;
   return temp;
}
queueArray* insertEnd(queueArray *q1, int data)
{
   queueArray *temp;

   queueArray *current;
   if(q1->rear == NULL)
   {
     q1->rear=addNode(data);
     if(q1->front==NULL)
       q1->front=q1->rear;
     return q1;
   }
  // temp->rear=addNode(data);
   q1->rear->next=addNode(data);
   q1->rear=q1->rear->next;
   return q1;
 
}
queueArray* deque(queueArray *q1)
{
  if(q1->front==NULL)
    printf("LinkedListQueue is empty");
  
  listNode * temp=q1->front;
   q1->front=q1->front->next;
   temp->next=NULL;
   free(temp);
   return q1;
}
void display(queueArray *q1)
{
  if(q1->front==NULL)
    printf("LinkedListQueue is empty");

  queueArray *temp=q1;
  while(temp->front!=q1->rear)
  {
    printf("%d ",temp->front->data);
    temp->front=temp->front->next; 
  }
  printf("%d ",temp->front->data);
}
int main()
{
  queueArray *q1;

  q1=(queueArray*)malloc(sizeof(queueArray));
  
  q1=insertEnd(q1,1);
  q1=insertEnd(q1,2);
  q1=insertEnd(q1,3);
  q1=insertEnd(q1,4);
  q1=insertEnd(q1,5);
  q1=insertEnd(q1,6);
  q1=insertEnd(q1,7);

  deque(q1);
  deque(q1);
  display(q1);
  
}
