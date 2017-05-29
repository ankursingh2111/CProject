#include<stdio.h>
#include<stdlib.h>
typedef struct listNode
{
   int data;
   struct listNode *next;
}listNode;
typedef struct listNode1
{
   int data;
   struct listNode1 *next;
}listNode1;
typedef struct hashNode
{
   listNode *head;
}hashNode;

hashNode *hashTable=NULL;
int listTraverse( listNode *head);
int listTraverse1( listNode *head);
listNode * insertBeg( listNode *head , int data);
listNode* addNode( listNode *current, int data);
listNode* insertEnd(listNode *head, int data);
listNode* insertBefore(listNode *head, listNode* prev, int data);
listNode* search(listNode *head, int data);
listNode* insertAfter(listNode *head, listNode* node, int data);
listNode* intersectNode(listNode *head1, listNode* head);
listNode* reverse(listNode *head);
void findLoop(listNode *head);
listNode* deleteAll(listNode *head);
listNode* delete(listNode *head, int data);
void createHash(listNode *head,int data);
void findNode(listNode *head, int data);
void findIntersection(listNode *head1,listNode *head, int count1,int count);
void stackIntersection(listNode *head1,listNode *head,int count1, int count);
void listEvenOdd(listNode *head);
listNode * mergeNode(listNode *head1,listNode *head);

int main()
{
   listNode *head=NULL;
   listNode *head1=NULL;
   listNode *next;
   int count=0,count1=0;
   head1=insertBeg(head1,9);
   head1=insertBeg(head1,7);
   head1=insertBeg(head1,4);
   head1=insertBeg(head1,3);
   head=insertBeg(head,0);
   head=insertEnd(head,1);
   head=insertEnd(head,2);
   head=insertEnd(head,5);
  // listTraverse(head);
   next=search(head1,7);
   printf("\n");
   head1=insertBefore(head1,next,6);
   head1=insertAfter(head1,next,8);
   //head=intersectNode(head,head);
   count=listTraverse(head);
   printf("\n");
   count1=listTraverse(head1);
   hashTable=(hashNode *) calloc(11,sizeof(hashNode));
   /*head=delete(head,4);
   printf("\n");
   listTraverse(head);
   head=delete(head,0);
   printf("\n");
   listTraverse(head);
   head=delete(head,6);
   printf("\n");
   listTraverse(head);

   head=deleteAll(head);
   printf("\n");
   listTraverse(head);*/

   
   /*printf("\n");
   printf("\n");
   printf("Please Enter the index of the node to search from end\n");

   int count;
   scanf("%d",&count);

   createHash(head,count);
   printf("\n");

   findNode(head,count);
   printf("\n");
   findLoop(head);*/
   
   //findIntersection(head1,head,count1,count);
   //stackIntersection(head1,head,count1,count);
  // head=reverse(head);
  // listTraverse(head);
   printf("\n");
 //  listTraverse1(head);
   printf("\n");
  // listEvenOdd(head);
   head1=mergeNode(head1,head);
   listTraverse(head1);
   return 0;
}
listNode* deleteAll(listNode *head)
{
   listNode *current,*temp;
   current=head;

   if(head->next==NULL)
   {
     free(head);
     return NULL;
   }
   while(current!=NULL)
   {
     temp=current;
     current=temp->next;
     temp->next==NULL;
     free(temp);
   }
   head=current=NULL;
   return NULL;
}
listNode* delete(listNode *head, int data)
{
   listNode *current=head;
   
   listNode *temp,*prev;
   
   listNode *node=search(head,data);

   if(head==node)
   {
      temp=head;
      head=temp->next;
      temp->next==NULL;
      free(temp);
      return head;
   }
   while(current!=node)
   {
      prev=current;
      current=current->next;
   }   

   temp=current;
   prev->next=temp->next;
   temp->next==NULL;
   free(temp);
   return head;
}
int listTraverse( listNode *head)
{
   if(head==NULL)
   {
     printf("Node not found");
     return 1;
   }
   int count=0;
   listNode *temp ;
   temp=head;
   while(temp!=NULL)
   {
     count++;
     printf("%d ", temp->data);
     temp=temp->next;
   }
   printf("\n");
   printf("%d",count);
   return count;
}
listNode* search(listNode *head, int data)
{
   if(head==NULL)
     exit(0);
   listNode *current=head;

   while(current->data!=data)
    current=current->next;
   
   return current;
}



listNode* insertBefore(listNode *head, listNode* node, int data)
{
   listNode *current=head;
   listNode *prev;
   if(node == NULL || head == NULL)
        return NULL;
   if(head==node)
   {
     insertBeg(head,data);
   }
   while(current!=node)
   {
     prev=current;
     current=current->next;
   }
   listNode *temp=addNode(node,data);
   prev->next=temp;
   return head;
}
listNode* insertAfter(listNode *head, listNode* node, int data)
{
   listNode *current=head;
   if(node == NULL || head == NULL)
        return NULL;
   if(head==node)
   { 
     insertBeg(head,data);
   }
   while(current!=node)
   {
     current=current->next;
   }
   listNode *temp=addNode(current->next,data);
   current->next=temp;
   return head;
}
listNode* insertEnd(listNode *head, int data)
{
   listNode *temp=NULL;

   listNode *current;
   /*current=(listNode *) malloc(sizeof(listNode));
   if(current==NULL)
   {
     printf("Error creating a new node.\n");
        exit(0);
   }*/
   if(head == NULL)
       return NULL;
   current=head;
   while(current->next!=NULL)
   {
      current=current->next;
   }
   temp=addNode(NULL,data);
   current->next=temp;
   return head;
   
}
listNode * insertBeg( listNode *head , int data)
{
   listNode *temp;
   /*temp=(listNode *) malloc(sizeof(listNode));
   if(temp==NULL)
   {
     printf("Error creating a new node.\n");
        exit(0);
   }*/

   if(head==NULL)
   {
     head=addNode(NULL,data);
     return head;
   } 
   listNode *current=head;
   temp=addNode(current, data);
   head=temp;
 
   return head;
   
}
listNode* addNode(listNode *current, int data)
{
   listNode *temp;
   temp=(listNode *) malloc(sizeof(listNode));
   if(temp==NULL)
   {
     printf("Error creating a new node.\n");
        exit(0);
   }

   temp->data= data;
   temp->next=current;
   return temp;
}
void createHash(listNode *head,int key)
{
   listNode *current,temp;
   if(head==NULL)
     exit(0);
    
   int count=0;
   current=head;
   while(current!=NULL)
   {
     hashTable[count].head=current;
     count++;
     current=current->next;
   }
   
   current=head;
   if(key<=count)
     key=count-key;
   else
   {
     printf("Invalid key:Key Should be below %d",count);
     exit(1);
   }
   int count1=0;
   while(current!=NULL)
   {
      if(count1==key)
      {
         printf("Value is %d",hashTable[key].head->data);
      }
      count1++;
      current=current->next;
   }
}
void findNode(listNode *head, int count)
{
   listNode *current,*temp,*curr;

   if(head==NULL)
   {
     printf("Node not found");
     exit(0);
   }
   current=head;
   temp=head;
   int count1=0;
   while(current!=NULL)
   {
     if(count1>=count)
     {
       temp=temp->next;
     }
     count1++;
     current=current->next;
   }   
   if(count1<count)
   {
     printf("Invalid Key:Key Should be below %d",count);
     exit(0);
   }
   printf("Value of key %d:",temp->data);
}
void findLoop(listNode *head)
{
  listNode *current,*temp;
  current=head;
  temp=head;
  while(current && temp)
  {
    current=current->next;
    if(current==NULL)
    {
      printf("Linked list has no loop");
      exit(0);
    }
    if(current==temp)
    {
      printf("Linked list has loop");
      exit(0);
    }
    current=current->next;
    if(current==temp)
    {
      printf("Linked list has loop");
      exit(0);
    }
    temp=temp->next;
  }
  if(current==NULL)
   printf("Linked list has no loop");
}
listNode* intersectNode(listNode *head1, listNode* head)
{
  listNode *current1;
  listNode *current;
  current1=head1;
  current=head;
  current=current->next;
  while(current1->next!=NULL)
  {
    current1=current1->next;
  }
  current1->next=current;
  return head1;
}
void findIntersection(listNode *head1,listNode *head, int count1,int count)
{
  listNode *current,*current1,*curr,*temp;
  current1=head1;
  current=head;
  int count2=0;
  if(count1>count)
    count2=count1-count;
  else
    count2=count-count1;
  int i=0;
  while(i<count2)
  {
    i++;
    current1=current1->next;
  }
  while(current && current1)
  {
    if(current==current1)
    {
      printf("\nNode Intersection found :%d,%d",current->data,current1->data);
      return ;
    }
    current=current->next;
    current1=current1->next;
  }
  
  printf("\nNode Intersection not found");
}
void stackIntersection(listNode *head1,listNode *head,int count1,int count)
{
  listNode *current,*current1,*curr,*temp;

  current=head;
  current1=head1;
  listNode *arr[count];
  listNode *arr1[count1];
  int i=0;
  while(current!=NULL)
  {
    arr[i++]=current;
    current=current->next;
  }
  i=0;
  while(current1!=NULL)
  { 
    arr1[i++]=current1;
    current1=current1->next;
  }
  count--;
  count1--;
  listNode *prev,*prev1;
  while(count1>=0 && count>=0)
  {
    if(arr[count] != arr1[count1])
    {
      printf("\nNode intersection found %d,%d", prev->data,prev1->data);
      return ;
    }
    prev=arr[count];
    prev1=arr1[count1];
    count--;
    count1--;
  }
    printf("\nNode Intersection not found");

}
listNode * reverse(listNode *head)
{
  listNode *current,*temp,*prev=NULL;
  current=head;
  while(current!=NULL)
  {
     temp=current->next;
     current->next=prev;
     prev=current;
     current=temp;
  }
  head=prev;
  return head;

}
int listTraverse1( listNode *head)
{
  if(head==NULL)
    return 1;
  printf("%d ",head->data);
  listTraverse1(head->next);
}
void listEvenOdd(listNode *head)
{
  listNode *current=head;

  while(current && current->next)
  {
     current=current->next->next;
  } 
  if(current)
    printf("Odd number of nodes");
  else
    printf("Even number of nodes");
}
listNode * mergeNode(listNode *head1, listNode *head)
{
  listNode *current1,*current,*temp;
  if(!head)
    return head1;
  if(!head1)
    return head;
  current1=head1;
  current=head;
  listNode *head2=NULL;
  int count=0;
  
    if(current1->data < current->data)
    {
       head2=current1;      
       head2->next=mergeNode(current1->next,current);
    }
    else{
       head2=current;
       head2->next=mergeNode(current->next,current1);
    }
  return head2;
}
