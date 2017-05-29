#include<stdio.h>
#include<stdlib.h>

typedef struct ClistNode
{
  int data;
  struct ClistNode *next;
}ClistNode;

ClistNode * createNode(ClistNode *current, int data);
ClistNode * insertBeg(ClistNode *head, int data);
ClistNode * insertEnd(ClistNode *head, int data);
int traverse(ClistNode *head);
ClistNode * search(ClistNode *head, int data);
ClistNode * delete(ClistNode *head,int data);
void findLoop(ClistNode *head);
void splitNode(ClistNode *head , ClistNode **head1,ClistNode **head2);
int traverse1(ClistNode **head);
void splitList(struct ClistNode *head, struct ClistNode **head1_ref, struct ClistNode **head2_ref);
int main()
{
  ClistNode *head=NULL, *temp;
  head=insertBeg(head,5);
  head=insertBeg(head,9);
  head=insertBeg(head,8);
  head=insertEnd(head,1);
  head=insertEnd(head,2);
  head=insertEnd(head,4);
  head=insertBeg(head,6);
  head=insertEnd(head,3);
  
  traverse(head);
 
/*  head=delete(head,0);
  traverse(head);
 
  head=delete(head,3);
  traverse(head);
 
  head=delete(head,1);
  traverse(head);

  head=delete(head,8);
  traverse(head);

  head=delete(head,4);
  traverse(head);*/
  printf("\n");
  ClistNode *head1,*head2;
  findLoop(head);
  printf("\n");
  //splitNode(head, head1,head2);
  printf("\n");
  splitList(head,&head1,&head2);
  traverse(head1);
  printf("\n");
  traverse(head2);
  
}
ClistNode * createNode(ClistNode *current, int data)
{
  ClistNode *temp;
  temp=(ClistNode*) malloc(sizeof(ClistNode));
 
  if(temp==NULL)
  {
    printf("Node not created");
    exit(0);
  }
  temp->data=data;
  temp->next=current;
  
  return temp;
}
ClistNode * search(ClistNode *head, int data)
{
  ClistNode *current=head,temp;
  while(current->data!=data)
  {
      current=current->next;
      if(current==head)
        return NULL;
  }
  return current;
}
ClistNode * delete(ClistNode *head,int data)
{
  ClistNode *current=head,*temp,*prev,*curr;

  temp=search(head,data);
  if(temp==head)
  {
    do
    {
      prev=current;
      current=current->next;
    }while(current!=head);
    head=current->next;
    prev->next=head;
    free(current);
    return head;
  }
  while(current!=temp)
  {
    prev=current;
    current=current->next;
  }
  prev->next=current->next;
  free(temp);
  return head;
}
ClistNode * insertBeg(ClistNode *head, int data)
{
  ClistNode *current ,*temp,*prev;

  if(head==NULL)
  {
    temp=createNode(head,data);
    head=temp;
    head->next=head;
    return head;
  }

  current=head;

  do
  {
    prev=current;
    current=current->next;
  }while(current!=head);
  temp=createNode(current,data);
  prev->next=temp;
  head=temp;
  return head;
}
ClistNode * insertEnd(ClistNode *head, int data)
{
  ClistNode *current ,*temp,*prev;

  if(head==NULL)
  {
    temp=createNode(head,data);
    head=temp;
    head->next=head;
    return head;
  }

  current=head;

  do
  {
    prev=current;
    current=current->next;
  }while(current!=head);
  temp=createNode(current,data);
  prev->next=temp;
  
  return head;
}
int traverse(ClistNode *head)
{
  ClistNode *current;
  int count=0;
  current=head;
  do
  {
    count++;
    printf("%d ",current->data);
    current=current->next;
  }while(current!=head);
  printf("\n");

  printf("%d",count);
  printf("\n");
  
}
void findLoop(ClistNode *head)
{
  ClistNode *current,*temp;
  current=head;
  temp=head;
  int count=0;
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
      break;
    }
    current=current->next;
    if(current==temp)
    {
      printf("Linked list has loop");
      break;
    }
    temp=temp->next;
  }
  if(current==NULL)
  {
    printf("Linked list has no loop");
    exit(0);
  }
   temp=temp->next;
  while(temp!=current)
  {
    count++;
    temp=temp->next;
  }
  printf("\n");
  printf("The length of loop is %d" , count);

}
void splitNode(ClistNode *head , ClistNode **head1,ClistNode **head2)
{
  ClistNode *fast,*slow;
  fast=head;
  slow=head;

  while(fast->next!=head && fast->next->next!=head)
  {
     slow=slow->next;
     fast=fast->next->next;
  }
  ClistNode *temp=slow->next;
  if(fast->next==head)
     printf("Odd number of nodes\n");
  else
  {
     printf("Even number of nodes\n");
     fast=fast->next;
  }
     *head1=head;
     *head2=temp;
     fast->next=temp;
     slow->next=head;

    
}
int traverse1(ClistNode **head)
{
  ClistNode **current;
  int count=0;
  current=head;
  do  
  {
    count++;
    printf("%d ",(*current)->data);
    *current=(*current)->next;
  }while(current!=head);
  printf("\n");

  printf("%d",count);
  printf("\n");
  
}
/* Function to split a list (starting with head) into two lists.
   head1_ref and head2_ref are references to head nodes of 
    the two resultant linked lists */
void splitList(struct ClistNode *head, struct ClistNode **head1_ref, struct ClistNode **head2_ref)
{
  struct ClistNode *slow_ptr = head;
  struct ClistNode *fast_ptr = head; 
 
  if(head == NULL)
    return;
  
  /* If there are odd nodes in the circular list then
     fast_ptr->next becomes head and for even nodes 
     fast_ptr->next->next becomes head */
  while(fast_ptr->next != head &&
         fast_ptr->next->next != head) 
  {
     fast_ptr = fast_ptr->next->next;
     slow_ptr = slow_ptr->next;
  }  
 
 /* If there are even elements in list then move fast_ptr */
  if(fast_ptr->next->next == head)
    fast_ptr = fast_ptr->next;      
   
  /* Set the head pointer of first half */
  *head1_ref = head;    
      
  /* Set the head pointer of second half */
  if(head->next != head)
    *head2_ref = slow_ptr->next;
   
  /* Make second half circular */  
  fast_ptr->next = slow_ptr->next;
   
  /* Make first half circular */  
  slow_ptr->next = head;       
}
