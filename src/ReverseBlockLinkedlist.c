#include<stdio.h>
#include<stdlib.h>

typedef struct listNode
{
   int data;
   struct listNode *next;
}listNode;

listNode * insertBeg( listNode *head , int data);
int listTraverse( listNode *head);
listNode* addNode( listNode *current, int data);
listNode * reverseKNode(listNode *head, int count);
listNode * returnKthNode(listNode *head,int count);
int checkKthNode(listNode *head,int k);

int main()
{
   listNode *head=NULL;
   listNode *head1=NULL;
   listNode *next;
   int count=0,count1=0;
   head=insertBeg(head,'1');
   head=insertBeg(head,'2');
   head=insertBeg(head,'3');
   head=insertBeg(head,'4');
   head=insertBeg(head,'5');
   head=insertBeg(head,'6');
   head=insertBeg(head,'7');
   head=insertBeg(head,'8');
   listTraverse(head);
   printf("\n");

   head=reverseKNode(head,4);
   listTraverse(head);
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
     printf("%c ", temp->data);
     temp=temp->next;
   }
   printf("\n");
   printf("%d",count);
   return count;
}
listNode * insertBeg( listNode *head , int data)
{
   listNode *temp;

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
int checkKthNode(listNode *head,int k)
{
   listNode *current=head;
   
   int count=1;
   while(current)
   {
     current=current->next;
     if(count==k)
       return 1;
     count++;
   }
   return 0;
}
listNode * returnKthNode(listNode *head,int count)
{
   listNode *current=head;
   int count1=1;
   if(checkKthNode(head,count))
   {
     while(current)
     {
       if(count1==count)
       {
          return current->next;
       }
       current=current->next;
       count1++;
     }
   }
   return head;
}
listNode * reverseKNode(listNode *head, int count)
{
   listNode *current=head;
   listNode *curr=head,*temp,*prev=NULL,*prev_curr=head,*prev_last=NULL;
   listNode *newHead=returnKthNode(current,count-1);
   int count1;
   while(current && checkKthNode(current,count))
   {
     curr=returnKthNode(current,count);
     int i=0;
     prev=NULL;
     while(i<count)
     {
       temp=current->next;
       current->next=prev;
       prev=current;
       current=temp;
       i++;
     }
     if(prev_last)
     {
        prev_last->next=prev;
     }
     prev_last=prev_curr;
     prev_curr=current;
  }
  if(current)
    prev_last->next=current;
  return newHead;
}
