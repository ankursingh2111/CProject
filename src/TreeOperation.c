#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
void display(binaryTree *curr)
{
  if(curr)
  {
    printf("%d ",curr->data);
    display(curr->left);
    display(curr->right);
 } 
}
void display1(binaryTree *curr)
{
  if(curr)
  {
    display1(curr->left);
    printf("%d ",curr->data);
    display1(curr->right);
 } 
}
void display2(binaryTree *curr)
{
  if(curr)
  {
    display2(curr->left);
    display2(curr->right);
    printf("%d ",curr->data);
 } 
}
int main()
{
  binaryTree *b1;
  b1=createTree(4);
  b1=addNode(b1,5);
  b1=addNode(b1,7);
  b1=addNode(b1,2);
  b1=addNode(b1,9);
  b1=addNode(b1,1);
  
  display(b1);
  printf("\n");
  display1(b1);
  printf("\n");
  display2(b1);
}
