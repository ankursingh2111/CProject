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
typedef struct stackTree
{
int top;
int size;
binaryTree ** btree;
}stackTree;

stackTree * createStack(int size)
{
 stackTree *stree=(stackTree*)malloc(sizeof(stackTree));
 if(stree==NULL)
 {
     printf("No memory allocated");
     exit(1);
 }
 stree->top=0;
 stree->size=size;
 stree->btree=(binaryTree**)malloc(size*sizeof(binaryTree));

 int i;
 for (i = 0; i < size; ++i)
      stree->btree[i] = NULL;

 return stree;
 

}
void stackPush(stackTree *stree, binaryTree *btree)
{
  if(stree->top==stree->size)
  {
     printf("Stack is full");
     exit(1);
  }
  stree->btree[(stree->top)++]=btree;
}
binaryTree * stackPop(stackTree *stree)
{
  if(stree->top==0)
  {
    printf("Stack is empty");
    exit(1);
  }
  return stree->btree[--(stree->top)];
}
int isStackEmpty(stackTree *stree)
{
  if(stree->top==0)
    return 0;
}
void DeleteStack(stackTree *stree)
{
   int i=0;

   for(i=0;i<stree->size;i++)
   {
      free(stree->btree[i]);
   }
   free(stree);
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
void Preorder(binaryTree *curr)
{
  if(curr)
  {
    printf("%d ",curr->data);
    Preorder(curr->left);
    Preorder(curr->right);
 } 
}
int PreorderItr(binaryTree *temp)
{
    binaryTree *curr=temp;
    if(curr==NULL)
      return 0;
    stackTree *currStack=createStack(10);
   
    while(1)
    {
       while(curr!=NULL)
       { 
         printf("%d ", curr->data);
         stackPush(currStack,curr); 
         
         curr=curr->left;
       }
       if(!isStackEmpty(currStack))
          break;
       curr=stackPop(currStack);
       curr=curr->right;

    }
   //DeleteStack(currStack);
        
}
void Inorder(binaryTree *curr)
{
  if(curr)
  {
    Inorder(curr->left);
    printf("%d ",curr->data);
    Inorder(curr->right);
 } 
}
int InorderItr(binaryTree *curr)
{
    if(curr==NULL)
      return 0;

    stackTree *currStack=createStack(10);

    while(1)
    {
       while(curr!=NULL)
       {
         stackPush(currStack,curr);

         curr=curr->left;
       }
       if(!isStackEmpty(currStack))
          break;
       curr=stackPop(currStack);
       printf("%d ", curr->data);
       curr=curr->right;

    }
    DeleteStack(currStack);

}
void Postorder(binaryTree *curr)
{
  if(curr)
  {
    Postorder(curr->left);
    Postorder(curr->right);
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
  
  Preorder(b1);
  printf("\n");
  Inorder(b1);
  printf("\n");
  Postorder(b1);
  printf("\n");
  PreorderItr(b1);
  printf("\n");
  InorderItr(b1);
}
