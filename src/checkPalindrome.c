#include<stdio.h>
#include<stdlib.h>
typedef struct listNode
{
   char data;
   struct listNode *next;
}listNode;

listNode * insertBeg( listNode *head , char data);
int listTraverse( listNode *head);
listNode* addNode( listNode *current, char data);
void listEvenOdd(listNode *head);
void checkPalindrome(listNode *head);
int main()
{
   listNode *head=NULL;
   listNode *head1=NULL;
   listNode *next;
   int count=0,count1=0;
   head=insertBeg(head,'a');
   head=insertBeg(head,'b');
   head=insertBeg(head,'a');
   head=insertBeg(head,'a');
   head=insertBeg(head,'b');
   head=insertBeg(head,'a');
  // head=insertEnd(head,2);
  // head=insertEnd(head,5);
   listTraverse(head);
   checkPalindrome(head);
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
listNode * insertBeg( listNode *head , char data)
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
listNode* addNode(listNode *current, char data)
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
void checkPalindrome(listNode *head)
{
   listNode *slow, *fast,*current;
   fast=head;
   slow=head;
   current=head;
   while(fast->next && fast->next->next)
   {
     slow=slow->next;
     fast=fast->next->next;
   }
   listNode *temp=slow,*temp1;
   listNode *prev=slow;
   slow=slow->next;
   while(slow)
   {
     temp1=slow->next;
     slow->next=prev;
     prev=slow;
     slow=temp1;
   }
   printf("\n");
  // listTraverse(prev);

   while(current!=temp)
   {
     if(current->data==prev->data)
     {
        current=current->next;
        prev=prev->next;
     }
     else
     {
        printf("Not a palindrome");
        exit(0);
     }
   }
   if(current->data==prev->data)
    printf("It is a palindrome");
}
