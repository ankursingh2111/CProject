#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct threadedTree
{
struct threadedTree *left;
struct threadedTree *right;
int Rtag;
int Ltag;
int data;
}threadedTree;

threadedTree * createTree(int data)
{
  threadedTree *temp=(threadedTree*)malloc(sizeof(threadedTree));

  if(temp==NULL)
  {  
     printf("No memory allocated");
     exit(1);
  } 
  temp->data=data;
  temp->Ltag=0;
  temp->Rtag=0;
  temp->left=NULL;
  temp->right=NULL;
  return temp;
}
threadedTree * createDummyNode()
{
  threadedTree *temp=createTree(200);
  
  temp->left=temp->right=temp;
  temp->Ltag=0;  
  temp->Rtag=1;

  return temp;
}
threadedTree * insertNode(threadedTree *root, int data)
{
  threadedTree *newNode=createTree(data);
  threadedTree *temp;
  int isLeft,isRight;
  isLeft=isRight=0;
  if(root->Ltag==0)
  {
     newNode->left=root;
     root->left=newNode;
     newNode->Ltag=root->Ltag;
     root->Ltag=1;
     newNode->right=root;
     return root;
  } 
  else
  {
     temp=root->left;
     while(1)
     {
       if(data>temp->data)
       {
          if(temp->Rtag==0)
          {
            isLeft=0;
            isRight=1;
            break;
          }
          else
            temp=temp->right;
       }
       else
       {     
          if(temp->Ltag==0)
          {
            isLeft=1;
            isRight=0;
            break;
          }
          else
            temp=temp->left;
       }
     }
  }
  
  if(isLeft)
  {
     newNode->left=temp->left;
     temp->left=newNode;
     newNode->Ltag=temp->Ltag;
     temp->Ltag=1;
     newNode->right=temp;
  }
  else if(isRight)
  {
     newNode->right=temp->right;
     temp->right=newNode;
     newNode->Rtag=temp->Rtag;
     temp->Rtag=1;
     newNode->left=temp;
  }
  return root;
}
threadedTree * inOrder(threadedTree * root)
{
  threadedTree *temp;
  if(root->Rtag==0)
   return root->right;
  else
  {
    temp=root->right;
    while(temp->Ltag!=0)
     temp=temp->left;
  }
  return temp;
}
void inorderTree(threadedTree * root)
{
  threadedTree *temp;

  temp=inOrder(root);

  while(temp!=root)
  {
    printf("%d ",temp->data);
    temp=inOrder(temp);
  }
}
threadedTree * preOrder(threadedTree *root)
{
  threadedTree *temp;
  if(root->Ltag==1)
    return root->left;
  else
  {
   temp=root;
   while(temp->Rtag==0)
     temp=temp->right; 
  }
  return temp->right;
}
void preorderTree(threadedTree *root)
{
  threadedTree *temp;

  temp=preOrder(root);

  while(temp!=root)
  {
    printf("%d ",temp->data);
    temp=preOrder(temp);
  }
}


int main()
{

  threadedTree *root=createDummyNode();
 
  insertNode(root,10);
  insertNode(root,7);
  insertNode(root,14);
  insertNode(root,6);
  insertNode(root,5);
  insertNode(root,13);
  insertNode(root,2);
  insertNode(root,3);

// preorderTree(root);
  printf("\n");
  inorderTree(root);
  return 0;
}

