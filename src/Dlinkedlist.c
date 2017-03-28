#include<stdio.h>
#include<stdlib.h>
typedef struct dlinkNode
{
   int data;
   struct dlinkNode *next;
   struct dlinkNode *prev;
}dlinkNode;
int traverse(dlinkNode *head);
dlinkNode * insertBeg(dlinkNode *head, int data);
dlinkNode * createNode(dlinkNode *prv,dlinkNode *nxt, int data);
dlinkNode * insertEnd(dlinkNode *head, int data);
dlinkNode * insertAfter(dlinkNode *head,dlinkNode *node, int data);
dlinkNode * insertBefore(dlinkNode *head,dlinkNode *node, int data);
dlinkNode * search(dlinkNode *head, int data);
dlinkNode * delete(dlinkNode *head, int data);
int main()
{
  dlinkNode *head=NULL,*temp=NULL;

  head=insertBeg(head,3);
  head=insertBeg(head,9);
  head=insertBeg(head,8);
  head=insertBeg(head,7);
  head=insertBeg(head,6);
  traverse(head);

  head=insertEnd(head,0);
  head=insertEnd(head,1);
  traverse(head);

  temp=search(head,7);

  head=insertAfter(head,temp,5);

  head=insertBefore(head,temp,2);
  traverse(head);

  head=delete(head,6);
  traverse(head);

  head=delete(head,1);
  traverse(head);

  head=delete(head,9);
  traverse(head);
}
int traverse(dlinkNode *head)
{
  dlinkNode *current = head;
  int count=0;
  if(head==NULL)
   return 1;
  while(current!=NULL)
  {
    count++;
    printf("%d ",current->data);
    current=current->next;
  }
  printf("\n");
  printf("%d", count);
  printf("\n");
  
  return count;
}
dlinkNode * search(dlinkNode *head, int data)
{
  dlinkNode *current;
  if(head==NULL)
    return NULL;

  current=head;
  while(current->data!=data)
    current=current->next;

  return current;
}
dlinkNode * createNode(dlinkNode *prv,dlinkNode *nxt, int data)
{
  dlinkNode *node;
  node=(dlinkNode*) malloc(sizeof(dlinkNode));

  if(node==NULL)
  {
     printf("Error creating a new node.\n");
     exit(0);
  }
  node->data=data;
  node->prev=prv;
  node->next=nxt;

  return node;
}
dlinkNode * insertBeg(dlinkNode *head, int data)
{
  dlinkNode *current,*temp;

  if(head==NULL)
  {
    temp=createNode(NULL,NULL,data);
    head=temp;
    return head;
  }

  current = head;

  temp=createNode(NULL,current,data);
  current->prev=temp;
  head=temp;
  return head;
}
dlinkNode * insertEnd(dlinkNode *head, int data)
{
  dlinkNode *current,*temp;

  if(head==NULL)
  {
    temp=createNode(NULL,NULL,data);
    head=temp;
    return head;
  }

  current = head;

  while(current->next!=NULL)
  {
    current=current->next;
  }
  temp=createNode(current,NULL,data);
  current->next=temp;
  return head;
}
dlinkNode * insertAfter(dlinkNode *head, dlinkNode *node, int data)
{
  dlinkNode *current,*temp,*curr;

  current=node->next;
  temp=createNode(node,current,data);
  node->next=temp;
  current->prev=temp;
  return head;
}
dlinkNode * insertBefore(dlinkNode *head, dlinkNode *node, int data)
{
  dlinkNode *current,*temp;

  current=node->prev;
  temp=createNode(current,node,data);
  node->prev=temp;
  current->next=temp;
  return head;
}
dlinkNode * delete(dlinkNode *head, int data)
{
  dlinkNode *current=NULL,*temp=NULL,*curr=NULL;

  temp=search(head,data);
  if(temp==NULL)
  {
    printf("No node found");
    return head;
  }
  current=head;
  if(head==temp)
  {
    head=current->next;
    head->prev=NULL;
    free(temp);
    return head;
  }
  else if(temp->next==NULL)
  {
    current=temp->prev;
    current->next=NULL;
    free(temp);
    return head;
  }
  else
  {
    current=temp->prev;
    curr=temp->next;

    current->next=temp->next;
    curr->prev=temp->prev;

    temp->next=NULL;
    temp->prev=NULL;
    free(temp);
    return head;
  }
}
