#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct BST
{
struct BST *left;
struct BST *right;
int data;
}BST;

BST * createTree(int data)
{
  BST *temp=(BST*)malloc(sizeof(BST));

  if(temp==NULL)
  {
     printf("No memory allocated");
     exit(1);
  }
  temp->data=data;
  temp->left=NULL;
  temp->right=NULL;
  return temp;
}

BST * insertNode(BST * root, int data)
{
  BST *temp;
  if(root==NULL)
    root=createTree(data);
  else
  {
    if(data>root->data)
      root->right=insertNode(root->right,data);
    else
      root->left=insertNode(root->left,data);
  }
  return root;
}

int Preorder(BST * root)
{
  if(root==NULL)
    return 0;
  printf("%d ",root->data);
  Preorder(root->left);
  Preorder(root->right);
  return 0;
}

int findMin(BST *root)
{
  if(root==NULL)
    return 0;
  if(root->left==NULL)
  {
    printf("%d \n",root->data);
    return 1;
  }
  findMin(root->left);
}
int findMax(BST *root)
{
  if(root==NULL)
    return 0;
  if(root->right==NULL)
  {
    printf("%d \n",root->data);
    return root->data;
  }
  findMax(root->right);
}
BST * searchTree(BST *root,int data)
{
  if(root==NULL)
    return root;

  if(data>root->data)
     return searchTree(root->right,data);
  else if(data<root->data)
     return searchTree(root->left,data);
  
  return root;
}

int searchTreeIterative(BST * root, int data)
{
  if(root==NULL)
     return 0;
  BST * temp=root;
  while(temp)
  {
    if(data>temp->data)
      temp=temp->right;
    else if(data<temp->data)
      temp=temp->left;
    else
    {
      printf("\nNode found %d",temp->data);
      return 1;
    }
  }
  printf("\nNode not found");
  return 0;
} 
BST * deleteNode(BST *root, int data)
{
  if(root==NULL)
     return 0;
  BST * temp;
  if(data>root->data)
    root->right=deleteNode(root->right,data);
  else if(data<root->data)
    root->left=deleteNode(root->left,data);
  else
  {
      if(root->right && root->left)
       {
          
         root->data=findMax(root->left);
         root->left=deleteNode(root->left,root->data);
       }
       else
       {
         temp=root;
         if(root->right)
           root=root->right;
         else if(root->left)
           root=root->left;

         free(temp);
       }
  }
  return root;
}
BST * deleteNode1(BST *root, int data)
{
  int isleft,isright;
  if(root==NULL)
     return 0;
  BST * temp=root;
  BST * prev;
  BST * prev1;
  while(temp)
  { 
    if(data>temp->data)
    {
      prev1=temp;
      temp=temp->right;
      isleft=0;
      isright=1;
    }
    else if(data<temp->data)
    {
      prev1=temp;
      temp=temp->left;
      isleft=1;
      isright=0;
    }
    else
    {
       prev=temp;
       if(temp->right && temp->left)
       {
         temp->data=findMax(temp->left);
         deleteNode(temp->left,temp->data);
         break; 
       }
       else
       {
         if(temp->right)
           temp=temp->right;
         else if(temp->left)
           temp=temp->left;
         else
         {
            free(temp);
            if(isleft)
              prev1->left=NULL;
            else
              prev1->right=NULL;
            break;
         }
         if(isright)
           prev1->right=temp;
         else
           prev1->left=temp;

         free(prev);
         prev=NULL;
         break;
        
       }
    }
  }
  return root;
}
BST * LCA(BST *root, int var, int var1)
{
   if(root==NULL)
      return root;
   else if(var>root->data && var1>root->data)
      return LCA(root->right,var,var1);
   else if(var<root->data && var1<root->data)
      return LCA(root->left,var,var1);
   else
     return root;

}
int checkBST(BST *root, int *prev)
{
  if(root==NULL)
    return 1;

  if(!checkBST(root->left, prev))
      return 0;
  if(root->data<*prev)
      return 0;

  *prev=root->data;
  
  return checkBST(root->right,prev);
}
int main()
{
  BST * root=NULL;
  root=insertNode(root,10);
  insertNode(root,15);
  insertNode(root,6);
  insertNode(root,9);
  insertNode(root,17);
  insertNode(root,4);
  insertNode(root,8);
  insertNode(root,13);
  insertNode(root,2);
  insertNode(root,3);
  insertNode(root,18);
  insertNode(root,16);

  Preorder(root);
  printf("\n");
  findMin(root);
  printf("\n");
  findMax(root);
 
  BST *temp=searchTree(root,8);
  printf("\n%d ",temp->data);

  searchTreeIterative(root,14);
  searchTreeIterative(root,13);
  
  root=deleteNode(root,6);
 printf("\n");  
   Preorder(root);
  printf("\n");

   temp=LCA(root, 2,9);
   printf("\nLCA of 2,9 is %d ",temp->data);

   temp=LCA(root,15,8);
   printf("\nLCA of 15,8 is %d ",temp->data);   
   int min=-1;
   printf("\n%d ",checkBST(root,&min));

}
