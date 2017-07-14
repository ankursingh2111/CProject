#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct binaryTree
{
  int data;
  struct binaryTree *left;
  struct binaryTree *right;
}binaryTree;

binaryTree * createTree(int num)
{
  binaryTree *btemp=(binaryTree*)malloc(sizeof(binaryTree));
  if(btemp==NULL)
  {
     printf("No memory allocated");
     exit(1);
  }
  btemp->data=num;
  btemp->left=NULL;
  btemp->right=NULL;
  return btemp;
}

binaryTree * addNode(binaryTree *root, int num)
{
   binaryTree *prev,*curr;
   if(root==NULL)
   {
     root=createTree(num);
     return root;
   }
   int isleft=0;
   curr=root;
   while(curr!=NULL)
   {
     prev=curr;
     if((curr->data)>num)
     {
       curr=curr->left;
       isleft=1;
     }
     else
     {
       curr=curr->right;
       isleft=0;
     }
   }
   curr=createTree(num);
   if(isleft)
     prev->left=curr;
   else
     prev->right=curr;

   return root;
}
typedef struct linkedList
{
  int data;
  struct linkedList *next;
}linkedList;

typedef struct assList
{
 linkedList *head;
}assList;
linkedList* createNode(int data)
{
   linkedList *temp;
   temp=(linkedList *) malloc(sizeof(linkedList));
   if(temp==NULL)
   {
     printf("Error creating a new node.\n");
        exit(0);
   }

   temp->data= data;
   temp->next=NULL;
   return temp;
}
void Preorder(binaryTree *curr,int ht,linkedList **l1)
{ 
  if(curr)
  { 
    if(l1[ht]==NULL)
       l1[ht]=createNode(curr->data);
    else
    {
       linkedList *lnode=createNode(curr->data);
       linkedList *temp=l1[ht];
       while(temp->next!=NULL)
         temp=temp->next;
       temp->next=lnode;
    }
    printf("%d ",curr->data);
    Preorder(curr->left,ht-1,l1);
    Preorder(curr->right,ht+1,l1);
 }
}

int main()
{
  binaryTree *b1;
  b1=createTree(6);
  b1=addNode(b1,1);
  b1=addNode(b1,5);
  b1=addNode(b1,7);
  b1=addNode(b1,9);
  b1=addNode(b1,4);
  b1=addNode(b1,8);
  b1=addNode(b1,3);
  b1=addNode(b1,2);

  linkedList **l1=(linkedList**)malloc(10*sizeof(linkedList*));

  for(int i=0; i<10;i++)
   l1[i]=NULL;

  Preorder(b1,5,l1);

  for(int j=0; j<10;j++) 
  {
    while(l1[j])
    {
       printf("%d ",l1[j]->data);
       l1[j]=l1[j]->next;
    }
    printf("\n");
  }
}
